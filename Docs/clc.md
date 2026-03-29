# CLC — *Clear Carry Flag* (Limpiar el flag de acarreo)

## 🧠 Convenciones

- **`C`**: Carry flag (se borra)
- **`IR`**: Instruction Register (opcode actual)
- **`PC`**: Program Counter
- **`DB`**: Data Bus
- **`AB`**: Address Bus
- **`tmp`**: Dirección temporal (no se usa directamente en `CLC`)

---

### 🔹 CLC — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `C ← 0`, **se limpia el Carry flag**, sin efecto en registros de datos |

---

### Explicación

- **`CLC`** limpia (pone a 0) el **Carry flag (C)**. Esto es útil para operaciones aritméticas donde deseas asegurarte de que no haya un acarreo residual de una operación anterior.
- Esta instrucción **no afecta** los registros de datos como **A** o **X**, ni actualiza los flags **Z**, **N** o **V**.

---
