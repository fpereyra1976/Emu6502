# TXA

## 🧠 Convenciones

- `PC`: Program Counter  
- `IR`: Instruction Register  
- `DB`: Data Bus  
- `AB`: Address Bus (no se usa para acceder a memoria en esta instrucción)  
- `X`: Registro fuente  
- `A`: Registro destino  
- `→`: asignación  
- **Afecta flags N y Z** (Negative y Zero)

---

## ⚙️ Qué hace `TXA`

Transfiere el contenido del registro **X** al registro **A**.  
Afecta **solo los flags Z y N**, según el valor transferido.

---

### 🔸 TXA — `Opcode $8A` — **2 ciclos**

| Ciclo | Acción |
|-------|--------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `A ← X`, `Z ← (A == 0)`, `N ← (A & $80 != 0)` |

---

## 🧾 Detalles importantes

- **No toca la memoria**.
- Es puramente interna a la CPU.
- Solo usa los **registros A y X**, y actualiza flags.

---

## 🧪 Ejemplo

Supongamos:

- `X = $00` → `TXA` pondrá `A = $00`, y:
  - `Z = 1` (porque es cero)
  - `N = 0` (bit 7 no está encendido)

Si:

- `X = $F3` → `A = $F3`, y:
  - `Z = 0`
  - `N = 1` (bit 7 encendido)

---

## 🧾 Resumen

| Mnemónico | Opcode | Ciclos | Fuente → Destino | Flags afectados |
|-----------|--------|--------|------------------|-----------------|
| `TXA`     | `$8A`  | 2      | `X → A`          | `N`, `Z`        |

---
