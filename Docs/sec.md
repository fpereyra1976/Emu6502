# SEC — *Set Carry Flag* (establecer el flag de carry)

## 🧠 Convenciones

- **`C`**: Carry flag
- **`Z`**: Zero flag
- **`N`**: Negative flag
- **`V`**: Overflow flag
- **`IR`**: Instruction Register
- **`PC`**: Program Counter
- **`AB`**: Address Bus
- **`DB`**: Data Bus
- **`tmp`**: Dirección temporal
- **`A`**: Acumulador

---

## 🟡 Cosas importantes sobre `SEC`

- `SEC` **solo establece el flag de Carry (C)** a 1.
- **No realiza ninguna operación de memoria ni de cálculo**, solo cambia el valor del flag de Carry a **1**.
- **No afecta** los otros flags (Zero, Negative, Overflow).

---

### 🔹 SEC — **2 ciclos** (1 ciclo para la instrucción + 1 ciclo para obtener el opcode)

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` (lectura del opcode `SEC`) |
| 2     | `C ← 1` (se activa el flag de Carry) |

---

### 📦 Ejemplo

```asm
SEC
```

- En este caso, el procesador primero realiza la **lectura del opcode** `SEC` desde la memoria, incrementando el `PC`. Luego, en el segundo ciclo, **se activa el Carry flag** (`C ← 1`), sin ningún otro efecto en la memoria ni en el acumulador.

---

Gracias por señalarlo. ¿Te gustaría que agregue más detalles sobre otras instrucciones o que continuemos con otro tema?