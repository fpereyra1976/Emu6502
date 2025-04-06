Aquí tienes una tabla comparativa de los ciclos de reloj que toma la instrucción `LDA` en el 6502, dependiendo del **modo de direccionamiento** utilizado.  

| **Modo de Direccionamiento** | **Ejemplo**       | **Ciclos** | **Explicación Paso a Paso** |
|------------------------------|------------------|-----------|---------------------------|
| **Inmediato** (`#n`)         | `LDA #$12`       | **2**     | 1. Buscar instrucción (opcode).<br>2. Leer el operando inmediato. |
| **Zero Page** (`n`)          | `LDA $44`        | **3**     | 1. Buscar instrucción.<br>2. Leer dirección Zero Page.<br>3. Leer el valor desde la dirección. |
| **Zero Page,X** (`n,X`)      | `LDA $44,X`      | **4**     | 1. Buscar instrucción.<br>2. Leer dirección Zero Page.<br>3. Sumar X (cálculo interno).<br>4. Leer el valor desde la dirección calculada. |
| **Absoluto** (`nnnn`)        | `LDA $4400`      | **4**     | 1. Buscar instrucción.<br>2. Leer **byte bajo** de la dirección.<br>3. Leer **byte alto** de la dirección.<br>4. Leer el valor desde la dirección completa. |
| **Absoluto,X** (`nnnn,X`)    | `LDA $4400,X`    | **4 (+1 si cruce de página)** | 1. Buscar instrucción.<br>2. Leer **byte bajo** de la dirección.<br>3. Leer **byte alto** de la dirección.<br>4. Sumar X y acceder a la dirección (si hay cruce de página, +1 ciclo).<br>5. Leer el valor desde la dirección final. |
| **Absoluto,Y** (`nnnn,Y`)    | `LDA $4400,Y`    | **4 (+1 si cruce de página)** | Igual a `Absoluto,X`, pero usando Y en vez de X. |
| **Indirecto, X** (`(n,X)`)   | `LDA ($44,X)`    | **6**     | 1. Buscar instrucción.<br>2. Leer dirección base Zero Page.<br>3. Sumar X a la dirección (Zero Page wraparound si es necesario).<br>4. Leer **byte bajo** de la dirección final.<br>5. Leer **byte alto** de la dirección final.<br>6. Leer el valor desde la dirección final. |
| **Indirecto, Y** (`(n),Y`)   | `LDA ($44),Y`    | **5 (+1 si cruce de página)** | 1. Buscar instrucción.<br>2. Leer dirección base Zero Page.<br>3. Leer **byte bajo** de la dirección final.<br>4. Leer **byte alto** de la dirección final.<br>5. Sumar Y y acceder a la dirección (si hay cruce de página, +1 ciclo).<br>6. Leer el valor desde la dirección final. |

### **Notas importantes:**
- En **modos absolutos con indexación** (`Absoluto,X` y `Absoluto,Y`), se agrega **1 ciclo extra** si el desplazamiento cruza una página de memoria.
- En **modo Indirecto,X (`(n,X)`)**, la dirección efectiva se obtiene sumando X antes de leer la dirección final.
- En **modo Indirecto,Y (`(n),Y`)**, la dirección efectiva se obtiene antes de sumar Y, g++ -std=c++11 -Wall -Wextra -O2 -c main.cpp -o main.o
make: *** No rule to make target `cpu.o', needed by `cpu'.  Stop.lo que puede causar un **ciclo extra** si hay cruce de página.

Espero que esta tabla te ayude a entender mejor los ciclos de `LDA` en el 6502. ¡Si necesitas más detalles, dime! 🚀
