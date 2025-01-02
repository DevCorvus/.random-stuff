const amqp = require("amqplib/callback_api");

const queue = "rpc_queue";

// It has Round-robin dispatching by default (Load Balancing)
amqp.connect("amqp://localhost", (err0, conn) => {
    if (err0) throw err0;

    conn.createChannel((err1, channel) => {
        if (err1) throw err1;

        channel.assertQueue(queue, { durable: false });
        channel.prefetch(1);

        console.log("Waiting for RPC requests...");
        channel.consume(queue, (msg) => {
            // Some heavy task
            const upperMsg = msg.content.toString().toUpperCase();

            channel.sendToQueue(msg.properties.replyTo, Buffer.from(upperMsg), {
                correlationId: msg.properties.correlationId,
            });

            channel.ack(msg);
        });
    });
});
