# BCS — *Branch if Carry Set*

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

## 🟡 Cosas importantes sobre `BCS`

- Salta **solo si el flag `C` (Carry) está en 1**
- Usa **offset con signo de 8 bits**
- Puede tomar **2, 3 o 4 ciclos**, igual que `BCC`:
  - 2 si **no se toma el branch**
  - 3 si **se toma sin cruce de página**
  - 4 si **se toma con cruce de página**

---

### 🔹 BCS $nn — Branch relativo — **2–4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `PC ← PC + 1`  
|       | Si `C == 0` → fin (no salta)  
|       | Si `C == 1` → `offset ← DB`  
|       | `tmp ← PC + (offset con signo)` |
| 3     | Si `tmp` está en **misma página** → `PC ← tmp`, fin  
|       | Si hay **cambio de página** → siguiente ciclo |
| 4     | `PC ← tmp` (ajuste final con cruce de página) |

---

### 📦 Ejemplo

```asm
BCS label ; Salta si Carry está seteado
```

Supongamos:
- `PC = $1000`
- Offset = `$05`
- Si `C = 1` → salta a `$1007`

---
