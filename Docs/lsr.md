# LSR — *Logical Shift Right*

## 📋 Descripción

`LSR` desplaza los bits del operando una posición a la derecha. El bit menos significativo (`bit 0`) se mueve al flag `C` (carry), y un `0` se inserta en el bit más significativo (`bit 7`).

---

## 🧠 Convenciones

- `PC`: Program Counter  
- `IR`: Instruction Register  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `SP`: Stack Pointer  
- `P`: Registro de estado  
- `tmp`: temporal intermedio para almacenamiento  
- `C`: Carry  
- `Z`: Zero  
- `N`: Negative (siempre 0 después de LSR, ya que el bit 7 se borra)  
- `[x]`: lectura de memoria  
- `→`: asignación  

---

## 🟡 Cosas importantes sobre `LSR`

- Bit 0 va al **carry**.
- Bit 7 siempre se borra.
- Se actualizan los flags `C`, `Z`, `N` (aunque `N` queda siempre en 0).
- Puede operar sobre el **acumulador** o sobre **memoria**.

---

## 🕒 Modos y Ciclos

---

### 🔹 LSR Acumulador — `LSR A` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `C ← A & $01`, `A ← A >> 1`, `A ← A & $7F`, `Z ← (A == 0)`, `N ← 0` |

---

### 🔹 LSR Zeropage — `LSR $44` — **5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `addr ← DB`, `PC ← PC + 1` |
| 3     | `AB ← addr`, `DB ← [AB]`, `tmp ← DB` |
| 4     | `C ← tmp & $01`, `tmp ← tmp >> 1`, `tmp ← tmp & $7F`, `Z ← (tmp == 0)`, `N ← 0` |
| 5     | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---

### 🔹 LSR Zeropage,X — `LSR $44,X` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `zp ← DB`, `PC ← PC + 1` |
| 3     | `addr ← (zp + X) & $FF`, `AB ← addr` |
| 4     | `DB ← [AB]`, `tmp ← DB` |
| 5     | `C ← tmp & $01`, `tmp ← tmp >> 1`, `tmp ← tmp & $7F`, `Z ← (tmp == 0)`, `N ← 0` |
| 6     | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---

### 🔹 LSR Absoluto — `LSR $4400` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `hi ← DB`, `PC ← PC + 1`, `addr ← lo | (hi << 8)` |
| 4     | `AB ← addr`, `DB ← [AB]`, `tmp ← DB` |
| 5     | `C ← tmp & $01`, `tmp ← tmp >> 1`, `tmp ← tmp & $7F`, `Z ← (tmp == 0)`, `N ← 0` |
| 6     | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---

### 🔹 LSR Absoluto,X — `LSR $4400,X` — **7 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `hi ← DB`, `PC ← PC + 1`, `base ← lo | (hi << 8)` |
| 4     | `addr ← base + X`, `AB ← addr` |
| 5     | `DB ← [AB]`, `tmp ← DB` |
| 6     | `C ← tmp & $01`, `tmp ← tmp >> 1`, `tmp ← tmp & $7F`, `Z ← (tmp == 0)`, `N ← 0` |
| 7     | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---
