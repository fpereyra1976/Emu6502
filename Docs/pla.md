# PLA

## 🧠 Convenciones

- `PC`: Program Counter  
- `IR`: Instruction Register (opcode)  
- `A`: Acumulador  
- `SP`: Stack Pointer  
- `→`: asignación  
- **No afecta flags**

---

## 🔷 `PLA` — Pull A from Stack

- **Opcode:** `$68`  
- **Ciclos:** `4`  
- **Efecto:** `A ← Mem[SP]`, incrementa `SP`, actualiza `N`, `Z`

---

### 🌀 Ciclo a Ciclo

| Ciclo | Acción |
|-------|--------|
| 1     | `IR ← [PC]`, `PC ← PC + 1` |
| 2     | `AB ← $0100 + SP`, `DB ← [AB]` (se obtiene el valor de la pila) |
| 3     | `A ← DB`, `SP ← SP + 1` (valor del acumulador es actualizado) |
| 4     | `Z ← (A == 0)`, `N ← (A & $80 != 0)` (se actualizan los flags Z y N) |

---

## 🧪 Ejemplo

Si:

- `Mem[$0100 + $FE] = $42`  
- `SP = $FE`  

Luego de ejecutar `PLA`:

- `A = $42`  
- `SP = $FF` (el puntero de la pila se incrementa)

Si el valor en la pila hubiera sido **0**, el valor de **`Z`** sería actualizado a **1**, y si fuera un valor negativo (con bit 7 activado), el flag **`N`** sería **1**.

---

## 📋 Resumen

| Instrucción | Opcode | Ciclos | Acción | Flags afectados |
|-------------|--------|--------|--------|-----------------|
| `PLA`       | `$68`  | 4      | `Mem[SP] → A`, incrementa `SP` | `N`, `Z`        |

---