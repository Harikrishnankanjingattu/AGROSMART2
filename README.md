Smart Water Sprinkler System
This project is an Arduino-based smart water sprinkler system with a user interface on an OLED screen. It allows you to control a water sprinkler (represented by an LED) using a rotary potentiometer for navigation and push buttons for selection. The system features three main modes: Auto Spray, Eco Mode, and Shutdown.

⚙️ Features
OLED Display: A 128x32 pixel OLED screen (SSD1306) shows the menu, settings, and status messages.

Menu-Driven Interface: Navigate through different modes using a rotary potentiometer.

User Controls:

Potentiometer: Used to scroll through menu options and adjust settings (e.g., wait and spray times).

SELECT button: Enters a submenu or confirms a setting.

BACK button: Returns to the main menu from a submenu.

Audio Feedback: A buzzer provides distinct tones for button presses and operational status changes.

Operating Modes:

Auto Spray: Set a custom wait time and a custom spray duration in minutes. The system will wait, then spray for the specified time, and finally return to the main menu.

Eco Mode: Automatically sprays water for 1 minute every 10 minutes. This mode continues to run in the background until the BACK button is pressed.

Shutdown: Deactivates all sprinkling functions and turns off the LED. The system remains in this state until the BACK button is pressed.

🛠️ Components
Arduino Board: (e.g., Arduino Uno, Nano)

OLED Display: Adafruit SSD1306 (128x32 I2C)

Potentiometer: A simple rotary potentiometer for input.

Push Buttons: Two push buttons, one for SELECT and one for BACK.

Buzzer: A passive or active buzzer for audio feedback.

LED: An LED to simulate the water sprinkler or pump.

Jumper Wires and Breadboard: To connect all the components.

🔌 Wiring Diagram
Connect the components to the Arduino as follows:

Component	Pin	Description
OLED Display	SCL, SDA	Connect to Arduino's I2C pins (A5, A4 on Uno)
Potentiometer	A0	Analog input for menu navigation and value setting
LED	4	Digital output for the "sprinkler"
SELECT Button	5	Digital input with internal pull-up
BACK Button	6	Digital input with internal pull-up
Buzzer	7	Digital output for tones

Export to Sheets
💻 How to Use
Upload the Code: Connect your Arduino board to your computer and upload the provided code using the Arduino IDE.

Power On: Once powered on, the OLED screen will display "Water Sprinkler" and "Starting...".

Main Menu: The system will then show the main menu with Auto Spray, Eco Mode, and Shutdown.

Navigation:

Use the potentiometer to scroll through the options.

Press the SELECT button to choose a mode.

Setting Modes:

Auto Spray:

Select Auto Spray.

Use the potentiometer to set the WAIT Time in minutes, then press SELECT.

Use the potentiometer again to set the SPRAY Time in minutes, then press SELECT.

The system will wait for the set duration before spraying, then return to the main menu.

Eco Mode:

Select Eco Mode.

The screen will show "Eco Mode ON" and "Every 10 min".

The system will now spray for 1 minute every 10 minutes until you press the BACK button.

Shutdown:

Select Shutdown.

The screen will show "Shutdown Mode" and "Back=exit".

The sprinkler function is disabled, and the LED turns off.

Press the BACK button to exit and return to the main menu.

💡 Code Overview
setup(): Initializes the display, pins, and shows a brief startup message.

loop(): The main function that continuously checks if the user is in the main menu or a submenu and calls the appropriate handler functions.

showMainMenu(): Renders the main menu options on the OLED screen, highlighting the selected item.

handleMenuNavigation(): Reads the potentiometer to update the menuIndex and checks for a press of the SELECT button to enter a submenu.

handleSubMenu(): Manages the logic for each specific menu item and checks for a press of the BACK button.

autoSprayMenu(): Guides the user through setting the wait and spray times using the potentiometer and SELECT button.

ecoModeMenu(): Activates Eco Mode and displays the status on the screen. The main loop handles the timed spraying.

shutdownMenu(): Sets the shutdownMode flag, turns off the LED, and displays the shutdown message.

sprayWater(durationMinutes): A helper function that simulates spraying by turning on the LED and waits for the specified duration before turning it off.

beep(f, d): A simple function to generate a tone on the buzzer with a given frequency (f) and duration (d).
