# JMP

## 🧠 Convenciones

- `IR`: Instruction Register (opcode actual)  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `tmp`: dirección temporal  
- `[x]`: lectura de memoria  
- `→`: asignación  

---

## 🟡 Cosas importantes sobre `JMP`

- No afecta **ningún flag**
- Salta incondicionalmente al nuevo valor de `PC`
- Tiene dos modos:
  - **Absoluto (`JMP $4400`)**
  - **Indirecto (`JMP ($4400)`)**: importante por un **bug del 6502** que si la dirección base es `$xxFF`, no cruza de página correctamente al leer el byte alto

---

### 🔹 JMP Absoluto — `JMP $4400` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `PC ← tmp_lo | (tmp_hi << 8)` |

---

### 🔹 JMP Indirecto — `JMP ($4400)` — **5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `ptr_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `ptr_hi ← DB`, `PC ← PC + 1` |
| 4     | `ptr ← ptr_lo | (ptr_hi << 8)`, `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 5     | `AB ← (ptr & $FF00) | ((ptr + 1) & $00FF)` ⬅️ *(bug clásico del 6502)*  
|       | `DB ← [AB]`, `tmp_hi ← DB`, `PC ← tmp_lo | (tmp_hi << 8)` |

---

### 🐞 Bug del 6502 en modo indirecto

Si la dirección es `($xxFF)`, el procesador **no** lee el byte alto desde `($xx+1)00`, sino desde `($xx00)`.  
Ejemplo: `JMP ($30FF)` lee el byte alto desde `$3000`, **no** desde `$3100`.

---
