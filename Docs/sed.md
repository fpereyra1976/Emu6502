# SED — *Set Decimal Mode*

## 📋 Descripción

`SED` establece el **flag decimal** (`D ← 1`). Cuando el flag decimal está activado, las instrucciones de suma y resta como `ADC` y `SBC` operan en modo **BCD (Binary Coded Decimal)** en lugar de en formato binario estándar.

---

## 🧠 Convenciones

- `PC`: Program Counter  
- `IR`: Instruction Register (opcode)  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `D`: Decimal flag  
- `[x]`: lectura de memoria  
- `→`: asignación  

---

## 🟡 Detalles de `SED`

- **No afecta ningún otro flag**  
- **No toca registros visibles**  
- Es una instrucción **implícita**, sin operandos  
- Siempre toma **2 ciclos**

---

### 🔹 SED — `SED` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `D ← 1` |

---
