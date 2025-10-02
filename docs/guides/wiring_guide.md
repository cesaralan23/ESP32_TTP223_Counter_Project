# Guía de Conexiones - ESP32 TTP223 Counter

## Diagrama de Conexiones

```
+-------------+     +-------------+
|   ESP32     |     |   TTP223   |
|             |     | Sensor A    |
| 3.3V    ----+-----+ VCC        |
| GND     ----+-----+ GND        |
| GPIO2   ----+-----+ OUT        |
+-------------+     +-------------+

+-------------+     +-------------+
|   ESP32     |     |   TTP223   |
|             |     | Sensor B    |
| 3.3V    ----+-----+ VCC        |
| GND     ----+-----+ GND        |
| GPIO4   ----+-----+ OUT        |
+-------------+     +-------------+
```

## Componentes Necesarios

- 1x ESP32 DevKit
- 2x Sensores táctiles capacitivos TTP223
- Cables de conexión
- (Opcional) Protoboard para montaje

## Pines Utilizados

| Pin ESP32 | Conexión        | Descripción                    |
|-----------|----------------|--------------------------------|
| GPIO2     | Sensor A (OUT) | Sensor de pulsación larga      |
| GPIO4     | Sensor B (OUT) | Sensor de pulsaciones múltiples |
| 3.3V      | VCC (ambos)   | Alimentación de los sensores    |
| GND       | GND (ambos)   | Tierra común                    |

## Instrucciones de Conexión

1. **Alimentación de los Sensores**
   - Conecta el pin VCC de ambos sensores TTP223 al pin 3.3V del ESP32
   - Conecta el pin GND de ambos sensores al pin GND del ESP32

2. **Conexión del Sensor A (Pulsación Larga)**
   - Conecta el pin OUT del primer sensor TTP223 al GPIO2 del ESP32
   - Este sensor se usará para la función de pulsación larga

3. **Conexión del Sensor B (Pulsaciones Múltiples)**
   - Conecta el pin OUT del segundo sensor TTP223 al GPIO4 del ESP32
   - Este sensor se usará para la función de pulsaciones múltiples

## Notas Importantes

- Los sensores TTP223 son activos en ALTO (HIGH)
- Los sensores funcionan con 3.3V, compatible directamente con el ESP32
- No es necesario usar resistencias pull-up/down, los sensores tienen resistencias internas
- La distancia máxima recomendada entre el ESP32 y los sensores es de 20cm para evitar interferencias

## Verificación de Conexiones

1. **Comprobación de Alimentación**
   - El LED de poder en los sensores TTP223 debe encenderse
   - Si no enciende, verifica las conexiones de VCC y GND

2. **Prueba de Sensores**
   - Al tocar cada sensor, su LED indicador debe encenderse
   - Si no responde, verifica la conexión del pin OUT correspondiente

## Solución de Problemas

| Problema | Posible Causa | Solución |
|----------|---------------|----------|
| Sensor no responde | Mala conexión VCC/GND | Verificar alimentación |
| Lecturas erráticas | Cables muy largos | Acortar cables o usar blindados |
| Falsos positivos | Interferencia | Alejar de fuentes de ruido eléctrico |

## Recomendaciones

1. Usar cables cortos para las conexiones
2. Mantener los sensores alejados de superficies metálicas
3. Si es posible, usar una protoboard para un montaje más estable
4. Considerar el uso de una caja protectora para el montaje final