# CLI — *Clear Interrupt Disable* (Deshabilitar interrupciones)

## 🧠 Convenciones

- **`A`**: Acumulador (no se ve afectado por esta instrucción)
- **`IR`**: Instruction Register (opcode actual)
- **`PC`**: Program Counter
- **`DB`**: Data Bus
- **`AB`**: Address Bus
- **`tmp`**: Dirección temporal
- **`I`**: Interrupt Disable flag (flag de deshabilitación de interrupciones)
- **`Z`**: Zero flag
- **`N`**: Negative flag
- **`V`**: Overflow flag
- **`C`**: Carry flag (no se ve afectado por `CLI`)

---

### 🔹 CLI — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `I ← 0` (se limpia el flag de deshabilitación de interrupciones) |

---

### Explicación

- **`CLI`** desactiva las interrupciones al limpiar el bit **I** del registro de estado de la CPU (que es parte de los flags).
- Esta instrucción no tiene efectos en el acumulador ni en otros registros, excepto en el flag **I**.

El **flag de Interrupción (I)** indica si las interrupciones están habilitadas o deshabilitadas. Al ejecutar `CLI`, se limpia dicho flag, lo que significa que la CPU estará habilitada para recibir interrupciones.
