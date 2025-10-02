# Guía de Usuario - ESP32 TTP223 Counter

## Descripción General

Este proyecto implementa un sistema de conteo dual utilizando dos sensores táctiles TTP223 conectados a un ESP32. Cada sensor tiene una función específica:

- **Sensor A**: Contador activado por pulsación larga (3 segundos)
- **Sensor B**: Contador activado por pulsaciones múltiples (3 pulsaciones rápidas)

## Características Principales

- Dos contadores independientes
- Persistencia de datos (los contadores se mantienen después de reinicios)
- Interfaz serial para monitoreo y control
- Diferentes modos de activación para cada contador
- Sistema anti-rebote incorporado
- Reportes periódicos del estado

## Uso del Sistema

### Inicialización

1. Al encender el sistema:
   - Los contadores se cargan desde la memoria
   - Se muestra el estado inicial en el monitor serial
   - El sistema está listo para usar inmediatamente

### Operación del Sensor A (Pulsación Larga)

1. **Activación**:
   - Mantén presionado el sensor A durante 3 segundos
   - Un mensaje confirmará la detección de la pulsación larga
   - El contador A se incrementará en 1

2. **Indicaciones**:
   - Pulsación detectada: "Sensor A: Pressed"
   - Pulsación muy corta: "Sensor A: Press too short"
   - Contador incrementado: "Sensor A: Long press detected!"

### Operación del Sensor B (Pulsaciones Múltiples)

1. **Activación**:
   - Realiza 3 pulsaciones rápidas en menos de 1 segundo
   - Cada pulsación será confirmada en el monitor
   - El contador B se incrementará después de la tercera pulsación

2. **Indicaciones**:
   - Pulsación detectada: "Sensor B: Press detected"
   - Timeout: "Sensor B: Multi-press timeout"
   - Contador incrementado: "Sensor B: Multiple presses detected!"

### Monitor Serial

- **Velocidad**: 115200 baudios
- **Comandos disponibles**:
  - `reset`: Reinicia ambos contadores a 0

### Reportes Automáticos

El sistema muestra automáticamente:
- Estado de los contadores cada 5 segundos
- Confirmación después de cada incremento
- Mensajes de error o timeout
- Confirmación de guardado en memoria

## Especificaciones Técnicas

### Tiempos y Duraciones

- Pulsación larga (Sensor A): 3 segundos
- Intervalo múltiples pulsaciones (Sensor B): 1 segundo
- Pulsaciones requeridas (Sensor B): 3 pulsaciones
- Intervalo de reporte automático: 5 segundos
- Debounce time: 200ms

### Almacenamiento

- Tipo: NVS (Non-Volatile Storage)
- Namespace: "my-app"
- Variables almacenadas:
  - counterA: Contador de pulsaciones largas
  - counterB: Contador de pulsaciones múltiples

## Solución de Problemas

### Problemas Comunes

1. **No se detectan pulsaciones**
   - Verificar conexiones físicas
   - Comprobar alimentación de los sensores
   - Revisar la guía de conexiones

2. **Pulsaciones erráticas**
   - Verificar distancia de cables
   - Alejar de fuentes de interferencia
   - Comprobar voltaje de alimentación

3. **Contadores no se guardan**
   - Verificar mensajes de error en serial
   - Reiniciar el dispositivo
   - Como último recurso, usar comando 'reset'

### Mensajes de Error

| Mensaje | Significado | Acción Recomendada |
|---------|-------------|-------------------|
| "Press too short" | Pulsación A insuficiente | Mantener presionado más tiempo |
| "Multi-press timeout" | Pulsaciones B muy lentas | Realizar pulsaciones más rápidas |
| "Counters saved to NVS" | Guardado exitoso | Ninguna acción necesaria |

## Mantenimiento

### Recomendaciones

1. **Limpieza**
   - Mantener los sensores limpios
   - Evitar humedad excesiva
   - No usar limpiadores conductivos

2. **Verificación Periódica**
   - Comprobar funcionamiento mensualmente
   - Verificar lecturas de los sensores
   - Revisar conexiones físicas

3. **Actualización**
   - Verificar GitHub para nuevas versiones
   - Seguir guía de actualización
   - Hacer backup de los contadores

## Personalización

El sistema puede personalizarse modificando las siguientes constantes en el código:

```cpp
const long LONG_PRESS_DURATION = 3000;    // Duración pulsación larga
const long MULTI_PRESS_INTERVAL = 1000;   // Intervalo múltiples pulsaciones
const int REQUIRED_PRESSES = 3;           // Número de pulsaciones requeridas
const long PRINT_INTERVAL = 5000;         // Intervalo de reporte
```

## Soporte

Para soporte adicional:
1. Consultar la documentación en GitHub
2. Revisar issues existentes
3. Crear un nuevo issue con:
   - Descripción detallada del problema
   - Mensajes de error
   - Pasos para reproducir el error