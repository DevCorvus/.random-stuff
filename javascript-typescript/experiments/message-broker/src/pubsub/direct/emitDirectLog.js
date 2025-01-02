const amqp = require("amqplib/callback_api");

const exchange = "direct_logs";
const msg = process.argv[2];
const severity = process.argv[3];

amqp.connect("amqp://localhost", (err0, conn) => {
    if (err0) throw err0;

    conn.createChannel((err1, channel) => {
        if (err1) throw err1;

        channel.assertExchange(exchange, "direct", { durable: false });
        channel.publish(exchange, severity, Buffer.from(msg));
        console.log("Message sent with severity level " + severity);
    });

    setTimeout(() => {
        conn.close();
        process.exit(0);
    }, 500);
});
