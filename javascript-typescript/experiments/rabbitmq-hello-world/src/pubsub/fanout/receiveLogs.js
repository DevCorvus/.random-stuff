const amqp = require("amqplib/callback_api");

const exchange = "logs";

amqp.connect("amqp://localhost", (err0, conn) => {
    if (err0) throw err0;

    conn.createChannel((err1, channel) => {
        if (err1) throw err1;

        channel.assertExchange(exchange, "fanout", { durable: false });

        channel.assertQueue("", { exclusive: true }, (err2, q) => {
            if (err2) throw err2;

            channel.bindQueue(q.queue, exchange, "");

            console.log("Waiting for messages...");
            channel.consume(
                q.queue,
                (msg) => {
                    if (msg.content) {
                        console.log(msg.content.toString());
                    }
                },
                { noAck: true },
            );
        });
    });
});
