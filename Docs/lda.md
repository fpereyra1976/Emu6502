# LDA

- Lectura y escritura de buses (`AB`, `DB`)
- Incrementos de `PC`
- Carga de registros (`IR`, `tmp`, `A`)
- Verificación de cruce de página si aplica
- Afectación de flags `Z` y `N`

---

## 🧠 Convenciones

- `IR`: Instruction Register (opcode actual)
- `PC`: Program Counter
- `DB`: Data Bus
- `AB`: Address Bus
- `tmp`: registro temporal (dirección intermedia, 16 bits)
- `[x]`: significa lectura desde memoria (e.g. `[PC]` = contenido de memoria en dirección `PC`)
- `→` = asignación
- Flags: se actualizan al final con `Z` (Zero) y `N` (Negative)

---

### 🟢 LDA Inmediato — `LDA #$10` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `A ← DB`, `PC ← PC + 1`, actualizar flags Z y N |

---

### 🟢 LDA Zeropage — `LDA $44` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `A ← DB`, actualizar flags Z y N |

---

### 🟢 LDA Zeropage,X — `LDA $44,X` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF` (wrap en zeropage), `AB ← tmp` |
| 4     | `DB ← [AB]`, `A ← DB`, actualizar flags Z y N |

---

### 🟢 LDA Absoluto — `LDA $4400` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `A ← DB`, actualizar flags Z y N |

---

### 🟢 LDA Absoluto,X — `LDA $4400,X` — **4 o 5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `tmp_sum ← tmp + X`, `AB ← tmp_sum`, si `page(tmp) ≠ page(tmp_sum)` → agregar ciclo extra |
| 5*    | (si cruce de página) `DB ← [AB]`, `A ← DB`, actualizar flags Z y N |
| 4*    | (si no hay cruce) `DB ← [AB]`, `A ← DB`, actualizar flags Z y N |

---

### 🟢 LDA Absoluto,Y — Igual que Absoluto,X pero con `Y`

---

### 🟢 LDA Indirecto,X — `LDA ($20,X)` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `zp_base ← DB`, `PC ← PC + 1` |
| 3     | `ptr ← (zp_base + X) & $FF`, `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `AB ← tmp` |
| 6     | `DB ← [AB]`, `A ← DB`, actualizar flags Z y N |

---

### 🟢 LDA Indirecto,Y — `LDA ($20),Y` — **5 o 6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `ptr ← DB`, `PC ← PC + 1` |
| 3     | `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `tmp_sum ← tmp + Y`, `AB ← tmp_sum`, si `page(tmp) ≠ page(tmp_sum)` → agregar ciclo extra |
| 6*    | (si cruce de página) `DB ← [AB]`, `A ← DB`, actualizar flags Z y N |
| 5*    | (si no hay cruce) `DB ← [AB]`, `A ← DB`, actualizar flags Z y N |

---