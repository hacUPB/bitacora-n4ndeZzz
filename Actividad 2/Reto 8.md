## 1. `int *pvar;`
- Declara una **variable puntero** llamada `pvar` que puede almacenar la **dirección de memoria** de un entero (`int`).
- No apunta a nada todavía (contiene basura si no se inicializa).
- Ejemplo mental: es como tener un papel donde anotar la dirección de una casa, pero aún no escribiste ninguna.

---

## 2. `pvar = var;`
- Intenta asignar a `pvar` el **valor de `var`**, no su dirección.
- Esto **normalmente es un error de compilación** si `var` es un `int` y no un puntero, porque `pvar` espera recibir una dirección, no un valor entero.
- Si `var` fuera un puntero, entonces se copiaría esa dirección.

---

## 3. `var2 = *pvar;`
- Lee el **contenido** de la dirección que guarda `pvar` y lo asigna a `var2`.
- `*pvar` significa “el valor al que apunta `pvar`”.
- Ejemplo: si `pvar` guarda la dirección de `var`, esto sería equivalente a `var2 = var;`.

---

## 4. `pvar = &var3;`
- Guarda en `pvar` la **dirección de memoria** de `var3`.
- Ahora `pvar` “apunta” a `var3`.
- Ejemplo: es como anotar en el papel la dirección de la casa de `var3`.
