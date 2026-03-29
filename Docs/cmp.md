# CMP

## 🧠 Convenciones

- `IR`: Instruction Register (opcode actual)  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `tmp`: dirección temporal intermedia  
- `A`: Acumulador  
- `C`, `Z`, `N`: Flags de estado  
- `[x]`: lectura de memoria  
- `→`: asignación  
- `cmp_val ← A - DB` (solo para flags, no se guarda)  

---

## 🟡 Cosas importantes sobre `CMP`

- Afecta los flags:  
  - `C` (Carry) se activa si `A ≥ DB`  
  - `Z` se activa si `A == DB`  
  - `N` se activa si el bit 7 del resultado (`A - DB`) es 1  
- **NO modifica el acumulador**
- El cálculo es similar a `SBC`, pero **sin** modificar `A`.

---

### 🔹 CMP Inmediato — `CMP #$10` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`, `cmp_val ← A - DB`, `set_flags(cmp_val)` |

---

### 🔹 CMP Zeropage — `CMP $44` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `cmp_val ← A - DB`, `set_flags(cmp_val)` |

---

### 🔹 CMP Zeropage,X — `CMP $44,X` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF`, `AB ← tmp` |
| 4     | `DB ← [AB]`, `cmp_val ← A - DB`, `set_flags(cmp_val)` |

---

### 🔹 CMP Absoluto — `CMP $4400` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `cmp_val ← A - DB`, `set_flags(cmp_val)` |

---

### 🔹 CMP Absoluto,X — `CMP $4400,X` — **4/5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `tmp ← tmp + X`, `AB ← tmp` |
| 5*    | `DB ← [AB]`, `cmp_val ← A - DB`, `set_flags(cmp_val)` |

> *El 5° ciclo solo ocurre si hay cruce de página*

---

### 🔹 CMP Absoluto,Y — `CMP $4400,Y` — **4/5 ciclos**

> Igual que el anterior, pero con `Y`.

---

### 🔹 CMP Indirecto,X — `CMP ($20,X)` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `zp_base ← DB`, `PC ← PC + 1` |
| 3     | `ptr ← (zp_base + X) & $FF`, `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `AB ← tmp`, `DB ← [AB]` |
| 6     | `cmp_val ← A - DB`, `set_flags(cmp_val)` |

---

### 🔹 CMP Indirecto,Y — `CMP ($20),Y` — **5/6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `ptr ← DB`, `PC ← PC + 1` |
| 3     | `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `tmp ← tmp + Y`, `AB ← tmp` |
| 6*    | `DB ← [AB]`, `cmp_val ← A - DB`, `set_flags(cmp_val)` |

> *El 6° ciclo ocurre si hay cruce de página*

---
