# DEY — *Decrement Y* (Decrementa el registro Y)

## 🧠 Convenciones

- **`Y`**: Registro Y
- **`IR`**: Instruction Register (opcode actual)
- **`PC`**: Program Counter
- **`DB`**: Data Bus
- **`AB`**: Address Bus
- **`tmp`**: Dirección temporal (no se usa directamente en `DEY`)
- **`Z`**: Zero flag (se ve afectado)
- **`N`**: Negative flag (se ve afectado)
- **`C`**: Carry flag (no se ve afectado)

---

### 🔹 DEY — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `Y ← Y - 1`, **se actualiza el registro Y**, `Z` y `N` se actualizan según el resultado de `Y` |

---

### Explicación

- **`DEY`** decrementa el valor del registro **Y** en 1.
- Esta instrucción actualiza los flags **Z** y **N**:
  - **`Z` (Zero flag)** se establece si el resultado de la operación es 0.
  - **`N` (Negative flag)** se establece si el bit más significativo del registro **Y** es 1, es decir, si el resultado es negativo en términos de 8 bits.

`DEY` no afecta el **Carry flag (C)** ni el **Overflow flag (V)**.

---
