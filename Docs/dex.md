# DEX — *Decrement X* (Decrementa el registro X)

## 🧠 Convenciones

- **`X`**: Registro X
- **`IR`**: Instruction Register (opcode actual)
- **`PC`**: Program Counter
- **`DB`**: Data Bus
- **`AB`**: Address Bus
- **`tmp`**: Dirección temporal (no se usa directamente en `DEX`)
- **`Z`**: Zero flag (se ve afectado)
- **`N`**: Negative flag (se ve afectado)
- **`C`**: Carry flag (no se ve afectado)

---

### 🔹 DEX — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `X ← X - 1`, **se actualiza el registro X**, `Z` y `N` se actualizan según el resultado de `X` |

---

### Explicación

- **`DEX`** decrementa el valor del registro **X** en 1.
- Esta instrucción actualiza los flags **Z** y **N**:
  - **`Z` (Zero flag)** se establece si el resultado de la operación es 0.
  - **`N` (Negative flag)** se establece si el bit más significativo del registro **X** es 1, es decir, si el resultado es negativo en términos de 8 bits.

`DEX` no afecta el **Carry flag (C)** ni el **Overflow flag (V)**.

---
