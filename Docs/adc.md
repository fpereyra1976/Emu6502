# ADC

## 🧠 Convenciones

- `IR`: Instruction Register (opcode actual)  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `tmp`: dirección temporal intermedia  
- `A`: Acumulador  
- `C`: Flag de Carry (acarreo)  
- `V`: Flag de Overflow  
- `Z`: Zero flag  
- `N`: Negative flag  
- `[x]`: lectura de memoria  
- `→`: asignación  
- `DB ← A`: carga en el Data Bus  
- `A ← A + DB + C`: suma con acarreo  
- `set_flags()`: rutina que actualiza `Z`, `N`, `V`, `C` según el resultado

---

## 🟡 Cosas importantes sobre `ADC`

- Afecta los flags: `C`, `Z`, `N`, `V`.
- El resultado de la suma incluye el flag de `Carry`.
- Si el resultado es >255, el flag `C` se activa.
- Si ocurre overflow aritmético en complemento a 2, se activa el flag `V`.
- Tiene muchas variantes por modo de direccionamiento.

---

### 🔹 ADC Inmediato — `ADC #$10` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`, `A ← A + DB + C`, `set_flags()` |

---

### 🔹 ADC Zeropage — `ADC $44` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `A ← A + DB + C`, `set_flags()` |

---

### 🔹 ADC Zeropage,X — `ADC $44,X` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF`, `AB ← tmp` |
| 4     | `DB ← [AB]`, `A ← A + DB + C`, `set_flags()` |

---

### 🔹 ADC Absoluto — `ADC $4400` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `A ← A + DB + C`, `set_flags()` |

---

### 🔹 ADC Absoluto,X — `ADC $4400,X` — **4/5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `tmp ← tmp + X`, `AB ← tmp` |
| 5*    | `DB ← [AB]`, `A ← A + DB + C`, `set_flags()` |

> *El 5° ciclo solo ocurre si hay cruce de página*

---

### 🔹 ADC Absoluto,Y — `ADC $4400,Y` — **4/5 ciclos**  
> Igual que con `X`, pero suma `Y`

---

### 🔹 ADC Indirecto,X — `ADC ($20,X)` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `zp_base ← DB`, `PC ← PC + 1` |
| 3     | `ptr ← (zp_base + X) & $FF`, `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `AB ← tmp`, `DB ← [AB]` |
| 6     | `A ← A + DB + C`, `set_flags()` |

---

### 🔹 ADC Indirecto,Y — `ADC ($20),Y` — **5/6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `ptr ← DB`, `PC ← PC + 1` |
| 3     | `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `tmp ← tmp + Y`, `AB ← tmp` |
| 6*    | `DB ← [AB]`, `A ← A + DB + C`, `set_flags()` |

> *El ciclo 6 ocurre si hay cruce de página*

---
