# EOR — *Exclusive OR with Accumulator* (Exclusive OR con el acumulador)

## 🧠 Convenciones

- **`A`**: Acumulador
- **`IR`**: Instruction Register (opcode actual)
- **`PC`**: Program Counter
- **`DB`**: Data Bus
- **`AB`**: Address Bus
- **`tmp`**: Dirección temporal
- **`Z`**: Zero flag
- **`N`**: Negative flag
- **`V`**: Overflow flag
- **`C`**: Carry flag (no se ve afectado por `EOR`)

---

### 🔹 EOR Zeropage — `EOR $44` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← [PC]`, `DB ← [AB]`, `PC ← PC + 1` |
| 3     | `A ← A ^ DB`, `Z ← (A == 0)`, `N ← (A >> 7)` |

---

### 🔹 EOR Zeropage,X — `EOR $44,X` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← [PC]`, `DB ← [AB]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF`, `AB ← tmp`, `DB ← [AB]` |
| 4     | `A ← A ^ DB`, `Z ← (A == 0)`, `N ← (A >> 7)` |

---

### 🔹 EOR Absoluto — `EOR $4400` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp_lo | (DB << 8)`, `DB ← [AB]` |
| 4     | `A ← A ^ DB`, `Z ← (A == 0)`, `N ← (A >> 7)` |

---

### 🔹 EOR Absoluto,X — `EOR $4400,X` — **5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `tmp ← tmp + X`, `AB ← tmp`, `DB ← [AB]` |
| 5     | `A ← A ^ DB`, `Z ← (A == 0)`, `N ← (A >> 7)` |

---

### 🔹 EOR Indirecto,X — `EOR ($20,X)` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← [PC]`, `DB ← [AB]`, `zp_base ← DB`, `PC ← PC + 1` |
| 3     | `ptr ← (zp_base + X) & $FF`, `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `AB ← tmp`, `DB ← [AB]` |
| 6     | `A ← A ^ DB`, `Z ← (A == 0)`, `N ← (A >> 7)` |

---

### 🔹 EOR Indirecto,Y — `EOR ($20),Y` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← [PC]`, `DB ← [AB]`, `ptr ← DB`, `PC ← PC + 1` |
| 3     | `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `tmp ← tmp + Y`, `AB ← tmp`, `DB ← [AB]` |
| 6     | `A ← A ^ DB`, `Z ← (A == 0)`, `N ← (A >> 7)` |

---

En la instrucción `EOR`, se realiza una operación lógica de "Exclusive OR" (XOR) entre el acumulador (`A`) y el operando leído desde la memoria. Luego, los **flags** de **Zero** y **Negative** se actualizan en base al resultado de la operación.

El **flag de Zero** se establece si el resultado de la operación es 0, y el **flag de Negative** se establece en el bit más significativo (bit 7) del resultado.
