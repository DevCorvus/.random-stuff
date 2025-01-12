const amqp = require("amqplib/callback_api");

const queue = "rpc_queue";
const msg = process.argv[2];

amqp.connect("amqp://localhost", (err0, conn) => {
    if (err0) throw err0;

    conn.createChannel((err1, channel) => {
        if (err1) throw err1;

        channel.assertQueue("", { durable: false }, (err2, q) => {
            if (err2) throw err2;

            const correlationId = generateRandomId();

            // Send request
            console.log("Request sent");
            channel.sendToQueue(queue, Buffer.from(msg), {
                correlationId,
                replyTo: q.queue,
            });

            // Handle response callback
            channel.consume(
                q.queue,
                (msg) => {
                    if (msg.properties.correlationId === correlationId) {
                        console.log("Result:", msg.content.toString());

                        setTimeout(() => {
                            conn.close();
                            process.exit(0);
                        }, 500);
                    }
                },
                { noAck: true },
            );
        });
    });
});

function generateRandomId() {
    return (
        Math.random().toString() +
        Math.random().toString() +
        Math.random().toString()
    );
}
