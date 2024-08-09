const WebSocket = require('ws');

// let connections = 0;

const kafka = require('./kafka');

const topic = 'updates'
const consumer = kafka.consumer({ groupId: process.env.GROUP_ID })
const producer = kafka.producer({ allowAutoTopicCreation: true });

const run = async () => {
  await producer.connect()
  await consumer.connect()
  await consumer.subscribe({ topic, fromBeginning: true })
  await consumer.run({
    eachMessage: async ({ topic, partition, message }) => {
        const prefix = `${topic}[${partition} | ${message.offset}] / ${message.timestamp}`;
        console.log(`- ${prefix} ${message.key}#${message.value}`);

        if(message.key !== process.env.GROUP_ID) {
            wss.clients.forEach(client => {
                client.readyState === WebSocket.OPEN && client.send((message.value));
            });
        }
    },
  })
}

const send_message = async (data) => {
    await producer.send({
        topic: topic,
        messages:[{
            key: process.env.GROUP_ID, value: data.toString()
        }]
    });
    console.log(data.toString());
};

const wss = new WebSocket.Server({ port: process.env.PORT || 8082 });

run();

wss.on("connection", (ws, req) => {
    // connections++;
    console.log("New connection from " + req.socket.remoteAddress + req.socket.remotePort);
    
    // if(connections === 1) run().catch(e => console.error(`[example/consumer] ${e.message}`, e))

    ws.on("close", (ws, reason) => {
        console.log("Client disconnected: " + req.socket.remoteAddress + reason);
        // connections--;
        // if(connections === 0) {
        //     try {
        //         consumer.disconnect();
        //         producer.disconnect();
        //     } catch(e) {
        //         console.log(`Something went wrong: ${e.message}`);
        //     }
        // }
    });

    ws.on("message",  (data) => {
        try {
            // await producer.send({
            //     topic: topic,
            //     messages:{
            //         key: 'key1', value: data
            //     }
            // })
            send_message(data);
            wss.clients.forEach(client => {
                client.readyState === WebSocket.OPEN && client.send((data));
            });
        } catch(e) {
            console.log(`Something went wrong with the message: ${e.message}`);
        }
    });
});