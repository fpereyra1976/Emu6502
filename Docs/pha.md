# PHA 

## 🧠 Convenciones

- `PC`: Program Counter  
- `IR`: Instruction Register (opcode)  
- `A`: Acumulador  
- `SP`: Stack Pointer  
- `→`: asignación  
- **No afecta flags**

---

## 🔷 `PHA` — Push A onto Stack

- **Opcode:** `$48`  
- **Ciclos:** `3`  
- **Efecto:** `Mem[SP] ← A`, decrementa `SP`, no afecta flags

---

### 🌀 Ciclo a Ciclo

| Ciclo | Acción |
|-------|--------|
| 1     | `IR ← [PC]`, `PC ← PC + 1` |
| 2     | `SP ← SP - 1`, `AB ← $0100 + SP`, `DB ← A` |
| 3     | `[AB] ← DB` (memoria de la pila recibe el valor de `A`) |

---

## 🧪 Ejemplo

Si:

- `A = $42`  
- `SP = $FF`  

Luego de ejecutar `PHA`:

- `Mem[$0100 + $FF] = $42`  
- `SP = $FE` (decrementa el puntero de la pila)

---

## 📋 Resumen

| Instrucción | Opcode | Ciclos | Acción | Flags afectados |
|-------------|--------|--------|--------|-----------------|
| `PHA`       | `$48`  | 3      | `A → Mem[SP]`, decrementa `SP` | Ninguno |


