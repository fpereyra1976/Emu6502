# BIT — *Bit Test* (prueba de bits)

## 🧠 Convenciones

- `IR`: Instruction Register  
- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `tmp`: dirección temporal  
- `A`: Acumulador  
- `M`: Memoria  
- `Z`: Flag de **Zero**  
- `N`: Flag de **Negative**  
- `V`: Flag de **Overflow**  

---

## 🟡 Cosas importantes sobre `BIT`

- `BIT` **no afecta el acumulador**, sino que se utiliza para verificar bits específicos en el valor de la memoria y ajustar los flags del procesador (Zero, Negative y Overflow).
- La instrucción compara el valor del acumulador (`A`) con el valor de memoria (`M`) bit a bit.
- Los **bits más importantes** de la memoria son importantes para los flags:
  - El **bit 7** de la memoria (MSB) se copia al **flag N** (Negative).
  - El **bit 6** de la memoria se copia al **flag V** (Overflow).
  - Si el **resultado de la comparación** es cero, se establece el **flag Z** (Zero).
- **No altera la memoria ni el acumulador**, solo los flags.

---

### 🔹 BIT Zeropage — `BIT $44` — **3 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← DB`, `DB ← [AB]` |
| 3     | `N ← (DB >> 7)`, `V ← (DB >> 6)`, `Z ← (A & DB == 0)` |

---

### 🔹 BIT Absoluto — `BIT $4400` — **4 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | `AB ← PC`, `DB ← [PC]`, `tmp_lo ← DB`, `PC ← PC + 1` |
| 3     | `AB ← tmp_lo | (DB << 8)`, `DB ← [AB]` |
| 4     | `N ← (DB >> 7)`, `V ← (DB >> 6)`, `Z ← (A & DB == 0)` |

---

### 📦 Ejemplo

```asm
BIT $44
```

- La instrucción `BIT` lee el valor en la dirección de memoria `$44`, y luego compara ese valor con el contenido del acumulador (`A`).
- Los **bits 7 y 6** de la memoria se copian a los flags **Negative** y **Overflow**.
- El resultado de la comparación `A & M` determina si se establece el flag **Zero**.

---
