#ifndef STATISTICS_H
#define STATISTICS_H

#include <Arduino.h>
#include "config.h"

class CounterStatistics {
private:
    // Statistics for Sensor A
    unsigned long totalLongPresses;
    unsigned long failedLongPresses;
    unsigned long lastLongPressTime;
    
    // Statistics for Sensor B
    unsigned long totalMultiPresses;
    unsigned long failedMultiPresses;
    unsigned long lastMultiPressTime;
    
    // General statistics
    unsigned long startTime;
    unsigned long lastSaveTime;

public:
    CounterStatistics() {
        reset();
    }

    void reset() {
        totalLongPresses = 0;
        failedLongPresses = 0;
        totalMultiPresses = 0;
        failedMultiPresses = 0;
        startTime = millis();
        lastSaveTime = startTime;
        lastLongPressTime = 0;
        lastMultiPressTime = 0;
    }

    // Record successful long press
    void recordLongPress() {
        totalLongPresses++;
        lastLongPressTime = millis();
    }

    // Record failed long press
    void recordFailedLongPress() {
        failedLongPresses++;
    }

    // Record successful multi press
    void recordMultiPress() {
        totalMultiPresses++;
        lastMultiPressTime = millis();
    }

    // Record failed multi press
    void recordFailedMultiPress() {
        failedMultiPresses++;
    }

    // Get runtime in hours
    float getRuntimeHours() {
        return (millis() - startTime) / 3600000.0;
    }

    // Get success rate for long presses
    float getLongPressSuccessRate() {
        float total = totalLongPresses + failedLongPresses;
        return total > 0 ? (totalLongPresses * 100.0) / total : 0;
    }

    // Get success rate for multi presses
    float getMultiPressSuccessRate() {
        float total = totalMultiPresses + failedMultiPresses;
        return total > 0 ? (totalMultiPresses * 100.0) / total : 0;
    }

    // Print statistics
    void printStats() {
        Serial.println("\n=== Estadísticas de Uso ===");
        Serial.print("Tiempo de ejecución: ");
        Serial.print(getRuntimeHours(), 2);
        Serial.println(" horas");
        
        Serial.println("\nSensor A (Pulsación Larga):");
        Serial.print("- Pulsaciones exitosas: ");
        Serial.println(totalLongPresses);
        Serial.print("- Pulsaciones fallidas: ");
        Serial.println(failedLongPresses);
        Serial.print("- Tasa de éxito: ");
        Serial.print(getLongPressSuccessRate(), 1);
        Serial.println("%");
        
        Serial.println("\nSensor B (Pulsaciones Múltiples):");
        Serial.print("- Secuencias exitosas: ");
        Serial.println(totalMultiPresses);
        Serial.print("- Secuencias fallidas: ");
        Serial.println(failedMultiPresses);
        Serial.print("- Tasa de éxito: ");
        Serial.print(getMultiPressSuccessRate(), 1);
        Serial.println("%");
        
        Serial.println("=========================");
    }

    // Check if it's time to save statistics
    bool shouldSave() {
        return (millis() - lastSaveTime) >= STATS_SAVE_INTERVAL;
    }

    // Mark statistics as saved
    void markSaved() {
        lastSaveTime = millis();
    }
};

#endif // STATISTICS_H