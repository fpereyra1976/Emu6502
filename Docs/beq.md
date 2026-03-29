# BEQ — *Branch if Equal* (salta si Z = 1)

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

## 🟡 Cosas importantes sobre `BEQ`

- Salta **solo si `Z = 1`** (último resultado fue cero)
- Offset es de 8 bits con signo
- Puede tomar **2, 3 o 4 ciclos**:
  - 2 si **no se toma el salto**
  - 3 si se toma y no cruza página
  - 4 si se toma y **cruza página**

---

### 🔹 BEQ $nn — Branch relativo — **2–4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`  
|       | Si `Z == 0` → fin (no hay salto)  
|       | Si `Z == 1` → `offset ← DB`, `tmp ← PC + (offset con signo)` |
| 3     | Si `tmp` en **misma página** → `PC ← tmp`, fin  
|       | Si **cruza página** → siguiente ciclo |
| 4     | `PC ← tmp` (ajuste final por cruce de página) |

---

### 📦 Ejemplo

```asm
BEQ skip
```

- Si `Z = 1`, salta a `PC + offset`
- Offset es relativo al **siguiente byte** después del offset mismo

---
