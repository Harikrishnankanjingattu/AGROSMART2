#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

// Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

// Pin Definitions
#define BUTTON_UP 15
#define BUTTON_SELECT 4
#define BUTTON_BACK 5
#define BUZZER 23
#define LED_PIN 13
#define DIR_PIN 27
#define STEP_PIN 26
#define ENABLE_PIN 25
#define PEST_ALARM_PIN 12

// Stepper Motor Configuration
#define STEPS_PER_REV 200
#define MICROSTEPS 16
#define LEAD_SCREW_PITCH 2.0

// System Parameters
#define TOTAL_LENGTH_CM 21.0
#define PARTITION_COUNT 3
#define PARTITION_LENGTH_CM (TOTAL_LENGTH_CM / PARTITION_COUNT)
#define MOISTURE_THRESHOLD 30

// Moisture Sensor Pins
#define MOISTURE_SENSOR_1 34
#define MOISTURE_SENSOR_2 35
#define MOISTURE_SENSOR_3 32

// Network and API Configuration
const char* ssid = "offline";
const char* password = "raziq2025";
const char* apiKey = "9a73e2999f2ac696e9e8ddb256c1ab4f";
const char* city = "Thrissur";

// Telegram Bot Configuration
#define BOT_TOKEN "7516663328:AAE0BMRYvVAu-AdDYzEthbOLJ11rhG1zhsM"
#define CHAT_ID "5310005938"
const unsigned long BOT_CHECK_INTERVAL = 1000;

// Global Variables
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long lastTimeBotRan;

long totalSteps = 0;
long stepsToPartition = 0;
bool isMoving = true;
int currentMenu = 0;
int totalMenuOptions = 4;
bool inSubMenu = false;
int ecoModeCycles = 1;
bool pestAlarmState = false;
bool exitMenu = false;
bool telegramMode = false;
unsigned long buttonPressTime = 0;
const int BUTTON_PRESS_DURATION = 500;

// Function Declarations
void handleNewMessages(int numNewMessages);
String getSensorData();
void setupWiFi();
void setupDisplay();
void setupPins();

void setup() {
  Serial.begin(115200);
  setupDisplay();
  setupPins();
  setupWiFi();
  
  secured_client.setInsecure(); // For demo purposes
  lastTimeBotRan = millis();
}

void setupDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("Display initialization failed");
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void setupPins() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW);

  pinMode(MOISTURE_SENSOR_1, INPUT);
  pinMode(MOISTURE_SENSOR_2, INPUT);
  pinMode(MOISTURE_SENSOR_3, INPUT);

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_BACK, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PEST_ALARM_PIN, OUTPUT);
}

void setupWiFi() {
  WiFi.begin(ssid, password);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi Connected!");
  display.display();
  delay(1000);
}

String getSensorData() {
  int sensorAnalog1 = readMoisture(MOISTURE_SENSOR_1);
  int sensorAnalog2 = readMoisture(MOISTURE_SENSOR_2);
  int sensorAnalog3 = readMoisture(MOISTURE_SENSOR_3);

  int moisture1 = convertToMoisturePercentage(sensorAnalog1);
  int moisture2 = convertToMoisturePercentage(sensorAnalog2);
  int moisture3 = convertToMoisturePercentage(sensorAnalog3);

  String message = "Sensor Readings:\n";
  message += "Moisture Sensor 1: " + String(moisture1) + "%\n";
  message += "Moisture Sensor 2: " + String(moisture2) + "%\n";
  message += "Moisture Sensor 3: " + String(moisture3) + "%\n";
  message += "Pest Alarm: " + String(pestAlarmState ? "ON" : "OFF") + "\n";
  message += "Eco Mode Cycles: " + String(ecoModeCycles);

  return message;
}
String getWeatherData() {
  HTTPClient http;
  String weatherData;
  http.begin("http://api.openweathermap.org/data/2.5/weather?q=" + String(city) + "&appid=" + String(apiKey) + "&units=metric");
  int httpCode = http.GET();
 
  if (httpCode > 0) {
    weatherData = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, weatherData);

    float temperature = doc["main"]["temp"];
    String weather = doc["weather"][0]["description"];
    bool rain = doc["weather"][0]["main"] == "Rain";

    weatherData = "Temperature: " + String(temperature) + "C\n";
    weatherData += "Weather: " + weather + "\n";
    weatherData += "Rain: " + String(rain ? "Yes" : "No");
  } else {
    weatherData = "Unable to fetch weather data";
  }
  http.end();
  return weatherData;
}

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    if (text == "/getdata") {
      String sensorData = getSensorData();
      String weatherData = getWeatherData();
      String combinedData = sensorData + "\n" + weatherData;
      bot.sendMessage(chat_id, combinedData, "");
    }
  }
}

