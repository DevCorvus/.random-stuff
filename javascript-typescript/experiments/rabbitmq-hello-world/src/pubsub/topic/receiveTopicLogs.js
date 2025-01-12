const amqp = require("amqplib/callback_api");

const exchange = "topic_logs";

amqp.connect("amqp://localhost", (err0, conn) => {
    if (err0) throw err0;

    conn.createChannel((err1, channel) => {
        if (err1) throw err1;

        channel.assertExchange(exchange, "topic", { durable: false });

        channel.assertQueue("", { exclusive: true }, (err2, q) => {
            if (err2) throw err2;

            // These are examples of topic patterns you might bind to
            channel.bindQueue(q.queue, exchange, "very.specific.topic");
            channel.bindQueue(q.queue, exchange, "error.*");
            channel.bindQueue(q.queue, exchange, "*.*.dummy");
            channel.bindQueue(q.queue, exchange, "critical.#");

            console.log("Waiting for messages with certain topics...");
            channel.consume(
                q.queue,
                (msg) => {
                    if (msg.content) {
                        console.log(
                            `Message with topic ${msg.fields.routingKey}: ${msg.content.toString()}`,
                        );
                    }
                },
                { noAck: true },
            );
        });
    });
});
