# ESP32 TTP223 Counter System

Sistema de conteo dual basado en ESP32 utilizando sensores táctiles capacitivos TTP223. Implementa dos contadores independientes con diferentes modos de activación y almacenamiento persistente.

## 🌟 Características Principales

- **Contador A**: Activación por pulsación larga (3 segundos)
- **Contador B**: Activación por pulsaciones múltiples (3 pulsaciones rápidas)
- Almacenamiento persistente en memoria flash
- Estadísticas de uso detalladas
- Interfaz serial para monitoreo y control
- Sistema anti-rebote optimizado
- Documentación completa

## 📁 Estructura del Proyecto

```
ESP32_TTP223_Counter_Project/
├── src/
│   ├── main.cpp           # Código principal
│   ├── config.h          # Configuración del sistema
│   └── statistics.h      # Manejo de estadísticas
├── docs/
│   ├── guides/
│   │   ├── wiring_guide.md    # Guía de conexiones
│   │   └── user_guide.md      # Manual de usuario
│   └── images/               # Diagramas y fotos
├── lib/                     # Bibliotecas adicionales
├── platformio.ini          # Configuración de PlatformIO
└── README.md              # Este archivo
```

## 🛠️ Requisitos

### Hardware
- ESP32 DevKit
- 2x Sensores táctiles TTP223
- Cables de conexión
- Fuente de alimentación 5V/3.3V

### Software
- PlatformIO IDE
- Framework Arduino para ESP32
- Biblioteca Preferences (incluida en ESP32)

## 📦 Instalación

1. **Preparación del Entorno**
   ```bash
   # Clonar el repositorio
   git clone https://github.com/cesaralan23/ESP32_TTP223_Counter_Project.git
   cd ESP32_TTP223_Counter_Project

   # Abrir en PlatformIO
   code .
   ```

2. **Conexiones de Hardware**
   - Seguir la [guía de conexiones](docs/guides/wiring_guide.md)
   - Verificar alimentación y pines

3. **Compilación y Carga**
   - Abrir en PlatformIO
   - Compilar el proyecto
   - Cargar al ESP32

## 💻 Uso

### Operación Básica
1. **Contador A (Pulsación Larga)**
   - Mantener presionado el sensor A por 3 segundos
   - El contador se incrementa al soltar

2. **Contador B (Pulsaciones Múltiples)**
   - Realizar 3 pulsaciones rápidas en el sensor B
   - El contador se incrementa tras la tercera pulsación

### Comandos Seriales
- `reset`: Reinicia ambos contadores
- `stats`: Muestra estadísticas de uso
- `help`: Muestra ayuda de comandos

Para más detalles, consultar la [guía de usuario](docs/guides/user_guide.md).

## 📊 Características Técnicas

### Especificaciones
- Voltaje de operación: 3.3V/5V
- Consumo: ~20mA en reposo
- Tiempo de respuesta: <50ms
- Memoria utilizada: ~4KB flash

### Límites del Sistema
- Valor máximo por contador: 999,999
- Tiempo mínimo entre pulsaciones: 200ms
- Máximo tiempo de pulsación: 10s

## 🔧 Configuración

El archivo `config.h` permite personalizar:
- Pines de los sensores
- Tiempos de respuesta
- Intervalos de reporte
- Modo debug

## 📝 Documentación

- [Guía de Conexiones](docs/guides/wiring_guide.md)
- [Manual de Usuario](docs/guides/user_guide.md)
- [Diagrama de Conexiones](docs/images/wiring_diagram.png)

## 🤝 Contribuciones

1. Fork del proyecto
2. Crear rama para feature (`git checkout -b feature/AmazingFeature`)
3. Commit cambios (`git commit -m 'Add AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abrir Pull Request

## 🐛 Reporte de Problemas

Si encuentras un bug o tienes una sugerencia:
1. Verificar que no exista un issue similar
2. Crear un nuevo issue con:
   - Descripción clara del problema
   - Pasos para reproducirlo
   - Comportamiento esperado
   - Capturas de pantalla si aplica

## 📄 Licencia

Este proyecto está bajo la Licencia MIT. Ver el archivo [LICENSE](LICENSE) para más detalles.

## ✨ Agradecimientos

- Comunidad ESP32
- Contribuidores de Arduino
- Usuarios que reportan problemas y mejoras