import { Kafka } from "kafkajs";
import os from "os";

export const kafka = new Kafka({
    clientId: "my-app-id",
    brokers: [`${os.hostname()}:9092`],
});
