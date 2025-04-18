# BRK — *Force Interrupt*

## 📋 Descripción

La instrucción `BRK` simula una interrupción por software. Es como una "auto-interrupción": guarda el estado de la CPU (PC y P), activa la bandera de interrupción (`I`) y salta a la dirección de interrupción definida en `$FFFE/$FFFF`.

---

## 🧠 Convenciones

- **`PC`**: Program Counter  
- **`IR`**: Instruction Register  
- **`DB`**: Data Bus  
- **`AB`**: Address Bus  
- **`SP`**: Stack Pointer  
- **`P`**: Registro de estado  
- Stack base: `$0100`  
- Dirección de vector de interrupción: `$FFFE` (low), `$FFFF` (high)  
- `[x]`: lectura de memoria  
- `→`: asignación  
- `DB ← P | $30`: se empujan las flags con los bits `B=1`, `U=1`

---

## 🟡 Cosas importantes sobre `BRK`

- Al ejecutarse, **PC se incrementa en 2**, no en 1 (aunque el segundo byte es ignorado).
- El byte siguiente al `BRK` suele ser un `NOP` o usado por debuggers.
- Empuja `PC+2` y `P` a la pila.
- Establece la bandera `I` (**Interrupt Disable**).
- Salta al vector de interrupción `$FFFE/$FFFF`.
- **7 ciclos.**

---

## 🕒 Ciclos

### 🔹 `BRK` — **7 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | (Se lee el byte siguiente como parte del "pseudo-operando") `PC ← PC + 1` |
| 3     | `AB ← $0100 | SP`, `DB ← (PC >> 8)`, `[AB] ← DB`, `SP ← SP - 1` |
| 4     | `AB ← $0100 | SP`, `DB ← (PC & $FF)`, `[AB] ← DB`, `SP ← SP - 1` |
| 5     | `AB ← $0100 | SP`, `DB ← P | $30`, `[AB] ← DB`, `SP ← SP - 1` |
| 6     | `AB ← $FFFE`, `DB ← [AB]`, `tmp_lo ← DB` |
| 7     | `AB ← $FFFF`, `DB ← [AB]`, `tmp_hi ← DB`, `PC ← tmp_lo | (tmp_hi << 8)`, `Set I = 1` |

---
