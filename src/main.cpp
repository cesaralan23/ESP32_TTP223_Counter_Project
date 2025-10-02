#include <Arduino.h>
#include <Preferences.h>
#include "config.h"
#include "statistics.h"

/**
 * ESP32 TTP223 Dual Counter System
 * 
 * Este sistema implementa dos contadores independientes utilizando sensores táctiles TTP223:
 * - Contador A: Se incrementa con una pulsación larga (3 segundos)
 * - Contador B: Se incrementa con múltiples pulsaciones rápidas (3 pulsaciones en 1 segundo)
 * 
 * Características:
 * - Persistencia de datos usando NVS
 * - Estadísticas de uso
 * - Sistema anti-rebote
 * - Reportes periódicos
 * - Comandos por serial
 */

// Objeto para almacenamiento no volátil
Preferences preferences;

// Contadores principales
long counterA = 0;
long counterB = 0;

// Objeto para estadísticas
CounterStatistics stats;

// Variables para Sensor A (Pulsación Larga)
unsigned long touchA_pressStartTime = 0;
bool touchA_pressed = false;

// Variables para Sensor B (Pulsaciones Múltiples)
unsigned long lastTouchB_time = 0;
int touchB_pressCount = 0;

// Control de tiempo para salida serial
unsigned long lastPrintTime = 0;

/**
 * Guarda los contadores en la memoria NVS
 * @return true si el guardado fue exitoso
 */
bool saveCounters() {
    if (counterA > MAX_COUNTER_VALUE || counterB > MAX_COUNTER_VALUE) {
        if (DEBUG_MODE) Serial.println("Error: Valor de contador excede el máximo");
        return false;
    }
    
    preferences.putLong(COUNTER_A_KEY, counterA);
    preferences.putLong(COUNTER_B_KEY, counterB);
    
    if (DEBUG_MODE) Serial.println("Contadores guardados en NVS.");
    return true;
}

/**
 * Carga los contadores desde la memoria NVS
 */
void loadCounters() {
    counterA = preferences.getLong(COUNTER_A_KEY, 0);
    counterB = preferences.getLong(COUNTER_B_KEY, 0);
    
    if (DEBUG_MODE) {
        Serial.print("Contador A cargado: ");
        Serial.println(counterA);
        Serial.print("Contador B cargado: ");
        Serial.println(counterB);
    }
}

/**
 * Reinicia los contadores y las estadísticas
 */
void resetCounters() {
    preferences.clear();
    counterA = 0;
    counterB = 0;
    stats.reset();
    Serial.println("Contadores y estadísticas reiniciados.");
    saveCounters();
}

/**
 * Imprime el estado actual de los contadores
 */
void printCounters() {
    Serial.println("\n=== Estado Actual ===");
    Serial.print("Contador A: ");
    Serial.println(counterA);
    Serial.print("Contador B: ");
    Serial.println(counterB);
    Serial.println("==================");
}

/**
 * Procesa los comandos recibidos por serial
 */
void processSerialCommands() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        
        if (command.equalsIgnoreCase("reset")) {
            resetCounters();
            printCounters();
        }
        else if (command.equalsIgnoreCase("stats")) {
            stats.printStats();
        }
        else if (command.equalsIgnoreCase("help")) {
            Serial.println("\nComandos disponibles:");
            Serial.println("- reset: Reinicia contadores y estadísticas");
            Serial.println("- stats: Muestra estadísticas de uso");
            Serial.println("- help: Muestra esta ayuda");
        }
    }
}

void setup() {
    // Inicialización de comunicación serial
    Serial.begin(SERIAL_BAUD_RATE);
    
    // Configuración de pines
    pinMode(TOUCH_SENSOR_A_PIN, INPUT);
    pinMode(TOUCH_SENSOR_B_PIN, INPUT);

    // Inicialización de almacenamiento
    preferences.begin(NVS_NAMESPACE, false);
    loadCounters();

    // Mensaje de bienvenida
    Serial.println("\nESP32 TTP223 Counter System");
    Serial.println("==========================");
    Serial.println("Sensor A (Pin " + String(TOUCH_SENSOR_A_PIN) + "): Pulsación larga de 3 segundos");
    Serial.println("Sensor B (Pin " + String(TOUCH_SENSOR_B_PIN) + "): 3 pulsaciones rápidas");
    Serial.println("Comandos: 'reset', 'stats', 'help'");
    Serial.println("==========================");
    
    printCounters();
    lastPrintTime = millis();
}

void loop() {
    // Procesamiento de Sensor A (Pulsación Larga)
    if (digitalRead(TOUCH_SENSOR_A_PIN) == HIGH) {
        if (!touchA_pressed) {
            touchA_pressStartTime = millis();
            touchA_pressed = true;
            if (DEBUG_MODE) Serial.println("Sensor A: Presionado.");
        }
        else if (millis() - touchA_pressStartTime >= LONG_PRESS_DURATION) {
            if (counterA < MAX_COUNTER_VALUE) {
                counterA++;
                stats.recordLongPress();
                Serial.print("Sensor A: ¡Pulsación larga detectada! Contador A: ");
                Serial.println(counterA);
                saveCounters();
                printCounters();
            }
            touchA_pressed = false;
        }
    }
    else if (touchA_pressed) {
        if (millis() - touchA_pressStartTime < LONG_PRESS_DURATION) {
            if (DEBUG_MODE) Serial.println("Sensor A: Pulsación muy corta.");
            stats.recordFailedLongPress();
        }
        touchA_pressed = false;
    }

    // Procesamiento de Sensor B (Pulsaciones Múltiples)
    if (digitalRead(TOUCH_SENSOR_B_PIN) == HIGH) {
        if (millis() - lastTouchB_time > DEBOUNCE_TIME || touchB_pressCount == 0) {
            touchB_pressCount++;
            lastTouchB_time = millis();
            if (DEBUG_MODE) {
                Serial.print("Sensor B: Pulsación detectada. Contador: ");
                Serial.println(touchB_pressCount);
            }

            if (touchB_pressCount >= REQUIRED_PRESSES) {
                if (counterB < MAX_COUNTER_VALUE) {
                    counterB++;
                    stats.recordMultiPress();
                    Serial.print("Sensor B: ¡Secuencia completada! Contador B: ");
                    Serial.println(counterB);
                    saveCounters();
                    printCounters();
                }
                touchB_pressCount = 0;
            }
        }
    }
    else if (touchB_pressCount > 0 && millis() - lastTouchB_time > MULTI_PRESS_INTERVAL) {
        if (DEBUG_MODE) Serial.println("Sensor B: Timeout de secuencia.");
        stats.recordFailedMultiPress();
        touchB_pressCount = 0;
    }

    // Impresión periódica de estado
    if (millis() - lastPrintTime >= PRINT_INTERVAL) {
        printCounters();
        lastPrintTime = millis();
    }

    // Guardado periódico de estadísticas
    if (ENABLE_STATISTICS && stats.shouldSave()) {
        stats.printStats();
        stats.markSaved();
    }

    // Procesamiento de comandos seriales
    processSerialCommands();

    // Pequeña pausa para estabilidad
    delay(50);
}