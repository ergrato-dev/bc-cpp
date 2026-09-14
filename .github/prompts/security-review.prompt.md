---
mode: agent
description: Revisa el código de una semana del bootcamp C++ Zero to Hero buscando UB, gestión de memoria insegura y entrada sin validar.
---

# Revisión de seguridad

Revisa `bootcamp/week-{{NN}}-{{SLUG}}/` (teoría, starters de ejercicios y de proyecto).

Lee antes [`.github/copilot-instructions.md`](../copilot-instructions.md), sección
"Reglas de Seguridad y Rigor del Contenido".

## Por qué existe esta revisión

Un bootcamp de C++ enseña con el ejemplo. Un fragmento con un desbordamiento de buffer
"para simplificar" es lo que el estudiante copiará en su primer trabajo. Aquí no hay
código de ejemplo inseguro sin marcar.

## Qué buscar

### 1. Comportamiento indefinido sin marcar

- Lectura de variables sin inicializar
- Índices fuera de rango en arrays C o `operator[]` de contenedores
- Desbordamiento de enteros con signo
- Uso tras liberación, doble liberación, `delete` de `new[]`
- Referencias o `string_view` a temporales
- Data races: acceso concurrente sin sincronización
- Violación de aliasing estricto, `reinterpret_cast` a tipos incompatibles

Todo UB que aparezca debe estar en una sección de antipatrones, con `// ❌ UB:` y el
sanitizer o flag que lo detecta. Si no está marcado, es un hallazgo crítico.

### 2. Funciones inseguras de C

`gets`, `strcpy`, `strcat`, `sprintf`, `scanf("%s")`, `system()` con entrada externa,
`atoi` sin control de error. Si aparecen como código recomendado, hallazgo crítico. Si
aparecen como antipatrón, deben ir con su sustituto (`std::string`, `std::format`,
`std::from_chars`, `std::getline`).

### 3. Entrada sin validar

Todo `main(int argc, char** argv)`, toda lectura de fichero, socket o `std::cin`:

- ¿Se comprueba `argc` antes de leer `argv[1]`?
- ¿Se comprueba el estado del stream tras leer?
- ¿Se limita el tamaño de lo que se lee?
- ¿Se rechaza lo que no cumple el formato en vez de "seguir a ver"?

### 4. Gestión de recursos

- `new`/`delete` fuera de la Semana 03
- Recursos (ficheros, sockets, mutex) sin RAII
- `shared_ptr` con ciclos sin `weak_ptr`
- `unique_ptr` construido desde un puntero crudo que sigue vivo en otro sitio

### 5. Red y sistema (semanas 16-17)

- Servidores que escuchan en `0.0.0.0` sin advertencia explícita
- Buffers de recepción sin límite
- Parsers HTTP que confían en `Content-Length` sin acotarlo
- `fork` sin control de errores, señales sin `sigaction`

### 6. Dependencias

- `FetchContent_Declare` sin `GIT_TAG`, o con una rama en vez de un tag
- Descargas sin origen verificable

### 7. Verificación real

Compila cada starter con:

```bash
./scripts/compilar-starters.sh week-{{NN}} asan
```

Un reporte de ASan/UBSan en un test es un hallazgo crítico, esté o no en la lista.

## Formato del informe

Una línea por hallazgo, ordenadas por gravedad:

```
ruta:línea: 🔴 crítico: <problema>. <qué hacer>.
ruta:línea: 🟡 medio: <problema>. <qué hacer>.
ruta:línea: 🔵 menor: <problema>. <qué hacer>.
```

- 🔴 crítico: UB sin marcar, función insegura recomendada, sanitizer que reporta,
  dependencia sin tag
- 🟡 medio: entrada sin validar en un ejemplo, recurso sin RAII, ciclo de `shared_ptr`
- 🔵 menor: `[[nodiscard]]` que falta, cast de C, `using namespace std;` en un `.cpp`

Cita siempre **literalmente** la línea y di **cómo** lo verificaste (compilador y
flags, o sanitizer). Sin elogios, sin resumen ejecutivo. Si no hay hallazgos, di
exactamente qué revisaste y con qué comandos.
