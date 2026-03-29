# SBC

## 🧠 Convenciones

- `IR`: Instruction Register (opcode actual)  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `tmp`: dirección temporal intermedia  
- `A`: Acumulador  
- `C`: Flag de Carry  
- `V`: Flag de Overflow  
- `Z`: Zero flag  
- `N`: Negative flag  
- `[x]`: lectura de memoria  
- `→`: asignación  
- `DB ← A`: carga en el Data Bus  
- `A ← A - DB - (1 - C)`: resta con acarreo invertido  
- `set_flags()`: rutina que actualiza `Z`, `N`, `V`, `C` según el resultado

---

## 🟡 Cosas importantes sobre `SBC`

- Afecta los flags: `C`, `Z`, `N`, `V`.
- La resta se hace como: `A ← A + (~DB) + C`
- Si no hay "préstamo", se mantiene el flag `C` (como en suma).
- Usa **complemento a 1** de `DB`, lo que convierte la resta en una suma.

---

### 🔹 SBC Inmediato — `SBC #$10` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`, `A ← A + (~DB) + C`, `set_flags()` |

---

### 🔹 SBC Zeropage — `SBC $44` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `A ← A + (~DB) + C`, `set_flags()` |

---

### 🔹 SBC Zeropage,X — `SBC $44,X` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF`, `AB ← tmp` |
| 4     | `DB ← [AB]`, `A ← A + (~DB) + C`, `set_flags()` |

---

### 🔹 SBC Absoluto — `SBC $4400` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `A ← A + (~DB) + C`, `set_flags()` |

---

### 🔹 SBC Absoluto,X — `SBC $4400,X` — **4/5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `tmp ← tmp + X`, `AB ← tmp` |
| 5*    | `DB ← [AB]`, `A ← A + (~DB) + C`, `set_flags()` |

> *El 5° ciclo solo ocurre si hay cruce de página*

---

### 🔹 SBC Absoluto,Y — `SBC $4400,Y` — **4/5 ciclos**  
> Igual que con `X`, pero suma `Y`

---

### 🔹 SBC Indirecto,X — `SBC ($20,X)` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `zp_base ← DB`, `PC ← PC + 1` |
| 3     | `ptr ← (zp_base + X) & $FF`, `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `AB ← tmp`, `DB ← [AB]` |
| 6     | `A ← A + (~DB) + C`, `set_flags()` |

---

### 🔹 SBC Indirecto,Y — `SBC ($20),Y` — **5/6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `ptr ← DB`, `PC ← PC + 1` |
| 3     | `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `tmp ← tmp + Y`, `AB ← tmp` |
| 6*    | `DB ← [AB]`, `A ← A + (~DB) + C`, `set_flags()` |

> *El ciclo 6 ocurre si hay cruce de página*

---