# 🔒 Política de Seguridad

Este repositorio es **material educativo**, no un producto en producción. Aun así
contiene código C++ que gestiona memoria a mano (Semana 03), abre sockets (Semana 17)
y ejecuta fuzzers (Semana 18), así que trata los reportes de seguridad con seriedad.

## Qué reportar

| Tipo | Ejemplo | Canal |
| ---- | ------- | ----- |
| Secreto expuesto en este repo | Un token de CI commiteado por error | **Privado** (ver abajo) |
| Fallo en un script de `scripts/` que pueda dañar datos | Un `rm` sobre una ruta mal expandida | **Privado** |
| Starter con comportamiento indefinido explotable **sin marcar** | Un buffer overflow presentado como código correcto | **Privado** |
| Dependencia con `GIT_TAG` que apunta a algo que no es lo que dice | Un tag movido o un repositorio comprometido | **Privado** |
| Ejemplo que enseña una práctica insegura | Un servidor que escucha en `0.0.0.0` sin advertirlo | Issue público |
| Errata, código que no compila, enlace roto | Cualquier error de contenido | Issue público |

Regla: si publicarlo aumenta el daño, va en privado. Si publicarlo solo mejora el
material, va en issue público.

## Cómo reportar en privado

1. **Preferido**: pestaña `Security` → `Report a vulnerability` (private vulnerability
   reporting) del repositorio.
2. Alternativa: correo a **elparcheti@gmail.com** con asunto
   `[SECURITY] bc-cpp: <resumen>`.

Incluye: archivo y línea, impacto concreto, compilador y versión, y pasos para
reproducirlo (idealmente el comando de sanitizer o el input del fuzzer que lo dispara).

**Tiempo de respuesta esperado**: primer acuse en 7 días naturales.

## Seguridad del material de red y sistema

Las semanas 16-17 enseñan `fork`, `mmap`, sockets y un servidor HTTP. Dos cosas que el
material repite y que conviene tener claras:

1. **Los servidores de ejemplo escuchan en `127.0.0.1`.** Cambiarlo a `0.0.0.0` expone
   un parser HTTP de aprendizaje a tu red local. No lo hagas sin haber pasado la Semana
   18 (fuzzing y endurecimiento).
2. **Los fuzzers escriben ficheros `crash-*` y `leak-*`** en el directorio donde se
   ejecutan. Están en `.gitignore`; si uno acaba en un commit, contiene el input que
   rompe el programa y conviene tratarlo como un reporte, no como basura.

## Fuera de alcance

- Fallos de GCC, Clang, CMake o Catch2 como productos → repórtalos a sus proyectos.
- Vulnerabilidades en las bibliotecas que traen los starters por `FetchContent` (Asio,
  nlohmann/json, Benchmark) → a esos proyectos; aquí solo se actualiza el `GIT_TAG`.
- Problemas con las plataformas que alojan recursos externos → a esas plataformas.
