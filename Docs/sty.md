# STY

## 🧠 Recordatorio de convenciones

- `PC`: Program Counter  
- `IR`: Instruction Register  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `tmp`: dirección temporal  
- `Y`: Registro Y  
- `[x]`: contenido en memoria  
- `→`: asignación  
- No afecta flags  
- Es una **instrucción de escritura**: el valor de `Y` se **escribe** en memoria.

---

## ⚙️ Qué hace `STY`

Copia el contenido del registro **`Y`** a una dirección de memoria.  
A diferencia de `LDY`, **NO modifica flags**.

---

## 🔸 STY Zeropage — `STY $44` — **3 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← Y`, `[AB] ← DB` |

---

## 🔸 STY Zeropage,X — `STY $44,X` — **4 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF`, `AB ← tmp` |
| 4     | `DB ← Y`, `[AB] ← DB` |

---

## 🔸 STY Absoluto — `STY $4400` — **4 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← Y`, `[AB] ← DB` |

---

## 🧾 Opcodes de STY

| Modo         | Opcode |
|--------------|--------|
| Zeropage     | `84`   |
| Zeropage,X   | `94`   |
| Absoluto     | `8C`   |

---

## 🧩 Comparación rápida con otras "Store"

- `STA` escribe `A` en memoria.
- `STX` escribe `X` en memoria.
- `STY` escribe `Y` en memoria.
- Todas tienen modos similares (ZP, ZP,X, ABS), aunque `STX` usa **ZP,Y** en vez de **ZP,X**.

---