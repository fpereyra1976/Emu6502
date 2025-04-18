# CPY

## 🧠 Convenciones

- `IR`: Instruction Register (opcode actual)  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `Y`: Registro Y  
- `cmp_val ← Y - DB`  
- `C`, `Z`, `N`: Flags modificados por la comparación  
- `[x]`: lectura de memoria  
- `→`: asignación  

---

## 🟡 Cosas importantes sobre `CPY`

- **No modifica `Y`**
- Afecta los flags:
  - `C`: se activa si `Y ≥ DB`
  - `Z`: se activa si `Y == DB`
  - `N`: se activa si el bit 7 del resultado (`Y - DB`) es 1
- Misma lógica que `CMP`/`CPX`, pero con el registro `Y`

---

### 🔹 CPY Inmediato — `CPY #$10` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`, `cmp_val ← Y - DB`, `set_flags(cmp_val)` |

---

### 🔹 CPY Zeropage — `CPY $44` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `cmp_val ← Y - DB`, `set_flags(cmp_val)` |

---

### 🔹 CPY Absoluto — `CPY $4400` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `cmp_val ← Y - DB`, `set_flags(cmp_val)` |

---
