# ROR — *Rotate Right* (Rotar a la derecha)

## 🧠 Convenciones

- **`A`**: Acumulador
- **`X`**: Registro X (si se usa en el modo de direccionamiento `ROR X`)
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

### 🔹 ROR Acumulador — `ROR A` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `tmp ← A`, **rotación de A a la derecha**: `A ← (tmp >> 1) | (C << 7)`, **se actualiza el Carry flag** con el bit 0 de A, `C ← tmp[0]`, **se actualizan los flags Z y N** |

---

### 🔹 ROR Zeropage — `ROR $44` — **5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `tmp ← DB`, **rotación de DB a la derecha**: `DB ← (tmp >> 1) | (C << 7)`, `C ← tmp[0]` |
| 4     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### 🔹 ROR Zeropage,X — `ROR $44,X` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF`, `AB ← tmp` |
| 4     | `DB ← [AB]`, `tmp ← DB`, **rotación de DB a la derecha**: `DB ← (tmp >> 1) | (C << 7)`, `C ← tmp[0]` |
| 5     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### 🔹 ROR Absoluto — `ROR $4400` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `tmp ← DB`, **rotación de DB a la derecha**: `DB ← (tmp >> 1) | (C << 7)`, `C ← tmp[0]` |
| 5     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### 🔹 ROR Absoluto,X — `ROR $4400,X` — **7 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `tmp ← tmp + X`, `AB ← tmp` |
| 5     | `DB ← [AB]`, `tmp ← DB`, **rotación de DB a la derecha**: `DB ← (tmp >> 1) | (C << 7)`, `C ← tmp[0]` |
| 6     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### Explicación

- **`ROR`** realiza una rotación de los bits hacia la derecha. El bit 0 de la operación se coloca en el **Carry flag** y el Carry flag anterior se coloca en el bit 7 de la operación.
- En el caso de la versión que usa el acumulador (`ROR A`), el contenido de **A** se rota a la derecha.
- El **Carry flag (C)** se actualiza con el bit 0 de la operación.
- Los **flags Z** y **N** se actualizan según el valor del resultado:
  - **`Z` (Zero flag)** se establece si el resultado es 0.
  - **`N` (Negative flag)** se establece si el bit 7 (más significativo) del resultado es 1.
- **`ROR`** no afecta el **Overflow flag (V)**.

---
