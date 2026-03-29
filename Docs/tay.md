# TAY

## 🧠 Convenciones

- `PC`: Program Counter  
- `IR`: Instruction Register (opcode)  
- `A`: Acumulador  
- `Y`: Registro Y  
- `→`: asignación  
- `N`, `Z`: flags Negative y Zero  
- **No toca memoria, solo registros internos**

---

## 🔷 `TAY` — Transfer A to Y

- **Opcode:** `$A8`  
- **Ciclos:** `2`  
- **Efecto:** `Y ← A`, actualiza `N`, `Z`

---

### 🌀 Ciclo a Ciclo

| Ciclo | Acción |
|-------|--------|
| 1     | `IR ← [PC]`, `PC ← PC + 1` |
| 2     | `Y ← A`, `Z ← (Y == 0)`, `N ← (Y & $80 != 0)` |

---

## 🧪 Ejemplos

- Si `A = $00` → `Y = $00`, `Z = 1`, `N = 0`
- Si `A = $F0` → `Y = $F0`, `Z = 0`, `N = 1`

---

## 📋 Resumen

| Instrucción | Opcode | Ciclos | Transferencia | Flags afectados |
|-------------|--------|--------|---------------|-----------------|
| `TAY`       | `$A8`  | 2      | `A → Y`       | `N`, `Z`        |

---
