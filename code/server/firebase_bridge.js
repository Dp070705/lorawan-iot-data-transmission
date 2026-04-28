
const mqtt = require('mqtt');
const admin = require('firebase-admin');

const serviceAccount = require('./firebase-key.json');//enter the file name with which you stored

admin.initializeApp({
  credential: admin.credential.cert(serviceAccount)
});

const db = admin.firestore();

console.log(" Starting TTN → Firestore bridge...");

// Connect to TTN MQTT
const client = mqtt.connect('mqtt://au1.cloud.thethings.network:1883', {
  username: 'hello1234',//APP ID
  password: 'NNSXS.XVP43BOCT442FOGP7KGNPVC7UY262PT324DWAEI.TMKN3BIZRWOGTD6NO6WFJMFRM34H6C45LJZCLT2BID5CWYTT6RBA'    // <-- Replace with your API key
});

console.log("Connecting to TTN MQTT broker...");

client.on('connect', () => {
  console.log('Connected to TTN MQTT');

  client.subscribe('v3/hello1234@ttn/devices/+/up');
});

client.on('error', (err) => {
  console.error(" MQTT connection error:", err.message);
});


client.on('message', async (topic, message) => {
  console.log(" Raw MQTT message:", message.toString());

  try {
    const payload = JSON.parse(message.toString());
    const deviceId = payload.end_device_ids.device_id;
    const sensorData = payload.uplink_message.decoded_payload;

    console.log(`📡 Data received from ${deviceId}:`, sensorData);

    await db.collection('devices')
      .doc(deviceId)
      .collection('readings')
      .add({
        ...sensorData,
        timestamp: admin.firestore.FieldValue.serverTimestamp()
      });

    console.log(` Saved data for ${deviceId} to Firestore`);
  } catch (err) {
    console.error(" Error parsing message:", err);
  }
});
