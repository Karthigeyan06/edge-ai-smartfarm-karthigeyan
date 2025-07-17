# 🌱 Smart Farming IoT System – ESP32 + MQTT

This project is a Smart Farming IoT solution built using **ESP32**, **DHT11 sensor**, **soil moisture sensor**, and **MQTT** protocol. It reads environmental data and sends it to a dashboard (e.g., Node-RED or MQTT broker).


---

## 🚀 Features

- 📡 ESP32 reads soil moisture and temperature/humidity data
- ☁️ Sends data to MQTT broker (`broker.hivemq.com`)
- 📊 Compatible with dashboards like Node-RED for live display
- 🔁 Runs every 10 seconds to update values

---

## 🔧 Hardware Used

| Component             | Pin Connection (ESP32) |
|----------------------|------------------------|
| DHT11 Sensor          | GPIO4                  |
| Soil Moisture Sensor  | GPIO34 (ADC1_CH6)      |
| ESP32 Dev Board       | WiFi + ADC             |

---

## 🧠 Software Stack

- **ESP-IDF (Embedded C Framework)**
- **MQTT Protocol**
- **Node-RED / MQTT Dashboard (client)**
- **FreeRTOS**

---

## 📦 Dependencies

Install ESP-IDF and add the DHT driver (`dht.c`, `dht.h`) to your `components` folder or `main` directory.

- Install ESP-IDF: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/

---

## 📁 Project Structure

smart_farming/
├── CMakeLists.txt
├── sdkconfig
├── main/
│ ├── smart_farming.c
│ ├── CMakeLists.txt
│ ├── dht.c
│ └── dht.h

yaml
Copy
Edit

---

## ⚙️ Configuration

Edit your Wi-Fi credentials in `smart_farming.c`:

```c
#define WIFI_SSID "your_wifi_name"
#define WIFI_PASS "your_wifi_password"
Set your MQTT broker URI (default is HiveMQ):

c
Copy
Edit
#define BROKER_URI "mqtt://broker.hivemq.com"
📲 How It Works
ESP32 connects to Wi-Fi

Reads data from:

Soil moisture sensor (analog value)

DHT11 sensor (temp and humidity)

Publishes the data to farm/data topic on MQTT broker

Node-RED or any MQTT dashboard can subscribe and display it

💡 Sample MQTT Payload
json
Copy
Edit
{
  "soil": 1580,
  "temp": 27,
  "hum": 64
}
📷 System Architecture
csharp
Copy
Edit
[Sensors]
   ↓
[ESP32 → Wi-Fi]
   ↓
[MQTT Broker (HiveMQ)]
   ↓
[Dashboard (Node-RED)]
🧪 Testing
Use MQTT Explorer to test MQTT messages

Use Node-RED to build dashboard with mqtt in and gauge nodes

🧑‍💻 Author
Karthigeyan06 – Final Year Embedded IoT Project

Smart Farming using Edge IoT, Embedded C, and MQTT

📝 License
This project is for educational purposes under an open license. Feel free to modify or extend it!

yaml
Copy
Edit

---

Let me know if you'd like a matching **architecture diagram**, or the **Node-RED flow**, or if you're working with **Buildroot/Yocto** for dashboard/Gateway side.

Shall I also give you `dht.c` and `dht.h` driver files next?
