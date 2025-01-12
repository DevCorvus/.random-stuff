const amqp = require("amqplib/callback_api");

const exchange = "logs";
const msg = process.argv[2];

amqp.connect("amqp://localhost", (err0, conn) => {
    if (err0) throw err0;

    conn.createChannel((err1, channel) => {
        if (err1) throw err1;

        channel.assertExchange(exchange, "fanout", { durable: false });
        channel.publish(exchange, "", Buffer.from(msg));
        console.log("Message sent");
    });

    setTimeout(() => {
        conn.close();
        process.exit(0);
    }, 500);
});
