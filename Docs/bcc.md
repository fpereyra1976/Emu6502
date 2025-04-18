# BCC — *Branch if Carry Clear*

## 🧠 Convenciones

- `IR`: Instruction Register  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `C`: Flag de **carry**  
- `offset`: byte con signo que se suma al `PC`  
- `tmp`: dirección tentativa (`PC + offset`)  
- `[x]`: lectura de memoria  
- `→`: asignación  

---

## 🟡 Cosas importantes sobre `BCC`

- Salta **solo si `C` (Carry) está limpio (0)**
- Usa **offset con signo de 8 bits**
- Puede tomar **2, 3 o 4 ciclos**:
  - 2 si **no toma el branch**
  - 3 si toma el branch **sin cruce de página**
  - 4 si toma el branch **con cruce de página**

---

### 🔹 BCC $nn — Branch relativo — **2–3–4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`  
|       | Si `C == 1` → fin (no hay branch)  
|       | Si `C == 0` → `offset ← DB`  
|       | `tmp ← PC + (offset con signo)` |
| 3     | Si `tmp` está en **misma página** → `PC ← tmp`, fin  
|       | Si hay **cambio de página** → siguiente ciclo |
| 4     | `PC ← tmp` (ajuste final con cruce de página) |

---

### 📦 Ejemplo

```assembly
BCC label ; Salta si Carry está limpio
```

Supongamos:
- `PC = $1000`
- Siguiente byte (offset) = `$FA` (−6 en complemento a dos)
- Si `C = 0`, salta a `$0FFA`

---
