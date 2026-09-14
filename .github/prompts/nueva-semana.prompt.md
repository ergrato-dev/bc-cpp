---
mode: agent
description: Genera el esqueleto completo de una semana del bootcamp C++ Zero to Hero.
---

# Nueva semana

Genera la estructura completa de la semana `{{NN}}` del bootcamp.

Antes de escribir nada, lee [`.github/copilot-instructions.md`](../copilot-instructions.md).
Es la fuente de verdad de la malla, las convenciones y las reglas de longitud.

## Entrada

- `{{NN}}` — número de semana con dos dígitos
- `{{SLUG}}` — slug en snake_case, tal y como aparece en la malla
- `{{TITULO}}` — título en español
- `{{FASE}}` — nombre de la fase a la que pertenece

Si alguno no se te da, sácalo de la tabla de la malla en `copilot-instructions.md`.
No inventes semanas nuevas ni cambies el temario declarado.

## Qué generar

```
bootcamp/week-{{NN}}-{{SLUG}}/
├── README.md
├── rubrica-evaluacion.md
├── 0-assets/
├── 1-teoria/
├── 2-practicas/ejercicio-NN-tema/{README.md, starter/}
├── 3-proyecto/{README.md, starter/}
├── 4-recursos/{ebooks-free,videografia,webgrafia}/README.md
└── 5-glosario/README.md
```

Genera **primero el `README.md`**, que es el índice del que cuelga todo lo demás, y
para en ese punto a que se revise. Luego, en tandas separadas: teoría, prácticas,
proyecto, recursos, glosario, rúbrica y SVG.

## El README de la semana: las 10 secciones, en este orden

1. `# Semana {{NN}} — {{TITULO}}` seguido de un blockquote de **una línea** que
   enganche: por qué esta semana importa, no un resumen de lo que contiene.
2. `## 🎯 Objetivos de la Semana` — "Al finalizar esta semana serás capaz de:" y una
   lista de verbos de acción concretos. Nada de "entender" o "conocer": *escribir*,
   *medir*, *elegir*, *detectar*, *diseñar*.
3. `## 📋 Prerrequisitos` — qué semanas anteriores hacen falta y qué herramientas
   (compilador, CMake, sanitizers) deben estar instaladas según `docs/setup.md`.
4. `## 🗂️ Estructura de la Semana` — el árbol real de archivos, con comentarios en línea.
5. `## 📝 Contenidos` — subsecciones `### Teoría` (tabla Archivo | Tema | Duración),
   `### Prácticas` (tabla Ejercicio | Qué haces | Duración) y `### Proyecto` (una línea
   con enlace). Las duraciones tienen que sumar con la sección 6.
6. `## ⏱️ Distribución del Tiempo (10 horas)` — tabla Actividad | Tiempo. **Suma
   exactamente 10 horas.**
7. `## 🎩 Trucos y atajos` — tabla Truco | Cómo. Mínimo cinco, de compilador, CMake,
   gdb, sanitizers, Compiler Explorer o editor. Cada uno se replica en
   `docs/trucos-cpp.md`.
8. `## 📌 Entregables` — lista numerada con ✅. Cada entregable se corresponde con un
   test de un starter o con un criterio de la rúbrica.
9. `## ✅ Verificación` — los comandos de compilación y tests:

   ```bash
   cmake --preset asan && cmake --build --preset asan && ctest --preset asan
   ```

10. `## 🔗 Navegación` — tabla Anterior | Actual | Siguiente, y la línea final
    `← [Volver al inicio del bootcamp](../../README.md)`.

Si la semana usa algo de C++23, añade entre 6 y 7 una sección
`## 🧪 Qué necesita C++23 esta semana` con la tabla Función | Qué hace | Alternativa en C++20.

## Reglas que no se negocian

- **10 horas exactas** en la distribución del tiempo.
- **Cero absoluto**: cada término nuevo se define donde aparece.
- **Progresión estricta**: nada de una semana posterior. Consulta la malla antes de
  usar un smart pointer, un template, una lambda, una excepción o un thread.
- **No inventes** funciones ni headers del estándar. Verifica en cppreference o dilo.
- La navegación anterior/siguiente tiene que apuntar a carpetas que existen.

## Al terminar

```bash
./scripts/verificar-enlaces.sh
./scripts/compilar-starters.sh week-{{NN}}
```

Y di explícitamente qué parte has entregado y qué falta.
