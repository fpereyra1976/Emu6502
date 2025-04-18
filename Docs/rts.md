# RTS

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

## 🟡 Cosas importantes sobre `RTS`

- `RTS` **no afecta los flags** (`Z`, `N`, etc.)
- `RTS` **devuelve el control a la dirección almacenada en la pila**, incrementando el **PC** antes de hacer el salto.
- La dirección de retorno se obtiene de la pila: el byte bajo y luego el byte alto, que son leídos de la pila en orden inverso.

---

### 🔹 RTS — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← $0100 + SP`, `DB ← [AB]`, `tmp_lo ← DB`, `SP ← SP + 1` |
| 2     | `AB ← $0100 + SP`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `SP ← SP + 1` |
| 3     | `PC ← tmp` |
| 4     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |

---

### 🔹 Explicación Ciclo por Ciclo

- **Ciclo 1**: El **CPU** obtiene el byte bajo de la dirección de retorno de la pila.
  - `AB ← $0100 + SP`: Se coloca la dirección de la pila (`SP`) en el **AB**.
  - `DB ← [AB]`: El **DB** toma el byte bajo de la dirección almacenada en la pila.
  - `tmp_lo ← DB`: El byte bajo se guarda en **tmp_lo**.
  - `SP ← SP + 1`: El **Stack Pointer** se incrementa, ya que se ha leído el primer byte.

- **Ciclo 2**: El **CPU** obtiene el byte alto de la dirección de retorno de la pila.
  - `AB ← $0100 + SP`: Se coloca nuevamente la dirección de la pila en el **AB**.
  - `DB ← [AB]`: El **DB** toma el byte alto de la dirección almacenada en la pila.
  - `tmp_hi ← DB`: El byte alto se guarda en **tmp_hi**.
  - `tmp ← tmp_lo | (tmp_hi << 8)`: Se forma la dirección completa de retorno uniendo los bytes bajo y alto.
  - `SP ← SP + 1`: El **Stack Pointer** se incrementa de nuevo para apuntar al siguiente valor de la pila.

- **Ciclo 3**: El **CPU** asigna la dirección de retorno al **PC**.
  - `PC ← tmp`: La dirección calculada en **tmp** se asigna al **Program Counter**, haciendo que la ejecución del programa continúe desde esa dirección.

- **Ciclo 4**: El **CPU** obtiene el siguiente byte del **PC**, lee el siguiente **opcode** (para el próximo ciclo de instrucciones).
  - `AB ← PC`, `DB ← [PC]`: El **AB** apunta a la siguiente dirección y el **DB** obtiene el siguiente byte del **PC**.
  - `IR ← DB`: El byte leído se asigna al **Instruction Register**.
  - `PC ← PC + 1`: El **PC** se incrementa para apuntar al siguiente byte.

Este proceso asegura que el programa pueda volver a la ejecución correcta desde el punto en el que fue interrumpido, devolviendo la dirección de retorno desde la pila y continuando la ejecución.

---