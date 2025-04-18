# STX

## 🧠 Convenciones (recordatorio)

- `PC`: Program Counter  
- `IR`: Instruction Register (opcode)  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `tmp`: dirección temporal  
- `X`: Registro X  
- `[x]`: contenido en memoria  
- `→`: asignación  
- **No afecta flags**

---

## ⚙️ Qué hace `STX`

Guarda el contenido del registro **X** en memoria.

---

### 🔸 STX Zeropage — `STX $44` — **3 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← X`, `[AB] ← DB` |

---

### 🔸 STX Zeropage,Y — `STX $44,Y` — **4 ciclos**

> 🔄 A diferencia de STY (que usa ZP,X), **STX usa ZP,Y**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + Y) & $FF`, `AB ← tmp` |
| 4     | `DB ← X`, `[AB] ← DB` |

---

### 🔸 STX Absoluto — `STX $4400` — **4 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← X`, `[AB] ← DB` |

---

## 🧾 Opcodes de STX

| Modo         | Opcode |
|--------------|--------|
| Zeropage     | `86`   |
| Zeropage,Y   | `96`   |
| Absoluto     | `8E`   |

---

## 🧩 Comparativa rápida

| Instrucción | Fuente | Modos                | Usa índice |
|-------------|--------|----------------------|------------|
| `STA`       | `A`    | ZP, ZP,X, ABS, ABS,X/Y, (ZP,X), (ZP),Y | Sí |
| `STX`       | `X`    | ZP, ZP,Y, ABS         | Sí (con `Y`) |
| `STY`       | `Y`    | ZP, ZP,X, ABS         | Sí (con `X`) |

---
