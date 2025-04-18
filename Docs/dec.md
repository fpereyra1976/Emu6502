# DEC — *Decrementa en uno una posición de memoria*

## 📋 Descripción

`DEC` decrementa en 1 el contenido de una dirección de memoria (sin afectar el acumulador), y escribe el nuevo valor en la misma dirección.  
Afecta los flags `Z` (Zero) y `N` (Negative), **pero no el carry**.

---

## 🧠 Convenciones

- `PC`: Program Counter  
- `IR`: Instruction Register  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `tmp`: valor temporal  
- `Z`, `N`: flags de Zero y Negative  
- `[x]`: lectura de memoria  
- `→`: asignación  

---

## 🕒 Modos de direccionamiento y ciclos

---

### 🔹 DEC Zeropage — `DEC $44` — **5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1 | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2 | `AB ← PC`, `DB ← [PC]`, `addr ← DB`, `PC ← PC + 1` |
| 3 | `AB ← addr`, `DB ← [AB]`, `tmp ← DB` |
| 4 | `tmp ← (tmp - 1) & $FF`, `Z ← (tmp == 0)`, `N ← tmp & $80` |
| 5 | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---

### 🔹 DEC Zeropage,X — `DEC $44,X` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1 | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2 | `AB ← PC`, `DB ← [PC]`, `zp ← DB`, `PC ← PC + 1` |
| 3 | `addr ← (zp + X) & $FF`, `AB ← addr` |
| 4 | `DB ← [AB]`, `tmp ← DB` |
| 5 | `tmp ← (tmp - 1) & $FF`, `Z ← (tmp == 0)`, `N ← tmp & $80` |
| 6 | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---

### 🔹 DEC Absoluto — `DEC $4400` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1 | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2 | `AB ← PC`, `DB ← [PC]`, `lo ← DB`, `PC ← PC + 1` |
| 3 | `AB ← PC`, `DB ← [PC]`, `hi ← DB`, `PC ← PC + 1`, `addr ← lo | (hi << 8)` |
| 4 | `AB ← addr`, `DB ← [AB]`, `tmp ← DB` |
| 5 | `tmp ← (tmp - 1) & $FF`, `Z ← (tmp == 0)`, `N ← tmp & $80` |
| 6 | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---

### 🔹 DEC Absoluto,X — `DEC $4400,X` — **7 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1 | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2 | `AB ← PC`, `DB ← [PC]`, `lo ← DB`, `PC ← PC + 1` |
| 3 | `AB ← PC`, `DB ← [PC]`, `hi ← DB`, `PC ← PC + 1`, `base ← lo | (hi << 8)` |
| 4 | `addr ← base + X`, `AB ← addr` |
| 5 | `DB ← [AB]`, `tmp ← DB` |
| 6 | `tmp ← (tmp - 1) & $FF`, `Z ← (tmp == 0)`, `N ← tmp & $80` |
| 7 | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---
