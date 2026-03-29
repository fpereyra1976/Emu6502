# LDY

## 🧠 Convenciones

- `IR`: Instruction Register (opcode)
- `PC`: Program Counter
- `DB`: Data Bus
- `AB`: Address Bus
- `tmp`: dirección temporal
- `Y`: Registro Y
- `[x]`: lectura de memoria
- `→`: asignación
- Flags: `Z` (zero) y `N` (negative) son actualizados por `LDY`

---

## ⚙️ Qué hace `LDY`

Carga el registro `Y` desde memoria o un valor inmediato, y ajusta los **flags `Z` y `N`**.

---

### 🔸 LDY Inmediato — `LDY #$44` — **2 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `Y ← DB`, `PC ← PC + 1`, `Z ← (Y == 0)`, `N ← (Y & 0x80)` |

---

### 🔸 LDY Zeropage — `LDY $44` — **3 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← [AB]`, `Y ← DB`, `Z ← (Y == 0)`, `N ← (Y & 0x80)` |

---

### 🔸 LDY Zeropage,X — `LDY $44,X` — **4 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF`, `AB ← tmp` |
| 4     | `DB ← [AB]`, `Y ← DB`, `Z ← (Y == 0)`, `N ← (Y & 0x80)` |

---

### 🔸 LDY Absoluto — `LDY $4400` — **4 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← [AB]`, `Y ← DB`, `Z ← (Y == 0)`, `N ← (Y & 0x80)` |

---

### 🔸 LDY Absoluto,X — `LDY $4400,X` — **4 o 5 ciclos** (dependiendo si cruza página)

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `addr ← tmp + X`, `AB ← addr`<br>Si no hay cruce de página: `DB ← [AB]`, `Y ← DB`, FIN |
| 5     | (si hay cruce): `DB ← [AB]`, `Y ← DB`, `Z/N` ← ... |

---

## 🧾 Opcodes de LDY

| Modo           | Opcode |
|----------------|--------|
| Inmediato      | `A0`   |
| Zeropage       | `A4`   |
| Zeropage,X     | `B4`   |
| Absoluto       | `AC`   |
| Absoluto,X     | `BC`   |

---