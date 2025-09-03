# 🌱 AGROSMART  
**Implementation of Smart Agriculture for Efficient Cultivation in Hilly Regions**  

---

## 📑 Index  

1. [Prototype 1 – Smart Water Sprinkler System](#1️⃣-prototype-1--smart-water-sprinkler-system)  
   - [📸 Project Image](#📸-project-image-1)  
   - [📖 Project Overview](#📖-project-overview-1)  
   - [⚙️ Features](#⚙️-features-1)  
   - [🚀 Operating Modes](#🚀-operating-modes-1)  
   - [🛠️ Components](#🛠️-components-1)  
   - [🔌 Wiring Diagram](#🔌-wiring-diagram-1)  
   - [💻 How to Use](#💻-how-to-use-1)  
   - [💡 Code Overview](#💡-code-overview-1)  
   - [📝 Source Code](#📝-source-code-1)  

2. [Prototype 2 – Agrivyaan: Weather-Based Smart Agriculture System](#2️⃣-prototype-2--agrivyaan-weather-based-smart-agriculture-system)  
   - [📸 Project Image](#📸-project-image-2)  
   - [📖 Problem Statement](#📖-problem-statement-2)  
   - [💡 Solution & SDGs](#💡-solution--sdgs-2)  
   - [🔑 System Description](#🔑-system-description-2)  
   - [✅ Advantages](#✅-advantages-2)  
   - [⚠️ Drawbacks of Existing Systems](#⚠️-drawbacks-of-existing-systems-2)  
   - [🧪 Agrivyaan Levels](#🧪-agrivyaan-levels-2)  
   - [📈 Future Market](#📈-future-market-2)  
   - [📌 Conclusion](#📌-conclusion-2)  
   - [📝 Source Code](#📝-source-code-2)  

---

# 1️⃣ PROTOTYPE 1 – Smart Water Sprinkler System  

---

## 📸 Project Image  
![AGROSMART Prototype 1](Screenshot%202025-09-01%20201059.png)  

---

## 📖 Project Overview  
AGROSMART Prototype 1 is an **Arduino-based smart water sprinkler system** with a simple menu-driven interface on an OLED screen. It allows farmers to control irrigation using a **rotary potentiometer for navigation** and **push buttons for selection**. A buzzer provides audio feedback, and an LED simulates the sprinkler.  

The system offers **three modes of operation**:  
- **Auto Spray** – Set wait and spray times.  
- **Eco Mode** – Spray 1 min every 10 min.  
- **Shutdown** – Disable the system.  

---

## ⚙️ Features  

- 128x32 OLED (SSD1306) display for menu and status.  
- Potentiometer-based navigation.  
- Two push buttons (SELECT & BACK).  
- Buzzer feedback.  
- Menu-driven control.  

---

## 🚀 Operating Modes  

1. **Auto Spray** → Waits for user-defined time, then sprays for set duration.  
2. **Eco Mode** → Sprays for 1 minute every 10 minutes.  
3. **Shutdown** → Turns sprinkler off until manually resumed.  

---

## 🛠️ Components  

- Arduino Uno/Nano  
- OLED Display (SSD1306)  
- Potentiometer  
- 2 Push Buttons (Select & Back)  
- Buzzer  
- LED (sprinkler simulation)  
- Jumper Wires, Breadboard  

---

## 🔌 Wiring Diagram  

| Component        | Pin on Arduino | Description |
|------------------|----------------|-------------|
| OLED Display     | A5 (SCL), A4 (SDA) | I2C pins |
| Potentiometer    | A0 | Analog input |
| LED              | 4  | Output (sprinkler simulation) |
| SELECT Button    | 5  | Input (internal pull-up) |
| BACK Button      | 6  | Input (internal pull-up) |
| Buzzer           | 7  | Digital output |

---

## 💻 How to Use  

1. Upload the Arduino code to your board.  
2. Power on → OLED shows startup message.  
3. Navigate menus with the potentiometer.  
4. Use SELECT to choose options, BACK to exit.  

---

## 💡 Code Overview  

- **setup()** → initializes display, pins, and startup screen.  
- **loop()** → handles menu navigation and operations.  
- **autoSprayMenu()** → allows setting custom wait & spray times.  
- **ecoModeMenu()** → runs Eco mode logic.  
- **shutdownMenu()** → disables sprinkler.  
- **sprayWater()** → simulates irrigation with LED.  
- **beep()** → generates audio feedback.  

---

## 📝 Source Code  

👉 [Prototype 1 Code – agrosmart1.ino](https://github.com/Harikrishnankanjingattu/AGROSMART2/blob/main/agrosmart1.ino)  

---

# 2️⃣ PROTOTYPE 2 – Agrivyaan: Weather-Based Smart Agriculture System  

---

## 📸 Project Image  
![AGROSMART Prototype 2](Screenshot%202025-09-03%20191915.png)  

---

## 📖 Problem Statement  

Farmers in hilly regions such as **Jorethang, South Sikkim** face severe irrigation challenges due to **water scarcity** and **unpredictable rainfall**. Traditional irrigation relies on manual labour and fixed schedules, which often waste water before rainfall or under-irrigate crops during dry spells. These inefficiencies reduce yields, increase labour costs, and make farmers highly vulnerable to climate change.  

---

## 💡 Solution & SDGs  

Agrivyaan addresses this by creating a **Weather-Based Smart Agriculture System**. It integrates **soil moisture and temperature sensors**, **rainwater harvesting systems**, and **real-time weather forecasts** with **Gemini AI crop intelligence**.  

Instead of fixed irrigation schedules, the system evaluates soil moisture, weather predictions, stored water levels, and crop-specific needs before making irrigation decisions. For example:  
- If soil moisture is low but rainfall is predicted, irrigation is skipped.  
- If a heatwave is forecast with low soil moisture, irrigation is triggered early.  

This adaptive approach supports multiple SDGs:  
- **SDG 2 – Zero Hunger** → Higher crop yields.  
- **SDG 6 – Clean Water & Sanitation** → Reduced water wastage.  
- **SDG 12 – Responsible Consumption** → Optimized resource use.  
- **SDG 13 – Climate Action** → Climate-resilient farming.  

---

## 🔑 System Description  

Agrivyaan works as a complete ecosystem. **IoT devices** continuously measure soil moisture and temperature. **Rainwater harvesting tanks** are equipped with ultrasonic sensors to track water levels. **Weather APIs** provide rainfall, humidity, and temperature forecasts.  

All data is fed into **Gemini AI**, which applies crop intelligence to recommend whether to irrigate, how much water to apply, and the method (e.g., drip vs sprinkler). These commands are executed by **Arduino/ESP32 controllers** managing valves and pumps.  

Farmers monitor data via a **dashboard** and receive real-time alerts like:  
- *“Irrigation skipped due to rain forecast.”*  
- *“Irrigation started: 3L per plant.”*  

---

## ✅ Advantages  

- Conserves water by avoiding unnecessary irrigation.  
- Increases yields with precise crop-specific watering.  
- Reduces manual labour through automation.  
- Makes farming resilient to unpredictable weather.  

---

## ⚠️ Drawbacks of Existing Systems  

- Fixed schedules ignore weather conditions.  
- No AI-driven decisions for crops.  
- Lack of rainwater harvesting integration.  
- High water wastage from manual methods.  

---

## 🧪 Agrivyaan Levels  

- **Level 1** → IoT sensors + automation (soil, water level, pumps).  
- **Level 2** → Gemini AI integration for predictive, weather-based irrigation.  

---

## 📈 Future Market  

India will need **70% more food by 2050** (FAO). With growing **water scarcity** and government support for **AgriTech solutions**, smart irrigation systems like Agrivyaan are well positioned for adoption both locally and globally.  

---

## 📌 Conclusion  

Agrivyaan transforms AgroSmart from a simple sprinkler into a **climate-smart irrigation ecosystem**. By combining **IoT sensors, rainwater harvesting, real-time weather, and Gemini AI**, it ensures water is applied **at the right time, in the right amount, using the most sustainable source available**. This enables farmers in regions like South Sikkim to **save water, improve productivity, and achieve sustainable farming**.  

---

## 📝 Source Code  

👉 [Prototype 2 Code – agri2.ino](https://github.com/Harikrishnankanjingattu/AGROSMART2/blob/main/agri2.ino)  

---
