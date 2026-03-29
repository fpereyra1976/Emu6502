# NOP — *No Operation*

## 📋 Descripción

La instrucción `NOP` simplemente consume tiempo (un ciclo) sin afectar ningún registro, bandera ni memoria. Se usa a menudo como espacio de relleno o para esperar un ciclo sin hacer nada.

---

## 🧠 Convenciones

- **`PC`**: Program Counter  
- **`IR`**: Instruction Register  
- **`DB`**: Data Bus  
- **`AB`**: Address Bus

---

## 🕒 Ciclos

### 🔹 `NOP` Implied (opcode `$EA`) — **2 ciclos**

| Ciclo | Acción detallada |
|-------|------------------|
| 1     | `AB ← PC`, `DB ← [PC]`, `IR ← DB`, `PC ← PC + 1` |
| 2     | (No operación real. CPU espera un ciclo. Puede usarse para sincronización interna) |

---

## 💡 Notas

- Aunque no modifica nada, **`NOP` sigue leyendo un byte del opcode y lo incrementa**.
- Algunos opcodes no documentados del 6502 también se comportan como `NOP`, pero con diferentes tiempos de ciclo y efectos colaterales.

---
