# PLP — *Pull Processor Status*

## 📋 Descripción

`PLP` saca un byte de la pila y lo copia al registro de estado (`P`), restaurando todas las banderas. Se usa normalmente para restaurar el estado después de una interrupción o rutina que modificó banderas.

---

## 🧠 Convenciones

- **`PC`**: Program Counter  
- **`IR`**: Instruction Register  
- **`DB`**: Data Bus  
- **`AB`**: Address Bus  
- **`SP`**: Stack Pointer (puntero de pila, de 8 bits)  
- **`P`**: Registro de estado (Status Flags)  
- **Stack base**: `$0100` — la pila siempre está en página 1

---

## 🟡 Cosas importantes sobre `PLP`

- Afecta **todas las banderas del registro de estado** (`NV-BDIZC`)
- El bit 5 (flag "unused") usualmente se ignora, aunque en algunas implementaciones se mantiene a `1`
- Consume **4 ciclos**

---

## 🕒 Ciclos

### 🔹 `PLP` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | (Ciclo interno sin operación visible; se prepara la pila) |
| 3     | `SP ← SP + 1`, `AB ← $0100 | SP` |
| 4     | `DB ← [AB]`, `P ← DB` |

---
