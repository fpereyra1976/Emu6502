# INC — *Incrementa en uno una posición de memoria*

## 📋 Descripción

`INC` incrementa en 1 el contenido de una dirección de memoria, dejando el resultado en la misma dirección. Afecta los flags `Z` y `N`, **pero no el carry**. El acumulador no se ve afectado.

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

### 🔹 INC Zeropage — `INC $44` — **5 ciclos**

| Ciclo | Acción |  
|-------|--------|  
| 1 | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2 | `AB ← PC`, `DB ← [PC]`, `addr ← DB`, `PC ← PC + 1` |
| 3 | `AB ← addr`, `DB ← [AB]`, `tmp ← DB` |
| 4 | `tmp ← (tmp + 1) & $FF`, `Z ← (tmp == 0)`, `N ← tmp & $80` |
| 5 | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---

### 🔹 INC Zeropage,X — `INC $44,X` — **6 ciclos**

| Ciclo | Acción |  
|-------|--------|  
| 1 | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2 | `AB ← PC`, `DB ← [PC]`, `zp ← DB`, `PC ← PC + 1` |
| 3 | `addr ← (zp + X) & $FF`, `AB ← addr` |
| 4 | `DB ← [AB]`, `tmp ← DB` |
| 5 | `tmp ← (tmp + 1) & $FF`, `Z ← (tmp == 0)`, `N ← tmp & $80` |
| 6 | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---

### 🔹 INC Absoluto — `INC $4400` — **6 ciclos**

| Ciclo | Acción |  
|-------|--------|  
| 1 | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2 | `AB ← PC`, `DB ← [PC]`, `lo ← DB`, `PC ← PC + 1` |
| 3 | `AB ← PC`, `DB ← [PC]`, `hi ← DB`, `PC ← PC + 1`, `addr ← lo | (hi << 8)` |
| 4 | `AB ← addr`, `DB ← [AB]`, `tmp ← DB` |
| 5 | `tmp ← (tmp + 1) & $FF`, `Z ← (tmp == 0)`, `N ← tmp & $80` |
| 6 | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---

### 🔹 INC Absoluto,X — `INC $4400,X` — **7 ciclos**

| Ciclo | Acción |  
|-------|--------|  
| 1 | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2 | `AB ← PC`, `DB ← [PC]`, `lo ← DB`, `PC ← PC + 1` |
| 3 | `AB ← PC`, `DB ← [PC]`, `hi ← DB`, `PC ← PC + 1`, `base ← lo | (hi << 8)` |
| 4 | `addr ← base + X`, `AB ← addr` |
| 5 | `DB ← [AB]`, `tmp ← DB` |
| 6 | `tmp ← (tmp + 1) & $FF`, `Z ← (tmp == 0)`, `N ← tmp & $80` |
| 7 | `AB ← addr`, `DB ← tmp`, `[AB] ← DB` |

---
