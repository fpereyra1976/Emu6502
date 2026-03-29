# STA

## 🧠 Convenciones (idénticas a antes)

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

## 🟡 Cosas importantes sobre `STA`

- `STA` **no afecta flags** (`Z`, `N`, etc.)
- `STA` **nunca cruza páginas**, pero algunos modos tienen 5 o 6 ciclos debido al modo de direccionamiento
- Almacena `A` en la dirección calculada

---

### 🔹 STA Zeropage — `STA $44` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp`, `DB ← A`, `[AB] ← DB` |

---

### 🔹 STA Zeropage,X — `STA $44,X` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp ← DB`, `PC ← PC + 1` |
| 3     | `tmp ← (tmp + X) & $FF`, `AB ← tmp` |
| 4     | `DB ← A`, `[AB] ← DB` |

---

### 🔹 STA Absoluto — `STA $4400` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `AB ← tmp`, `DB ← A`, `[AB] ← DB` |

---

### 🔹 STA Absoluto,X — `STA $4400,X` — **5 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← PC`, `DB ← [PC]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)`, `PC ← PC + 1` |
| 4     | `tmp ← tmp + X`, `AB ← tmp` |
| 5     | `DB ← A`, `[AB] ← DB` |

---

### 🔹 STA Absoluto,Y — `STA $4400,Y` — **5 ciclos** (igual que con `X`, pero suma `Y`)

---

### 🔹 STA Indirecto,X — `STA ($20,X)` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `zp_base ← DB`, `PC ← PC + 1` |
| 3     | `ptr ← (zp_base + X) & $FF`, `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `AB ← tmp` |
| 6     | `DB ← A`, `[AB] ← DB` |

---

### 🔹 STA Indirecto,Y — `STA ($20),Y` — **6 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `ptr ← DB`, `PC ← PC + 1` |
| 3     | `AB ← ptr`, `DB ← [AB]`, `tmp_lo ← DB` |
| 4     | `AB ← (ptr + 1) & $FF`, `DB ← [AB]`, `tmp_hi ← DB`, `tmp ← tmp_lo | (tmp_hi << 8)` |
| 5     | `tmp ← tmp + Y`, `AB ← tmp` |
| 6     | `DB ← A`, `[AB] ← DB` |

---