# Reset

## 🧠 Convenciones

- `PC`: Program Counter  
- `DB`: Data Bus  
- `AB`: Address Bus  
- `IR`: Instruction Register  
- `[x]`: lectura de memoria  
- `→`: asignación  
- `RESET`: línea de entrada activa en bajo (`0 = activo`)

---

## 🛠️ Qué hace el 6502 al recibir RESET

1. **Señal RESET baja (activa):**
   - Cuando el pin RESET se pone en 0 (bajo), el 6502 **entra en estado de reset**, sin ejecutar instrucciones.
   - El procesador no responde a IRQ o NMI durante este tiempo.
   - Algunas líneas (como `RW`) se ponen en estado conocido, pero otras pueden estar indefinidas por un breve tiempo.
   - Internamente, se inicia un proceso de 6 ciclos.

---

## 🔁 Secuencia interna de RESET (6 ciclos)

Durante el RESET, el 6502 realiza internamente lo siguiente:

| Ciclo | Acción                                                  |
|-------|---------------------------------------------------------|
| 1–2   | Leer ciclos vacíos o basura. Internamente limpia el estado. |
| 3     | Lee desde `$FFFC` → `tmp_lo ← [FFFC]`                   |
| 4     | Lee desde `$FFFD` → `tmp_hi ← [FFFD]`                   |
| 5     | `PC ← tmp_lo | (tmp_hi << 8)`                           |
| 6     | `RW ← 1`, `AB ← PC`, `comienza la ejecución normal`     |

⚠️ Nota: El CPU no hace `fetch` de instrucciones válidas hasta que **RESET sube a 1**.

---

## 📦 Vector de Reset

- La dirección de inicio está en la dirección **$FFFC (low byte)** y **$FFFD (high byte)**
- Este vector apunta a la **rutina de arranque (boot code)**

Por ejemplo, si:
```
[FFFC] = $00
[FFFD] = $80
```
Entonces:
```
PC ← $8000
```
La próxima instrucción será buscada desde $8000.

---

## 🟡 Estado de los registros después del RESET

| Registro | Estado                  |
|----------|-------------------------|
| `A`, `X`, `Y` | Indeterminado       |
| `P` (status)  | `IRQ disabled`, `bit 5 = 1`, el resto indeterminado |
| `SP`          | `SP ← $FD`          |
| `PC`          | Cargado desde `$FFFC/$FFFD` |

---

## 📌 ¿Qué debe haber en $FFFC/$FFFD?

- Tu **programa de arranque** debe colocar ahí la dirección donde querés comenzar a ejecutar instrucciones.
- En un sistema real, esto suele apuntar a código de inicialización del sistema operativo o del juego (por ejemplo, en NES apunta al "start").

---

¿Querés que también te pase el flujo de `NMI` y `IRQ`? ¿O una rutina de ejemplo de arranque para una ROM?