# BVS — *Branch if Overflow Set* (salta si V = 1)

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

## 🟡 Cosas importantes sobre `BVS`

- Salta **solo si `V = 1`** (el flag de **Overflow** está activado, es decir, se produjo un desbordamiento aritmético)
- Offset es de 8 bits con signo
- Puede tomar **2, 3 o 4 ciclos**:
  - 2 si **no se toma el salto**
  - 3 si se toma **y no cruza página**
  - 4 si se toma **y cruza página**

---

### 🔹 BVS $nn — Branch relativo — **2–4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`  
|       | Si `V == 0` → fin (no se salta)  
|       | Si `V == 1` → `offset ← DB`, `tmp ← PC + (offset con signo)` |
| 3     | Si `tmp` está en **misma página** → `PC ← tmp`, fin  
|       | Si hay **cruce de página** → siguiente ciclo |
| 4     | `PC ← tmp` (ajuste final por cruce de página) |

---

### 📦 Ejemplo

```asm
BVS overflow_detected
```

- Si el flag de **Overflow** (`V = 1`) está activado, significa que se produjo un desbordamiento durante una operación aritmética, y entonces se salta a la etiqueta `overflow_detected`
- Muy útil para gestionar desbordamientos en operaciones de adición o sustracción

---
