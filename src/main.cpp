#include <Arduino.h>
#include <Preferences.h>

// Define pins for TTP223 sensors
const int TOUCH_SENSOR_A_PIN = 2; // Example pin for Sensor A (long press)
const int TOUCH_SENSOR_B_PIN = 4; // Example pin for Sensor B (multiple presses)

// Preferences namespace
Preferences preferences;

// Counters
long counterA = 0;
long counterB = 0;

// Sensor A (Long Press) variables
unsigned long touchA_pressStartTime = 0;
bool touchA_pressed = false;
const long LONG_PRESS_DURATION = 3000; // 3 seconds

// Sensor B (Multiple Presses) variables
unsigned long lastTouchB_time = 0;
int touchB_pressCount = 0;
const long MULTI_PRESS_INTERVAL = 1000; // 1 second for multiple presses
const int REQUIRED_PRESSES = 3;

// Variables for serial output timing
unsigned long lastPrintTime = 0;
const long PRINT_INTERVAL = 5000; // Print every 5 seconds

void saveCounters() {
  preferences.putLong("counterA", counterA);
  preferences.putLong("counterB", counterB);
  Serial.println("Counters saved to NVS.");
}

void loadCounters() {
  counterA = preferences.getLong("counterA", 0);
  counterB = preferences.getLong("counterB", 0);
  Serial.print("Loaded Counter A: ");
  Serial.println(counterA);
  Serial.print("Loaded Counter B: ");
  Serial.println(counterB);
}

void resetCounters() {
  preferences.clear(); // Clear all keys in the namespace
  counterA = 0;
  counterB = 0;
  Serial.println("Counters reset to 0.");
  saveCounters(); // Save the reset state immediately
}

void printCounters() {
  Serial.println("\n--- Current Counters ---");
  Serial.print("Counter A: ");
  Serial.println(counterA);
  Serial.print("Counter B: ");
  Serial.println(counterB);
  Serial.println("------------------------");
}

void setup() {
  Serial.begin(115200);
  pinMode(TOUCH_SENSOR_A_PIN, INPUT);
  pinMode(TOUCH_SENSOR_B_PIN, INPUT);

  preferences.begin("my-app", false); // Open NVS namespace
  loadCounters();

  Serial.println("\nESP32 TTP223 Counter Ready!");
  Serial.println("----------------------------");
  Serial.println("Sensor A (Pin " + String(TOUCH_SENSOR_A_PIN) + "): Long press for 3 seconds to increment.");
  Serial.println("Sensor B (Pin " + String(TOUCH_SENSOR_B_PIN) + "): Press 3 times within 1 second to increment.");
  Serial.println("Type 'reset' in Serial Monitor to clear counters.");
  Serial.println("----------------------------");
  printCounters(); // Initial print of counters
  lastPrintTime = millis();
}

void loop() {
  // Sensor A (Long Press) Logic
  if (digitalRead(TOUCH_SENSOR_A_PIN) == LOW) { // Sensor A is active HIGH, so LOW means not touched
    if (touchA_pressed) {
      touchA_pressed = false;
      // If released before long press, reset timer
      if (millis() - touchA_pressStartTime < LONG_PRESS_DURATION) {
        Serial.println("Sensor A: Press too short.");
      }
    }
  } else { // Sensor A is touched (HIGH)
    if (!touchA_pressed) {
      touchA_pressStartTime = millis();
      touchA_pressed = true;
      Serial.println("Sensor A: Pressed.");
    } else if (millis() - touchA_pressStartTime >= LONG_PRESS_DURATION) {
      if (touchA_pressed) { // Ensure it's still pressed
        counterA++;
        Serial.print("Sensor A: Long press detected! Counter A: ");
        Serial.println(counterA);
        saveCounters();
        printCounters(); // Print after update
        touchA_pressed = false; // Reset for next long press
      }
    }
  }

  // Sensor B (Multiple Presses) Logic
  if (digitalRead(TOUCH_SENSOR_B_PIN) == LOW) { // Sensor B is active HIGH, so LOW means not touched
    // Reset multiple press count if no press within interval
    if (touchB_pressCount > 0 && millis() - lastTouchB_time > MULTI_PRESS_INTERVAL) {
      Serial.println("Sensor B: Multi-press timeout. Resetting count.");
      touchB_pressCount = 0;
    }
  }
  else { // Sensor B is touched (HIGH)
    if (millis() - lastTouchB_time > 200 || touchB_pressCount == 0) { // Debounce or first press
      touchB_pressCount++;
      lastTouchB_time = millis();
      Serial.print("Sensor B: Press detected. Count: ");
      Serial.println(touchB_pressCount);

      if (touchB_pressCount >= REQUIRED_PRESSES) {
        counterB++;
        Serial.print("Sensor B: Multiple presses detected! Counter B: ");
        Serial.println(counterB);
        saveCounters();
        printCounters(); // Print after update
        touchB_pressCount = 0; // Reset for next multiple press
      }
    }
  }

  // Periodically print counters
  if (millis() - lastPrintTime >= PRINT_INTERVAL) {
    printCounters();
    lastPrintTime = millis();
  }

  // Handle serial input for reset command
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove any whitespace
    if (command.equalsIgnoreCase("reset")) {
      resetCounters();
      printCounters(); // Print after reset
    }
  }

  delay(50); // Small delay to prevent excessive looping
}