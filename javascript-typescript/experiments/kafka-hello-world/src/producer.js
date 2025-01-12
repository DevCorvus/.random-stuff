import { kafka } from "./kafka.js";

const message = process.argv[2];

(async () => {
    const producer = kafka.producer();
    await producer.connect();

    await producer.send({
        topic: "logs",
        messages: [{ value: message }],
    });

    await producer.disconnect();
})();
