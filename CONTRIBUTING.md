# 🤝 Cómo contribuir

Gracias por querer mejorar esto. El material se escribe para gente que empieza de cero,
así que la contribución más valiosa suele ser la más aburrida: un fragmento que ya no
compila con el compilador nuevo, un término que se usa sin haberlo definido, un ejemplo
con comportamiento indefinido sin marcar, un enlace roto.

---

## Qué se acepta

- **Erratas y correcciones.** Ortografía, gramática, enlaces rotos.
- **Código que no compila** o **diagnósticos que ya no coinciden** con GCC/Clang
  actuales. Indica **la versión exacta** del compilador donde lo comprobaste.
- **UB sin marcar.** Si un ejemplo tiene comportamiento indefinido y no lleva
  `// ❌ UB:` con su sanitizer, eso es un fallo de contenido y se arregla.
- **Términos usados sin definir.** Si algo se explica asumiendo vocabulario que el
  bootcamp no ha enseñado todavía, es un fallo de progresión.
- **Recursos nuevos** para `4-recursos/`, siempre con una línea de por qué valen la pena
  y con su licencia verificada.
- **Trucos** que cumplan el criterio de admisión: ahorran tiempo real o revelan algo
  que el compilador, CMake o gdb esconden. Ver `.github/copilot-instructions.md`.
- **Mejoras a los scripts** de `scripts/` y a las plantillas de `docs/plantillas/`.
- **Actualizaciones de versiones** de dependencias, siguiendo
  [`docs/politica-versiones.md`](docs/politica-versiones.md).

## Qué no se acepta

- Reescrituras de estilo sin cambio de contenido.
- Semanas nuevas o reordenaciones de la malla curricular sin discusión previa en un
  issue. La malla está dimensionada por horas y cambiarla afecta a las 20 semanas.
- Carpetas `solution/`. Los ejercicios se resuelven descomentando; el proyecto lo
  resuelve cada estudiante en su dominio.
- Dependencias nuevas en los starters para algo que la biblioteca estándar ya hace.
- Cambios a `.clang-format` por preferencia personal.
- Ejemplos que dependan de extensiones del compilador (`__attribute__`, VLAs, `typeof`).

---

## Antes de escribir nada

Lee **[`.github/copilot-instructions.md`](.github/copilot-instructions.md)**. Es el
molde completo: estructura de una semana, longitudes, convenciones de código y de
escritura, paleta de los SVG y reglas de seguridad del contenido. Casi todas las
revisiones que se piden en un pull request están ya respondidas ahí.

---

## Flujo

1. **Abre un issue primero** si el cambio es de contenido, no de errata. Ahorra trabajo
   a todo el mundo.
2. Haz un *fork* y crea una rama:

   ```bash
   git switch -c fix/week-03-dangling-span
   ```

   Nombre de rama en inglés, kebab-case, con la semana si aplica.

3. Escribe el cambio. Si tocas contenido de una semana, respeta su estructura.

4. **Verifica antes de abrir el pull request**:

   ```bash
   ./scripts/verificar-enlaces.sh
   ./scripts/compilar-starters.sh week-NN
   ```

   El primero comprueba nombres de carpeta, enlaces relativos, navegación, SVG
   huérfanos, carpetas prohibidas y `GIT_TAG` exactos. Tiene que salir
   `OK: sin problemas detectados.`. El segundo compila y ejecuta los tests de cada
   starter de la semana en `debug` y `asan`.

   Si has tocado un fragmento de teoría, **compílalo**:

   ```bash
   g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -fsyntax-only fragmento.cpp
   ```

   Un fragmento que nunca se ha compilado no está probado.

5. Commit siguiendo [Conventional Commits](https://www.conventionalcommits.org/):

   ```
   <tipo>(<alcance>): <descripción>
   ```

   Ejemplos reales:

   ```
   fix(week-03): marca como UB el ejemplo de string_view a temporal
   docs(setup): añade la ruta con apt.llvm.org para Ubuntu 22.04
   feat(week-05): contenido completo de la Semana 05
   ```

   Tipos: `feat`, `fix`, `docs`, `refactor`, `chore`.

6. Abre el pull request describiendo **qué cambia y por qué**, y con qué compilador y
   versión lo has comprobado.

---

## Checklist antes de abrir el pull request

- [ ] `./scripts/verificar-enlaces.sh` sin errores
- [ ] `./scripts/compilar-starters.sh week-NN` en verde si toqué un starter
- [ ] Los fragmentos de código que toco los he compilado, no deducido
- [ ] Digo en el PR con qué compilador y versión lo he verificado
- [ ] Cada término técnico nuevo queda definido donde aparece
- [ ] Ningún concepto de una semana posterior sin su aviso
- [ ] Todo UB va marcado con `// ❌ UB:` y su sanitizer
- [ ] Si toco algo de C++23, lleva su bloque de aviso y su alternativa en C++20
- [ ] Los SVG nuevos usan la paleta del bootcamp y están enlazados desde algún `.md`
- [ ] Los trucos nuevos están replicados en `docs/trucos-cpp.md`
- [ ] El commit sigue Conventional Commits

---

## Licencia de las contribuciones

Al contribuir aceptas que tu aportación se publique bajo la misma licencia del
repositorio: [CC BY-NC-SA 4.0](LICENSE).
