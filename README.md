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

2. [Prototype 2 – Agrivyaan: Smart Agriculture System](#2️⃣-prototype-2--agrivyaan-smart-agriculture-system)  
   - [📸 Project Image](#📸-project-image-2)  
   - [📖 Problem Statement](#📖-problem-statement-2)  
   - [💡 Solution & SDGs](#💡-solution--sdgs-2)  
   - [🔑 Key Features](#🔑-key-features-2)  
   - [⚙️ System Functions](#⚙️-system-functions-2)  
   - [✅ Advantages](#✅-advantages-2)  
   - [⚠️ Drawbacks of Existing Systems](#⚠️-drawbacks-of-existing-systems-2)  
   - [🧪 Agrivyaan Levels](#🧪-agrivyaan-levels-2)  
   - [📈 Future Market](#📈-future-market-2)  
   - [📌 Conclusion](#📌-conclusion-2)  

---

# 1️⃣ PROTOTYPE 1 – Smart Water Sprinkler System  

---

## 📸 Project Image  
![AGROSMART Prototype 1](Screenshot%202025-09-01%20201059.png)  

---

## 📖 Project Overview  
AGROSMART is an **Arduino-based smart water sprinkler system** with a **user interface on an OLED screen**. It allows you to control a water sprinkler (represented by an LED) using a **rotary potentiometer for navigation** and **push buttons for selection**.  

The system features three main modes:  
- **Auto Spray**  
- **Eco Mode**  
- **Shutdown**  

---

## ⚙️ Features  

- **OLED Display**: A 128x32 pixel OLED screen (SSD1306) shows the menu, settings, and status messages.  
- **Menu-Driven Interface**: Navigate through modes using a rotary potentiometer.  
- **User Controls**:  
  - Potentiometer → scroll through menu options & adjust values.  
  - SELECT button → enter/confirm selections.  
  - BACK button → return to the main menu.  
- **Audio Feedback**: Buzzer provides tones for button presses & mode changes.  

---

## 🚀 Operating Modes  

### 1. Auto Spray  
- Set custom **WAIT Time** (minutes).  
- Set custom **SPRAY Time** (minutes).  
- System waits, sprays for set time, then returns to menu.  

### 2. Eco Mode  
- Automatically sprays for **1 minute every 10 minutes**.  
- Runs in the background until **BACK button** is pressed.  

### 3. Shutdown  
- Disables all sprinkler functions.  
- LED turns off.  
- Exit with BACK button.  

---

## 🛠️ Components  

- Arduino Board (Uno/Nano)  
- OLED Display (SSD1306, 128x32 I2C)  
- Potentiometer  
- SELECT & BACK Push Buttons  
- Buzzer (active/passive)  
- LED (simulating sprinkler)  
- Jumper Wires & Breadboard  

---

## 🔌 Wiring Diagram  

| Component        | Pin on Arduino | Description |
|------------------|----------------|-------------|
| OLED Display     | A5 (SCL), A4 (SDA) | I2C pins |
| Potentiometer    | A0 | Analog input for menu navigation |
| LED              | 4  | Output for sprinkler simulation |
| SELECT Button    | 5  | Digital input with internal pull-up |
| BACK Button      | 6  | Digital input with internal pull-up |
| Buzzer           | 7  | Digital output for tones |

---

## 💻 How to Use  

1. **Upload Code** via Arduino IDE.  
2. On startup → OLED shows *“Water Sprinkler”* → *“Starting...”*.  
3. Navigate with **Potentiometer** & select with **Buttons**.  
4. Modes:  
   - Auto Spray → set Wait & Spray times.  
   - Eco Mode → sprays 1 min / 10 min.  
   - Shutdown → sprinkler off.  

---

## 💡 Code Overview  

- **setup()** → initializes OLED, pins, and startup message.  
- **loop()** → checks current mode & runs handler functions.  
- **showMainMenu()** → draws main menu on OLED.  
- **handleMenuNavigation()** → updates menu index based on potentiometer.  
- **handleSubMenu()** → executes logic for selected mode.  
- **autoSprayMenu()** → lets user set wait & spray times.  
- **ecoModeMenu()** → manages timed spraying.  
- **shutdownMenu()** → disables sprinkler.  
- **sprayWater(durationMinutes)** → turns LED on/off for given duration.  
- **beep(f, d)** → generates buzzer tone.  

---

# 2️⃣ PROTOTYPE 2 – Agrivyaan: Smart Agriculture System  

---

## 📸 Project Image  
![AGROSMART Prototype 2](Screenshot%202025-09-03%20191915.png)  

---

## 📖 Problem Statement  

Traditional farming suffers from:  
- 🌊 **Inefficient water management**  
- 🌱 **Limited plant & soil monitoring**  
- 📉 **Low productivity & high resource wastage**  
- ❌ **No integration of rainwater harvesting or climate resilience**  

Farmers lack **real-time insights**, **remote control**, and **sustainability measures** to adapt to climate challenges.  

---

## 💡 Solution & SDGs  

**Agrivyaan is a Smart Agriculture System** integrating IoT, AI, and automation to optimize cultivation.  

- **SDG 2 – Zero Hunger** → Improves yield & food security.  
- **SDG 6 – Clean Water & Sanitation** → Reduces irrigation water wastage by up to 40%.  
- **SDG 12 – Responsible Consumption** → Optimizes water use.  
- **SDG 13 – Climate Action** → Enables sustainable farming.  

---

## 🔑 Key Features  

- 🌱 **AI-driven Smart Farming**  
- 📊 **Real-time monitoring & daily AI reports**  
- 💧 **Precision irrigation using soil moisture sensors**  
- ☁️ **Cloud & Offline Support**  
- 📷 **Optional camera-based analysis for crop monitoring**  
- 🔔 **Remote monitoring & alerts via mobile app**  
- ♻️ **Rainwater harvesting with water-level monitoring**  

---

## ⚙️ System Functions  

- **Soil Moisture & Temperature Monitoring**  
- **AI-based Crop Intelligence** for irrigation recommendations  
- **Automated Pump/Valve Control** (ESP32/Arduino)  
- **Rainwater Harvesting Unit** with storage level sensors  
- **Farmer Dashboard (Web/App)** for visualization and control  
- **SMS/Push Alerts** for irrigation status & warnings  

---

## ✅ Advantages  

- Conserves water (up to 40% reduction in wastage)  
- Improves crop yield & resource efficiency  
- Enables climate-resilient farming  
- Reduces labour & manual effort  
- Provides **real-time data-driven decisions**  

---

## ⚠️ Drawbacks of Existing Systems  

- No AI-based analysis  
- Fixed irrigation schedules  
- No rainwater harvesting integration  
- Limited offline/remote support  

---

## 🧪 Agrivyaan Levels  

### **Level 1**  
- ESP32 + Sensors (moisture, temperature, ultrasonic, PIR)  
- Automated irrigation + monitoring  
- Cloud connectivity with farmer alerts  

### **Level 2**  
- **AI Integration (Gemini AI/LLM)**  
- Soil moisture readings processed via AI  
- AI suggests irrigation quantity & method  
- Automated system executes commands + notifies farmer  

---

## 📈 Future Market  

- 🇮🇳 India needs **70% more food by 2050** (FAO).  
- 🌊 Growing **water scarcity & sustainability demand**.  
- 💰 Government subsidies & **AgriTech adoption programs**.  
- 📈 Rising global demand for **precision farming solutions**.  

---

## 📌 Conclusion  

**Prototype 2 (Agrivyaan)** transforms farming from **basic automation (Prototype 1)** into a **comprehensive AI + IoT ecosystem**. By combining:  

- **IoT sensors**  
- **AI-driven decision making**  
- **Rainwater harvesting & water-level monitoring**  

it enables farmers in regions like **South Sikkim** to **conserve water, increase productivity, and achieve sustainable agriculture**.  

---
