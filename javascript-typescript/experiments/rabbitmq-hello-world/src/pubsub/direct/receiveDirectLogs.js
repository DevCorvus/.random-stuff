const amqp = require("amqplib/callback_api");

const exchange = "direct_logs";
const expectedSeverity = process.argv[2];

amqp.connect("amqp://localhost", (err0, conn) => {
    if (err0) throw err0;

    conn.createChannel((err1, channel) => {
        if (err1) throw err1;

        channel.assertExchange(exchange, "direct", { durable: false });

        channel.assertQueue("", { exclusive: true }, (err2, q) => {
            if (err2) throw err2;

            // We can bind it to multiple routes (severity levels)
            channel.bindQueue(q.queue, exchange, expectedSeverity);

            console.log(
                `Waiting for messages with severity level ${expectedSeverity}...`,
            );
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
