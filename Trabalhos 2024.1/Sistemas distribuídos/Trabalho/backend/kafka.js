const {Kafka} = require("kafkajs")

const kafka = new Kafka({
    clientId: 'wss',
    brokers: [process.env.KAFKA_BOOTSTRAP_SERVER]
})

module.exports = kafka