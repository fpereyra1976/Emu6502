# TYA

## 🧠 Convenciones

- `PC`: Program Counter  
- `IR`: Instruction Register (opcode)  
- `A`: Acumulador  
- `Y`: Registro Y  
- `→`: asignación  
- `N`, `Z`: flags Negative y Zero  
- **No toca memoria, solo registros internos**

---

## 🔷 `TYA` — Transfer Y to A

- **Opcode:** `$98`  
- **Ciclos:** `2`  
- **Efecto:** `A ← Y`, actualiza `N`, `Z`

---

### 🌀 Ciclo a Ciclo

| Ciclo | Acción |
|-------|--------|
| 1     | `IR ← [PC]`, `PC ← PC + 1` |
| 2     | `A ← Y`, `Z ← (A == 0)`, `N ← (A & $80 != 0)` |

---

## 🧪 Ejemplos

- Si `Y = $00` → `A = $00`, `Z = 1`, `N = 0`
- Si `Y = $F0` → `A = $F0`, `Z = 0`, `N = 1`

---

## 📋 Resumen

| Instrucción | Opcode | Ciclos | Transferencia | Flags afectados |
|-------------|--------|--------|---------------|-----------------|
| `TYA`       | `$98`  | 2      | `Y → A`       | `N`, `Z`        |

---
