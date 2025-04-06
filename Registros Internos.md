¡Claro! Vamos a desglosar con más detalle estos **registros internos del 6502**, que son clave para entender cómo ejecuta instrucciones paso a paso.

---

## 📦 Registros internos del 6502

Aunque el programador solo ve registros como A, X, Y, SP, PC, el **núcleo del 6502** tiene varios registros **internos y temporales** que la **unidad de control (CU)** usa para gestionar cada ciclo de instrucción.

Aquí están los más relevantes:

---

### 🧠 1. **IR (Instruction Register)**

- **Tamaño**: 8 bits
- **Función**: Guarda el **opcode** de la instrucción que se está ejecutando.
- **Cuándo se usa**: Se carga al comienzo de la instrucción (T0), y su contenido **permanece fijo durante todos los ciclos** de esa instrucción.
- **Ejemplo**: Si la instrucción es `LDA #$05`, el opcode `A9` se guarda en el IR, y la unidad de control lo decodifica para saber qué señales activar.

---

### 🧮 2. **TEMP (o TMP / Temporary Register)**

- **Tamaño**: 8 bits
- **Función**: Guarda **valores intermedios**, usualmente bytes leídos de memoria que todavía no son el destino final.
- **Usos comunes**:
  - Guardar la **dirección base** antes de indexar con X o Y.
  - Almacenar la **parte baja** de una dirección (por ejemplo, en modos indirectos).
- **Ejemplo**: En `LDA ($20),Y`, se usa TEMP para guardar el byte bajo de la dirección leída desde `$20`.

---

### 🏠 3. **ADL / ADH (Address Data Low / High)**

- **Tamaño**: 8 bits cada uno (juntos forman una dirección de 16 bits)
- **Función**: Contienen la dirección efectiva de memoria que se va a acceder para **leer o escribir**.
- **Cómo funciona**:
  - `ADL` guarda el byte **bajo** de la dirección.
  - `ADH` guarda el byte **alto**.
  - Se combinan como: `Dirección = (ADH << 8) | ADL`
- **Ejemplo**: En `LDA $1234`, ADH = `$12`, ADL = `$34`, y se accede a la memoria `$1234`.

---

### 📥 4. **DL (Data Latch / Data Bus Latch)**

- **Tamaño**: 8 bits
- **Función**: Guarda el **dato leído desde memoria**, justo antes de transferirlo a su destino (como A, X, Y, etc.).
- **No lo escribe directamente el programador**.
- **Ejemplo**: En cualquier carga (`LDA`, `LDX`, etc.), el valor final leído de memoria va primero al **DL**, y luego se copia al registro correspondiente.

---

### 🛠️ Diagrama conceptual simplificado

```
[Memoria] → DL → A (acumulador)
        ↑
     [ADH:ADL] (dirección generada a partir de TEMP, X, Y...)
        ↑
       TEMP ← (byte leído como operando o dirección parcial)
        ↑
        IR ← (opcode inicial)
```

---

### 🧩 Ejemplo práctico: `LDA ($20),Y`

Instrucción en memoria:
```
$0600: B1 20     ; LDA ($20),Y
Mem[$0020] = 34
Mem[$0021] = 12
Y = 03
```

**Paso a paso:**

1. `IR ← B1` (opcode)
2. `TEMP ← 20` (operando)
3. Se accede a `$0020`, se lee `$34` → TEMP = 34
4. Se accede a `$0021`, se lee `$12` → Dirección base = `$1234`
5. Se suma Y → Dirección efectiva = `$1237` → se carga en `ADH/ADL`
6. Se accede a `$1237`, se lee el dato → va a `DL`
7. `A ← DL`

---

¿Querés que lo ilustre con otro diagrama visual o paso a paso en estilo tabla? ¿O con una instrucción de escritura como `STA` que usa DL y ADH/ADL en dirección inversa?