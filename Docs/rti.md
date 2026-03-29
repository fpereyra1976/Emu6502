# RTI — *Return from Interrupt*

## 📋 Descripción

`RTI` se usa al final de una rutina de interrupción. Restaura el estado de la CPU tal como estaba antes de que la interrupción ocurriera: primero recupera el registro de estado (`P`) y luego la dirección de retorno al `PC`.

---

## 🧠 Convenciones

- **`PC`**: Program Counter  
- **`IR`**: Instruction Register  
- **`DB`**: Data Bus  
- **`AB`**: Address Bus  
- **`SP`**: Stack Pointer (8 bits)  
- **`P`**: Registro de estado  
- Stack base: `$0100`

---

## 🟡 Cosas importantes sobre `RTI`

- **Restaura todas las flags** (`NV-BDIZC`) desde la pila.
- Recupera el `PC` con los dos siguientes bytes (low y high).
- Consume **6 ciclos**.
- Se usa exclusivamente para salir de interrupciones como IRQ o NMI.

---

## 🕒 Ciclos

### 🔹 `RTI` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | (Ciclo interno: sin efecto visible) |
| 3     | `SP ← SP + 1`, `AB ← $0100 | SP` |
| 4     | `DB ← [AB]`, `P ← DB` |
| 5     | `SP ← SP + 1`, `AB ← $0100 | SP` |
| 6     | `DB ← [AB]`, `tmp_lo ← DB`, `SP ← SP + 1`, `AB ← $0100 | SP`, `DB ← [AB]`, `tmp_hi ← DB`, `PC ← tmp_lo | (tmp_hi << 8)` |

> 🔍 Nota: los ciclos 5 y 6 se solapan parcialmente si querés visualizarlo a bajo nivel, ya que en ciclo 6 se hace la lectura y ensamblado del `PC` completo.

---
