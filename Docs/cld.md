# CLD — *Clear Decimal Mode*

## 📋 Descripción

`CLD` borra el **flag decimal** (`D ← 0`). Este flag afecta cómo se comporta la suma/resta (`ADC`/`SBC`), ya que en modo decimal los resultados se ajustan en BCD (decimal empaquetado).

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

## 🟡 Detalles de `CLD`

- **No afecta ningún otro flag**  
- **No toca registros visibles**  
- Es una instrucción **implícita**, sin operandos  
- Siempre toma **2 ciclos**

---

### 🔹 CLD — `CLD` — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `D ← 0` |

---
