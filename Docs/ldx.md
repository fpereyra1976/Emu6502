# LDX

## 🧠 Convenciones

Idénticas a antes:

- `IR`: Instruction Register (opcode)
- `PC`: Program Counter
- `DB`: Data Bus (lo que se lee de memoria o se va a escribir)
- `AB`: Address Bus (la dirección en memoria que se accede)
- `tmp`: dirección intermedia (16 bits)
- `X`: registro X
- `[x]`: contenido en memoria en dirección `x`
- `→`: asignación
- Los flags `Z` y `N` se modifican en `LDX`

---

## ⚙️ Qué hace LDX

Carga el registro `X` con un valor desde memoria.  
Modifica flags **Z (zero)** y **N (negative)** según el nuevo valor de `X`.

---

## 🟢 LDX Inmediato — `LDX #$44` — **2 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `X ← DB`, `PC ← PC + 1`, `Z ← (X == 0)`, `N ← (X & 0x80)` |

---

## 🟢 LDX Zeropage — `LDX $44` — **3 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `X ← DB`, `Z ← (X == 0)`, `N ← (X & 0x80)` |

---

## 🟢 LDX Zeropage,Y — `LDX $44,Y` — **4 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + Y) & 0xFF`, `AB ← tmp` |
| 4     | `DB ← [AB]`, `X ← DB`, `Z ← (X == 0)`, `N ← (X & 0x80)` |

---

## 🟢 LDX Absoluto — `LDX $4400` — **4 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `X ← DB`, `Z ← (X == 0)`, `N ← (X & 0x80)` |

---

## 🟢 LDX Absoluto,Y — `LDX $4400,Y` — **4 o 5 ciclos**

Este modo puede requerir un ciclo extra si se cruza página al sumar `Y`.

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `addr ← tmp + Y`, `AB ← addr`<br>Si no cruza página → `DB ← [AB]`, `X ← DB`, `Z/N` ← ..., FIN |
| 5     | (solo si cruzó página): repetir lectura con nueva página<br>`DB ← [AB]`, `X ← DB`, `Z/N ← ...` |

---

## 🧾 Opcodes (por si te interesa)

| Modo           | Opcode |
|----------------|--------|
| Inmediato      | `A2`   |
| Zeropage       | `A6`   |
| Zeropage,Y     | `B6`   |
| Absoluto       | `AE`   |
| Absoluto,Y     | `BE`   |

---