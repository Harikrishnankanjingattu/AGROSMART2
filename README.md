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

2. [Prototype 2 – Smart Agriculture with Water Monitoring & Rainwater Harvesting](#2️⃣-prototype-2--smart-agriculture-with-water-monitoring--rainwater-harvesting)  
   - [📖 Background](#📖-background-2)  
   - [💡 Proposed Solution](#💡-proposed-solution-2)  
   - [🎯 Impact](#🎯-impact-2)  
   - [📈 Conclusion](#📈-conclusion-2)  

---

# 1️⃣ PROTOTYPE 1 – Smart Water Sprinkler System  

---

## 📸 Project Image  
![AGROSMART Prototype](Screenshot%202025-09-01%20201059.png)  

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
- **beep(f, d)** → generates buzzer tone at a given frequency and duration.  

---

# 2️⃣ PROTOTYPE 2 – Smart Agriculture with Water Monitoring & Rainwater Harvesting  

---

## 📖 Background  

The agricultural region of **Jorethang in South Sikkim** experiences **harsh, rainless summers** and frequent **water scarcity**, making traditional irrigation unreliable and inefficient. Farmers struggle to provide adequate water to crops, often leading to **reduced yields** and **wasted resources**.  

With **climate change intensifying** these issues, there is a pressing need for a **sustainable, smart irrigation approach** that maximizes water efficiency and crop productivity. Integrating **rainwater harvesting, sensor-based monitoring, and crop-specific intelligence** offers a forward-thinking solution to these regional challenges.  

---

## 💡 Proposed Solution  

**AgroSmart: A Sensor-Based Smart Irrigation System with Crop Intelligence and Rainwater Harvesting**  

The system provides affordable, automated irrigation tailored to each crop’s needs using **soil moisture and environmental sensors**. It integrates a **rainwater harvesting unit with real-time water level monitoring**, ensuring efficient water use even during dry periods.  

### Solution Highlights  
- 🌱 **Soil moisture & temperature sensors** → monitor real-time field conditions.  
- 📊 **Crop database** → determines optimal watering levels for each crop.  
- 🔧 **Automated valve control** → managed by microcontrollers (Arduino/ESP32).  
- 💧 **Rainwater harvesting with level sensors** → track stored water availability.  
- 📱 **Mobile/Web dashboard** → allows farmers to monitor data and control irrigation remotely.  
- 🔔 **Alerts & updates** → SMS or app notifications to keep farmers informed.  

---

## 🎯 Impact  

- 🌍 **Conserves water** → reduces wastage through precision irrigation.  
- 🌾 **Improves crop yields** → ensures crops get the right amount of water.  
- 🤖 **Reduces manual labour** → minimizes dependency on constant field monitoring.  
- 🌦️ **Adaptation to climate change** → resilient system for uncertain weather.  
- 🔄 **Self-sustaining** → integrates renewable rainwater harvesting into irrigation.  

---

## 📈 Conclusion  

**Prototype 2** enhances the basic water sprinkler idea into a **complete smart irrigation ecosystem** tailored for hilly regions like South Sikkim. By combining **IoT-based monitoring, rainwater harvesting, and crop intelligence**, AgroSmart empowers farmers to **increase productivity sustainably** while addressing **water scarcity challenges**.  

---
