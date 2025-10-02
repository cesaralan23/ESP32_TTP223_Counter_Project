#ifndef CONFIG_H
#define CONFIG_H

// Pin Configuration
const int TOUCH_SENSOR_A_PIN = 2;     // Sensor for long press detection
const int TOUCH_SENSOR_B_PIN = 4;     // Sensor for multiple press detection

// Timing Configuration (all values in milliseconds)
const long LONG_PRESS_DURATION = 3000; // Duration required for long press (3 seconds)
const long MULTI_PRESS_INTERVAL = 1000;// Window for multiple presses (1 second)
const long PRINT_INTERVAL = 5000;      // Status print interval (5 seconds)
const long DEBOUNCE_TIME = 200;        // Debounce time for button presses

// Counter Configuration
const int REQUIRED_PRESSES = 3;        // Number of presses required for counter B
const long MAX_COUNTER_VALUE = 999999; // Maximum value for counters

// Storage Configuration
const char* NVS_NAMESPACE = "my-app";  // Namespace for NVS storage
const char* COUNTER_A_KEY = "counterA";// Storage key for counter A
const char* COUNTER_B_KEY = "counterB";// Storage key for counter B

// Statistics Configuration
const bool ENABLE_STATISTICS = true;   // Enable/disable statistics tracking
const long STATS_SAVE_INTERVAL = 3600000; // Save stats every hour (3600000ms)

// Debug Configuration
#define DEBUG_MODE true                // Enable/disable debug messages
#define SERIAL_BAUD_RATE 115200       // Serial communication speed

#endif // CONFIG_H