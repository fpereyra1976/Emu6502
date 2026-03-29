# BNE — *Branch if Not Equal* (salta si Z = 0)

## 🧠 Convenciones

- `IR`: Instruction Register  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `Z`: Flag de **Zero**  
- `offset`: byte con signo  
- `tmp`: dirección tentativa (`PC + offset`)  
- `[x]`: lectura de memoria  
- `→`: asignación  

---

## 🟡 Cosas importantes sobre `BNE`

- Salta **solo si `Z = 0`** (último resultado **no fue cero**)
- Offset es de 8 bits con signo (–128 a +127)
- Puede tomar **2, 3 o 4 ciclos**:
  - 2 si **no se toma el salto**
  - 3 si se toma y **no cruza página**
  - 4 si se toma y **cruza página**

---

### 🔹 BNE $nn — Branch relativo — **2–4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`  
|       | Si `Z == 1` → fin (no se salta)  
|       | Si `Z == 0` → `offset ← DB`, `tmp ← PC + (offset con signo)` |
| 3     | Si `tmp` está en **misma página** → `PC ← tmp`, fin  
|       | Si hay **cruce de página** → siguiente ciclo |
| 4     | `PC ← tmp` (ajuste final por cruce de página) |

---

### 📦 Ejemplo

```asm
BNE loop
```

- Si el resultado anterior **no fue cero**, salta a `loop`
- Muy usado en bucles y comparaciones

---
