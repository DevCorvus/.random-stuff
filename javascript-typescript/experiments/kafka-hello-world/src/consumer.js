import { kafka } from "./kafka.js";

(async () => {
    const consumer = kafka.consumer({ groupId: "test-group" });

    await consumer.connect();

    await consumer.subscribe({
        topic: "logs",
        fromBeginning: true,
    });

    await consumer.run({
        eachMessage: async ({ topic, partition, message }) => {
            console.log("topic:", topic);
            console.log("partition:", partition);
            console.log(
                "message key:",
                message.key !== null ? message.key.toString() : null,
            );
            console.log("message value:", message.value.toString());
        },
    });
})();
