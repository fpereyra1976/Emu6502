# ASL — *Arithmetic Shift Left* (Desplazamiento aritmético a la izquierda)

## 🧠 Convenciones

- **`A`**: Acumulador
- **`X`**: Registro X (si se usa en el modo de direccionamiento `ASL X`)
- **`IR`**: Instruction Register (opcode actual)
- **`PC`**: Program Counter
- **`DB`**: Data Bus
- **`AB`**: Address Bus
- **`tmp`**: Dirección temporal (cuando se trata de un operando de memoria)
- **`C`**: Carry flag (se actualiza)
- **`Z`**: Zero flag (se actualiza)
- **`N`**: Negative flag (se actualiza)
- **`V`**: Overflow flag (no se ve afectado)

---

### 🔹 ASL Acumulador — `ASL A` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `tmp ← A`, **desplazamiento de A a la izquierda**: `A ← tmp << 1`, `C ← tmp[7]`, **se actualiza el Carry flag** y **se ajustan los flags Z y N** |

---

### 🔹 ASL Zeropage — `ASL $44` — **5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `tmp ← DB`, **desplazamiento de DB a la izquierda**: `DB ← tmp << 1`, `C ← tmp[7]` |
| 4     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### 🔹 ASL Zeropage,X — `ASL $44,X` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF`, `AB ← tmp` |
| 4     | `DB ← [AB]`, `tmp ← DB`, **desplazamiento de DB a la izquierda**: `DB ← tmp << 1`, `C ← tmp[7]` |
| 5     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### 🔹 ASL Absoluto — `ASL $4400` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `tmp ← DB`, **desplazamiento de DB a la izquierda**: `DB ← tmp << 1`, `C ← tmp[7]` |
| 5     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### 🔹 ASL Absoluto,X — `ASL $4400,X` — **7 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `tmp ← tmp + X`, `AB ← tmp` |
| 5     | `DB ← [AB]`, `tmp ← DB`, **desplazamiento de DB a la izquierda**: `DB ← tmp << 1`, `C ← tmp[7]` |
| 6     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### Explicación

- **`ASL`** realiza un desplazamiento a la izquierda de un byte (8 bits), y este proceso equivale a multiplicar el valor por 2.
- En el caso de la versión que usa el acumulador (`ASL A`), el contenido de **A** se desplaza a la izquierda. El bit de acarreo **C** se actualiza con el bit 7 de la operación.
- Los flags **Z** y **N** se actualizan según el valor del resultado:
  - **`Z` (Zero flag)** se establece si el resultado es 0.
  - **`N` (Negative flag)** se establece si el bit 7 (más significativo) del resultado es 1.
- **`ASL`** no afecta el **Overflow flag (V)**.

---
