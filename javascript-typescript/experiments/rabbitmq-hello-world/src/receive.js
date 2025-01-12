const amqp = require("amqplib/callback_api");

const queue = "alert";

// It has Round-robin dispatching by default (Load Balancing)
amqp.connect("amqp://localhost", (err0, conn) => {
    if (err0) throw err0;

    conn.createChannel((err1, channel) => {
        if (err1) throw err1;

        channel.assertQueue(queue, { durable: false });

        console.log("Waiting for messages...");
        channel.consume(
            queue,
            (msg) => {
                console.log(msg.content.toString());
            },
            { noAck: true },
        );
    });
});
