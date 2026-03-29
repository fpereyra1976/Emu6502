Aquí tienes el detalle de la instrucción **`ROL`** (Rotate Left) para el procesador 6502:

---

# ROL — *Rotate Left* (Rotar a la izquierda)

## 🧠 Convenciones

- **`A`**: Acumulador
- **`X`**: Registro X (si se usa en el modo de direccionamiento `ROL X`)
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

### 🔹 ROL Acumulador — `ROL A` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `tmp ← A`, **rotación de A a la izquierda**: `A ← (tmp << 1) | C`, **se actualiza el Carry flag** con el bit 7 de A, `C ← tmp[7]`, **se actualizan los flags Z y N** |

---

### 🔹 ROL Zeropage — `ROL $44` — **5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `tmp ← DB`, **rotación de DB a la izquierda**: `DB ← (tmp << 1) | C`, `C ← tmp[7]` |
| 4     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### 🔹 ROL Zeropage,X — `ROL $44,X` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF`, `AB ← tmp` |
| 4     | `DB ← [AB]`, `tmp ← DB`, **rotación de DB a la izquierda**: `DB ← (tmp << 1) | C`, `C ← tmp[7]` |
| 5     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### 🔹 ROL Absoluto — `ROL $4400` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `tmp ← DB`, **rotación de DB a la izquierda**: `DB ← (tmp << 1) | C`, `C ← tmp[7]` |
| 5     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### 🔹 ROL Absoluto,X — `ROL $4400,X` — **7 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `tmp ← tmp + X`, `AB ← tmp` |
| 5     | `DB ← [AB]`, `tmp ← DB`, **rotación de DB a la izquierda**: `DB ← (tmp << 1) | C`, `C ← tmp[7]` |
| 6     | `Z ← (DB == 0)`, `N ← DB[7]`, **se actualizan los flags Z y N**, `[AB] ← DB` |

---

### Explicación

- **`ROL`** realiza una rotación de los bits hacia la izquierda. El bit 7 de la operación se coloca en el **Carry flag** y el Carry flag anterior se coloca en el bit 0 de la operación.
- En el caso de la versión que usa el acumulador (`ROL A`), el contenido de **A** se rota a la izquierda.
- El **Carry flag (C)** se actualiza con el bit 7 de la operación.
- Los **flags Z** y **N** se actualizan según el valor del resultado:
  - **`Z` (Zero flag)** se establece si el resultado es 0.
  - **`N` (Negative flag)** se establece si el bit 7 (más significativo) del resultado es 1.
- **`ROL`** no afecta el **Overflow flag (V)**.

---

Si necesitas más detalles sobre otra instrucción o tienes alguna pregunta adicional, ¡avísame!