int readMoisture(int pin) {
  return analogRead(pin);
}

int convertToMoisturePercentage(int sensorValue) {
  return (100 - ((sensorValue / 4095.0) * 100));
}

long calculateStepsForLength(float lengthCm) {
  float distancePerStep = LEAD_SCREW_PITCH / (STEPS_PER_REV * MICROSTEPS);
  long steps = lengthCm / distancePerStep;
  return steps;
}

void moveToPartition(int partition) {
  long stepsToMove = 0;
 
  if (partition == 1) {
    stepsToMove = calculateStepsForLength(PARTITION_LENGTH_CM);
    digitalWrite(DIR_PIN, HIGH);
  } else if (partition == 2) {
    stepsToMove = calculateStepsForLength(PARTITION_LENGTH_CM * 2);
    digitalWrite(DIR_PIN, HIGH);
  } else if (partition == 3) {
    stepsToMove = calculateStepsForLength(PARTITION_LENGTH_CM * 3);
    digitalWrite(DIR_PIN, HIGH);
  }

  stepsToPartition = stepsToMove;  // Global assignment

  for (long i = 0; i < stepsToMove; i++) {
    if (!isMoving) {
      return;
    }
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);
  }

  delay(10000);
}

void returnToStart() {
  digitalWrite(DIR_PIN, LOW);  
  for (long i = 0; i < stepsToPartition; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000);
  }
}

void checkAndActOnMoistureLevels() {
  int sensorAnalog1 = readMoisture(MOISTURE_SENSOR_1);
  int sensorAnalog2 = readMoisture(MOISTURE_SENSOR_2);
  int sensorAnalog3 = readMoisture(MOISTURE_SENSOR_3);

  int moisture1 = convertToMoisturePercentage(sensorAnalog1);
  int moisture2 = convertToMoisturePercentage(sensorAnalog2);
  int moisture3 = convertToMoisturePercentage(sensorAnalog3);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Moisture 1: ");
  display.print(moisture1);
  display.println("%");

  display.print("Moisture 2: ");
  display.print(moisture2);
  display.println("%");

  display.print("Moisture 3: ");
  display.print(moisture3);
  display.println("%");

  display.display();

  if (moisture1 < MOISTURE_THRESHOLD) {
    moveToPartition(1);
    returnToStart();
  }
  if (moisture2 < MOISTURE_THRESHOLD) {
    moveToPartition(2);
    returnToStart();
  }
  if (moisture3 < MOISTURE_THRESHOLD) {
    moveToPartition(3);
    returnToStart();
  }
}

void displayWeather() {
  HTTPClient http;
  String weatherData;
  http.begin("http://api.openweathermap.org/data/2.5/weather?q=" + String(city) + "&appid=" + String(apiKey) + "&units=metric");
  int httpCode = http.GET();
 
  if (httpCode > 0) {
    weatherData = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, weatherData);

    float temperature = doc["main"]["temp"];
    String weather = doc["weather"][0]["description"];
    bool rain = doc["weather"][0]["main"] == "Rain";

    weatherData = "Temperature: " + String(temperature) + "C\n";
    weatherData += "Weather: " + weather + "\n";
    weatherData += "Rain: " + String(rain ? "Yes" : "No");

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Temp: ");
    display.print(temperature);
    display.println("C");

    display.print("Weather: ");
    display.println(weather);

    display.print("Rain: ");
    display.println(rain ? "Yes" : "No");

    display.display();
  }
  http.end();
}

void displayMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.print("  Moisture");
  display.setCursor(0, 8);
  display.print("  Weather");
  display.setCursor(0, 16);
  display.print("  Eco Mode");
  display.setCursor(0, 24);
  display.print("  pest&check");

  display.setCursor(0, currentMenu * 8);
  display.print("> ");
 
  display.display();
}

