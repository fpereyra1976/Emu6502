# BVC — *Branch if Overflow Clear* (salta si V = 0)

## 🧠 Convenciones

- `IR`: Instruction Register  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `V`: Flag de **Overflow**  
- `offset`: byte con signo  
- `tmp`: dirección tentativa (`PC + offset`)  
- `[x]`: lectura de memoria  
- `→`: asignación  

---

## 🟡 Cosas importantes sobre `BVC`

- Salta **solo si `V = 0`** (el flag de **Overflow** está limpio, es decir, no hubo desbordamiento aritmético)
- Offset es de 8 bits con signo
- Puede tomar **2, 3 o 4 ciclos**:
  - 2 si **no se toma el salto**
  - 3 si se toma **y no cruza página**
  - 4 si se toma **y cruza página**

---

### 🔹 BVC $nn — Branch relativo — **2–4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`  
|       | Si `V == 1` → fin (no se salta)  
|       | Si `V == 0` → `offset ← DB`, `tmp ← PC + (offset con signo)` |
| 3     | Si `tmp` está en **misma página** → `PC ← tmp`, fin  
|       | Si hay **cruce de página** → siguiente ciclo |
| 4     | `PC ← tmp` (ajuste final por cruce de página) |

---

### 📦 Ejemplo

```asm
BVC no_overflow
```

- Si el flag de **Overflow** (`V = 0`) está limpio, significa que **no hubo desbordamiento** durante una operación aritmética, y se salta a la etiqueta `no_overflow`
- Es útil para manejar situaciones donde no se produjo desbordamiento y se quiere tomar una acción diferente

---
