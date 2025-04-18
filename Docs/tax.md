# TAX

## 🧠 Convenciones

- `PC`: Program Counter  
- `IR`: Instruction Register (opcode)  
- `A`: Acumulador  
- `X`: Registro X  
- `→`: asignación  
- `N`, `Z`: flags Negative y Zero  
- **No toca memoria, solo registros internos**

---

## 🔷 `TAX` — Transfer A to X

- **Opcode:** `$AA`  
- **Ciclos:** `2`  
- **Efecto:** `X ← A`, actualiza `N`, `Z`

---

### 🌀 Ciclo a Ciclo

| Ciclo | Acción |
|-------|--------|
| 1     | `IR ← [PC]`, `PC ← PC + 1` |
| 2     | `X ← A`, `Z ← (X == 0)`, `N ← (X & $80 != 0)` |

---

## 🧪 Ejemplos

- Si `A = $00` → `X = $00`, `Z = 1`, `N = 0`
- Si `A = $F0` → `X = $F0`, `Z = 0`, `N = 1`

---

## 📋 Resumen

| Instrucción | Opcode | Ciclos | Transferencia | Flags afectados |
|-------------|--------|--------|---------------|-----------------|
| `TAX`       | `$AA`  | 2      | `A → X`       | `N`, `Z`        |

---
