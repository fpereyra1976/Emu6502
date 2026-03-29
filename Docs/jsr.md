# JSR

## 🧠 Convenciones

- `IR`: Instruction Register (opcode actual)
- `PC`: Program Counter
- `DB`: Data Bus
- `AB`: Address Bus
- `tmp`: dirección temporal intermedia
- `A`: Acumulador
- `[x]`: lectura de memoria
- `→`: asignación
- `DB ← A`: se pone el contenido del acumulador en el Data Bus para escribir

---

## 🟡 Cosas importantes sobre `JSR`

- `JSR` **no afecta los flags** (`Z`, `N`, etc.)
- `JSR` **siempre empuja la dirección de retorno** a la pila antes de saltar.
- El **PC** se actualiza para saltar a la subrutina después de empujar la dirección de retorno.

---

### 🔹 JSR — `JSR $4400` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (tmp + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `AB ← $0100 + SP`, `DB ← (PC + 2) & $FF`, `[AB] ← DB`, `SP ← SP - 1` |
| 6     | `AB ← $0100 + SP`, `DB ← (PC + 2) >> 8`, `[AB] ← DB`, `SP ← SP - 1` |

---

### 🔹 Explicación Ciclo por Ciclo

- **Ciclo 1**: El CPU obtiene el opcode `JSR` y lee la siguiente dirección del **PC**. Se incrementa el **PC** para leer la dirección de la subrutina.
  - `AB ← PC`, `DB ← [PC]` (el opcode de `JSR` se obtiene)
  - `IR ← DB` (el opcode se carga en el registro de instrucciones)
  - `PC ← PC + 1` (incrementa el **PC** para apuntar a la dirección de la subrutina)

- **Ciclo 2**: El CPU obtiene los siguientes dos bytes que representan la dirección de la subrutina.
  - `AB ← PC`, `DB ← [PC]` (se obtiene el primer byte de la dirección)
  - `tmp ← DB` (se guarda en **tmp** el primer byte de la dirección)
  - `PC ← PC + 1` (incrementa el **PC** para leer el siguiente byte de la dirección)

- **Ciclo 3**: El segundo byte de la dirección de la subrutina es leído y se guarda en **tmp_hi**.
  - `AB ← tmp`, `DB ← [AB]` (el **AB** apunta a la dirección de la subrutina)
  - `tmp_lo ← DB` (se guarda el byte bajo de la dirección)

- **Ciclo 4**: Se obtiene el byte alto de la dirección.
  - `AB ← (tmp + 1) & $FF`, `DB ← [AB]` (el **AB** apunta al siguiente byte de la dirección)
  - `tmp_hi ← DB` (se guarda el byte alto de la dirección)
  - `tmp ← tmp_lo | (tmp_hi << 8)` (se forma la dirección completa de la subrutina)

- **Ciclo 5**: El **PC** se incrementa por 2 (la longitud del `JSR`) para obtener la dirección de retorno. Luego, esa dirección se empuja a la pila, comenzando por el byte bajo.
  - `AB ← $0100 + SP`, `DB ← (PC + 2) & $FF` (se coloca el byte bajo de la dirección de retorno en el **Data Bus**)
  - `[AB] ← DB` (el byte bajo de la dirección se almacena en la pila)
  - `SP ← SP - 1` (el **Stack Pointer** se decrementa)

- **Ciclo 6**: El byte alto de la dirección de retorno se coloca en la pila.
  - `AB ← $0100 + SP`, `DB ← (PC + 2) >> 8` (se coloca el byte alto de la dirección de retorno)
  - `[AB] ← DB` (el byte alto de la dirección se almacena en la pila)
  - `SP ← SP - 1` (el **Stack Pointer** se decrementa nuevamente)
