# Codeforces - Repositorio de Soluciones

Este repositorio contiene soluciones a problemas de Codeforces con una plantilla optimizada para competencias de programación competitiva.

## ¿Para qué sirve #ifdef?

`#ifdef` es una directiva del preprocesador de C/C++ que significa "if defined" (si está definido). Permite incluir o excluir código de manera condicional durante la compilación.

### Sintaxis básica

```cpp
#ifdef NOMBRE_MACRO
    // Este código solo se compila si NOMBRE_MACRO está definido
#endif
```

### Uso en este repositorio

En el archivo `Plantilla.cpp`, utilizamos `#ifdef DEBUG` en dos lugares importantes:

#### 1. Activar verificaciones de depuración (líneas 1-3)

```cpp
#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif
```

**Propósito:** Cuando se compila con `-DDEBUG`, se activa `_GLIBCXX_DEBUG`, que habilita verificaciones adicionales en los contenedores de la STL (Standard Template Library). Esto ayuda a detectar:
- Acceso fuera de rango en vectores
- Iteradores inválidos
- Uso incorrecto de contenedores

#### 2. Sistema de depuración personalizado (líneas 10-14)

```cpp
#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 228
#endif
```

**Propósito:** 
- **Con DEBUG:** Incluye una librería de depuración que permite imprimir variables de manera formateada
- **Sin DEBUG:** Define `debug(...)` como una macro vacía (228), por lo que las llamadas a `debug()` no generan código

### Cómo compilar

#### Modo DEBUG (desarrollo/pruebas)

```bash
# Powershell
g++ -DDEBUG -std=c++17 -O3 -o main.exe "test.cpp"

# Bash
g++ -DDEBUG -std=c++17 -O3 -o main.exe "test.cpp"
```

En este modo:
- Se activan las verificaciones de la STL
- Las funciones `debug()` imprimen información
- Ideal para encontrar errores durante el desarrollo

#### Modo RELEASE (envío a Codeforces)

```bash
# Sin el flag -DDEBUG
g++ -std=c++17 -O3 -o main.exe "problema.cpp"
```

En este modo:
- No hay verificaciones extra (mayor velocidad)
- Las llamadas a `debug()` no generan código
- Código optimizado para el envío final

### Ventajas de usar #ifdef

1. **Un solo archivo fuente:** No necesitas mantener dos versiones del código
2. **Depuración sencilla:** Puedes agregar llamadas a `debug()` sin preocuparte por eliminarlas antes de enviar
3. **Seguridad:** Las verificaciones extra te ayudan a encontrar bugs antes de enviar
4. **Rendimiento:** El código final es igual de rápido porque las llamadas de debug no se compilan

### Ejemplo práctico

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> v(n);
    
    // Esta línea solo imprime cuando se compila con -DDEBUG
    debug(n, v);
    
    // Tu solución aquí
}
```

Cuando compilas con `-DDEBUG`: Verás la salida de debug
Cuando compilas sin `-DDEBUG`: La línea debug() se ignora completamente

## Comandos útiles

Ver los comandos de compilación comunes en el archivo `Apuntes.txt`.
