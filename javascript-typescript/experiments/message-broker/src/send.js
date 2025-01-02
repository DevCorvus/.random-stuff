const amqp = require("amqplib/callback_api");

const queue = "alert";
const msg = process.argv[2];

amqp.connect("amqp://localhost", (err0, conn) => {
    if (err0) throw err0;

    conn.createChannel((err1, channel) => {
        if (err1) throw err1;

        channel.assertQueue(queue, { durable: false });
        channel.sendToQueue(queue, Buffer.from(msg));
        console.log("Message sent");
    });

    setTimeout(() => {
        conn.close();
        process.exit(0);
    }, 500);
});
