# BMI — *Branch if Minus* (salta si N = 1)

## 🧠 Convenciones

- `IR`: Instruction Register  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `N`: Flag de **Negative** (signo)  
- `offset`: byte con signo  
- `tmp`: dirección tentativa (`PC + offset`)  
- `[x]`: lectura de memoria  
- `→`: asignación  

---

## 🟡 Cosas importantes sobre `BMI`

- Salta **solo si `N = 1`** (el último resultado fue negativo, es decir, el bit más significativo fue 1)
- Offset es de 8 bits con signo
- Puede tomar **2, 3 o 4 ciclos**:
  - 2 si **no se toma el salto**
  - 3 si se toma **y no cruza página**
  - 4 si se toma **y cruza página**

---

### 🔹 BMI $nn — Branch relativo — **2–4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`  
|       | Si `N == 0` → fin (no se salta)  
|       | Si `N == 1` → `offset ← DB`, `tmp ← PC + (offset con signo)` |
| 3     | Si `tmp` está en **misma página** → `PC ← tmp`, fin  
|       | Si hay **cruce de página** → siguiente ciclo |
| 4     | `PC ← tmp` (ajuste final por cruce de página) |

---

### 📦 Ejemplo

```asm
BMI negative
```

- Si el último resultado de una operación fue **negativo** (`N = 1`), se salta a la etiqueta `negative`
- Muy usado para saltar cuando hay resultados negativos en cálculos o comparaciones

---
