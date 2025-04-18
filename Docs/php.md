# PHP — *Push Processor Status*

## 📋 Descripción

La instrucción `PHP` empuja (guarda) el contenido del registro de estado `P` en la pila. Muy útil antes de cambiar banderas para luego restaurarlas con `PLP`.

---

## 🧠 Convenciones

- **`PC`**: Program Counter  
- **`IR`**: Instruction Register  
- **`DB`**: Data Bus  
- **`AB`**: Address Bus  
- **`SP`**: Stack Pointer (8 bits)  
- **`P`**: Registro de estado  
- **Stack base**: `$0100`

---

## 🟡 Cosas importantes sobre `PHP`

- El byte empujado contiene todas las banderas (`NV-BDIZC`)
- El bit 4 (Break) y bit 5 (Unused) se fijan a `1` al ser empujados (aunque no estén activos en `P`)
- No afecta ningún flag directamente
- Consume **3 ciclos**

---

## 🕒 Ciclos

### 🔹 `PHP` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | (Preparación de la pila, sin efecto externo visible) |
| 3     | `AB ← $0100 | SP`, `DB ← P | $30` (set bits 4 y 5), `[AB] ← DB`, `SP ← SP - 1` |

---
