#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define POT_PIN A0
#define LED_PIN 4
#define SELECT_BTN 5
#define BACK_BTN 6
#define BUZZER_PIN 7

String menuItems[] = {"Auto Spray", "Eco Mode", "Shutdown"};
int menuIndex = 0;
const int totalMenus = 3;

bool inSubMenu = false;
int currentMenu = -1;
bool ecoModeActive = false;
bool shutdownMode = false;

const unsigned long ECO_INTERVAL_MS = 600000UL;
const unsigned int ECO_SPRAY_DURATION_MIN = 1;
unsigned long lastSprayTime = 0;

// Auto Spray variables
int waitTime = 1;
int sprayTime = 1;
int autoSprayStep = 0;

void showMainMenu();
void handleMenuNavigation();
void handleSubMenu();
void autoSprayMenu();
void ecoModeMenu();
void shutdownMenu();
void sprayWater(unsigned int durationMinutes);
void beep(unsigned int f, unsigned int d);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SELECT_BTN, INPUT_PULLUP);
  pinMode(BACK_BTN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1) {}
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(8, 10);
  display.println("Water Sprinkler");
  display.setCursor(22, 20);
  display.println("Starting...");
  display.display();
  delay(1200);
}

void loop() {
  if (!inSubMenu) {
    showMainMenu();
    handleMenuNavigation();
  } else {
    handleSubMenu();
  }

  if (!shutdownMode && ecoModeActive && (millis() - lastSprayTime >= ECO_INTERVAL_MS)) {
    sprayWater(ECO_SPRAY_DURATION_MIN);
    lastSprayTime = millis();
  }
}

void showMainMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("== Mode ==");

  for (int i = 0; i < totalMenus; i++) {
    if (i == menuIndex) display.setTextColor(BLACK, WHITE);
    else display.setTextColor(WHITE);
    display.setCursor(0, 10 + i * 10);
    display.println(menuItems[i]);
  }
  display.display();
}

void handleMenuNavigation() {
  int potValue = analogRead(POT_PIN);
  menuIndex = map(potValue, 0, 1023, 0, totalMenus - 1);

  if (digitalRead(SELECT_BTN) == LOW) {
    beep(1000, 120);
    delay(200);
    inSubMenu = true;
    currentMenu = menuIndex;
    autoSprayStep = 0;
  }
}

void handleSubMenu() {
  if (digitalRead(BACK_BTN) == LOW) {
    beep(800, 120);
    ecoModeActive = false;
    shutdownMode = false;
    inSubMenu = false;
    delay(200);
    return;
  }

  switch (currentMenu) {
    case 0: autoSprayMenu(); break;
    case 1: ecoModeMenu(); break;
    case 2: shutdownMenu(); break;
  }
}

void autoSprayMenu() {
  if (autoSprayStep == 0) {
    waitTime = map(analogRead(POT_PIN), 0, 1023, 1, 30);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Set WAIT Time:");
    display.setCursor(0, 12);
    display.print(waitTime);
    display.println(" min");
    display.display();

    if (digitalRead(SELECT_BTN) == LOW) {
      beep(1200, 120);
      delay(200);
      autoSprayStep = 1;
    }
  } else if (autoSprayStep == 1) {
    sprayTime = map(analogRead(POT_PIN), 0, 1023, 1, 30);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Set SPRAY Time:");
    display.setCursor(0, 12);
    display.print(sprayTime);
    display.println(" min");
    display.display();

    if (digitalRead(SELECT_BTN) == LOW) {
      beep(1300, 120);
      delay(200);
      autoSprayStep = 2;
      unsigned long waitMs = (unsigned long)waitTime * 60000UL;

      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Waiting...");
      display.display();

      delay(waitMs);
      sprayWater((unsigned int)sprayTime);
      inSubMenu = false;
    }
  }
}

void ecoModeMenu() {
  if (!ecoModeActive) {
    ecoModeActive = true;
    lastSprayTime = millis();
    beep(900, 100);
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Eco Mode ON");
  display.setCursor(0, 12);
  display.println("Every 10 min");
  display.display();
}

void shutdownMenu() {
  shutdownMode = true;
  ecoModeActive = false;
  digitalWrite(LED_PIN, LOW);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Shutdown Mode");
  display.setCursor(0, 12);
  display.println("Back=exit");
  display.display();
}

void sprayWater(unsigned int durationMinutes) {
  if (shutdownMode) return;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Spraying...");
  display.display();

  digitalWrite(LED_PIN, HIGH);
  beep(1500, 150);

  unsigned long ms = (unsigned long)durationMinutes * 60000UL;
  delay(ms);

  digitalWrite(LED_PIN, LOW);
  beep(600, 250);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Done!");
  display.display();
  delay(600);
}

void beep(unsigned int f, unsigned int d) {
  tone(BUZZER_PIN, f, d);
}
