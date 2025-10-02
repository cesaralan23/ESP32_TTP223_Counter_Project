# Contador Táctil con ESP32

Sistema de contador utilizando el sensor táctil TTP223 y ESP32. Implementación de interfaz táctil para aplicaciones de control de acceso.

## Características principales

- Interfaz táctil capacitiva
- Contador con persistencia
- Conectividad WiFi para monitoreo
- Bajo consumo de energía

## Requisitos

- PlatformIO IDE
- ESP32 DevKit
- Sensor táctil TTP223

## Instalación

1. Clona este repositorio
2. Abre el proyecto en PlatformIO
3. Conecta tu ESP32
4. Compila y sube el código

## Uso

El sistema inicia automáticamente después de la programación. El sensor táctil TTP223 detectará toques y el contador se incrementará. Los valores se mantienen incluso después de un reinicio.

## Estructura del Proyecto

```
ESP32_TTP223_Counter_Project/
├── src/
│   └── main.cpp          # Código principal
├── platformio.ini        # Configuración de PlatformIO
└── README.md            # Este archivo
```

## Licencia

Este proyecto está bajo la Licencia MIT.