void beepBuzzer() {
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(100);
}

void loop() {
  // Check for Telegram mode activation/deactivation
  if (digitalRead(BUTTON_BACK) == LOW) {
    if (millis() - buttonPressTime > BUTTON_PRESS_DURATION) {
      telegramMode = !telegramMode;
      buttonPressTime = millis();
      
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println(telegramMode ? "Telegram Mode ON" : "Telegram Mode OFF");
      display.display();
      beepBuzzer();
      delay(1000);
    }
  } else {
    buttonPressTime = millis();
  }

  // Only check Telegram messages when in Telegram mode
  if (telegramMode) {
    if (millis() - lastTimeBotRan > BOT_CHECK_INTERVAL) {
      int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      if (numNewMessages) {
        handleNewMessages(numNewMessages);
      }
      lastTimeBotRan = millis();
    }
  }

  // Regular menu operation when not in Telegram mode
  if (!telegramMode) {
    displayMenu();

  if (digitalRead(BUTTON_UP) == LOW) {
    currentMenu = (currentMenu + 1) % totalMenuOptions;
    beepBuzzer();
    delay(200);
  }

  if (digitalRead(BUTTON_SELECT) == LOW) {
    if (currentMenu == 0) {
      checkAndActOnMoistureLevels();
    } else if (currentMenu == 1) {
      displayWeather();
      while (digitalRead(BUTTON_BACK) != LOW) {
        delay(100);  
      }
      beepBuzzer();
    } else if (currentMenu == 2) {
      ecoModeCycles = 1;
      while (!exitMenu) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Select cycles (1-7): ");
        display.print(ecoModeCycles);
        display.display();
        
        if (digitalRead(BUTTON_UP) == LOW && ecoModeCycles < 7) {
          ecoModeCycles++;
          delay(200);
        }

        if (digitalRead(BUTTON_SELECT) == LOW) {
          int remainingCycles = ecoModeCycles;
          while (remainingCycles > 0) {
            moveToPartition(1);
            returnToStart();
            moveToPartition(2);
            returnToStart();
            moveToPartition(3);
            returnToStart();
            remainingCycles--;
          }
          break;
        }
        delay(100);
      }
    } else if (currentMenu == 3) {
      int sensorAnalog1 = readMoisture(MOISTURE_SENSOR_1);
      int sensorAnalog2 = readMoisture(MOISTURE_SENSOR_2);
      int sensorAnalog3 = readMoisture(MOISTURE_SENSOR_3);

      int moisture1 = convertToMoisturePercentage(sensorAnalog1);
      int moisture2 = convertToMoisturePercentage(sensorAnalog2);
      int moisture3 = convertToMoisturePercentage(sensorAnalog3);

      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Pest Alarm: ");
      display.println(pestAlarmState ? "ON" : "OFF");

      if (moisture1 < MOISTURE_THRESHOLD) {
        display.setCursor(0, 8);
        display.print("M1 is low!");
      }
      if (moisture2 < MOISTURE_THRESHOLD) {
        display.setCursor(0, 16);
        display.print("M2 is low!");
      }
      if (moisture3 < MOISTURE_THRESHOLD) {
        display.setCursor(0, 24);
        display.print("M3 is low!");
      }

      display.display();

      if (digitalRead(BUTTON_SELECT) == LOW) {
        pestAlarmState = !pestAlarmState;
        if (pestAlarmState) {
          digitalWrite(12, HIGH);  // Start continuous buzzer sound on GPIO12
          digitalWrite(LED_PIN, HIGH);  // Turn on the LED on pin 13
        } else {
          digitalWrite(12, LOW);   // Stop buzzer sound on GPIO12
          digitalWrite(LED_PIN, LOW);  // Turn off the LED on pin 13
        }
        beepBuzzer();
        delay(200);
      }
      
      while (digitalRead(BUTTON_BACK) != LOW) {
        delay(100);
      }
      beepBuzzer();
    }
    beepBuzzer();
    delay(200);
  }

  if (digitalRead(BUTTON_BACK) == LOW) {
    if (currentMenu == 3 || currentMenu == 1) {
      exitMenu = false;
    } else {
      exitMenu = true;
    }
    currentMenu = 0;
    beepBuzzer();
    delay(200);
  }

  delay(100);
}}

