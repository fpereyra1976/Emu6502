# CPX

## 🧠 Convenciones

- `IR`: Instruction Register (opcode actual)  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `X`: Registro X  
- `cmp_val ← X - DB`  
- `C`, `Z`, `N`: Flags modificados por la comparación  
- `[x]`: lectura de memoria  
- `→`: asignación  

---

## 🟡 Cosas importantes sobre `CPX`

- **No modifica `X`**
- Afecta los flags:
  - `C`: se activa si `X ≥ DB`
  - `Z`: se activa si `X == DB`
  - `N`: se activa si el bit 7 del resultado (`X - DB`) es 1
- Misma lógica que `CMP`, pero operando con `X`

---

### 🔹 CPX Inmediato — `CPX #$10` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`, `cmp_val ← X - DB`, `set_flags(cmp_val)` |

---

### 🔹 CPX Zeropage — `CPX $44` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `cmp_val ← X - DB`, `set_flags(cmp_val)` |

---

### 🔹 CPX Absoluto — `CPX $4400` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `cmp_val ← X - DB`, `set_flags(cmp_val)` |

---
