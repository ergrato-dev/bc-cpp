---
mode: agent
description: Genera el mensaje de commit del bootcamp C++ Zero to Hero.
---

# Mensaje de commit

Genera el mensaje del commit a partir de los cambios preparados (`git diff --staged`).

## Formato

[Conventional Commits](https://www.conventionalcommits.org/):

```
<tipo>(<alcance>): <descripción en imperativo, español, sin punto final>

[cuerpo opcional: el porqué, no el qué]
```

## Tipos

| Tipo | Cuándo |
| ---- | ------ |
| `feat` | Contenido nuevo: una semana, una teoría, un ejercicio, un diagrama |
| `fix` | Corrección: errata, código que no compilaba, UB sin marcar, enlace roto, test mal etiquetado |
| `docs` | Cambios en `docs/`, `README.md`, `CONTRIBUTING.md` y compañía |
| `refactor` | Reorganización sin cambio de contenido |
| `chore` | Scripts, `.gitignore`, `.clang-format`, configuración del repositorio |

## Alcances

- `week-NN` para contenido de una semana concreta
- El nombre del documento para `docs/`: `docs(setup)`, `docs(politica-versiones)`
- `scripts` para el tooling
- `assets` para los recursos visuales globales

## Ejemplos reales

```
feat(week-01): contenido completo de la Semana 01 — toolchain y compilación
feat(week-05): añade el diagrama del bloque de control de shared_ptr
fix(week-03): marca como UB el ejemplo de lectura fuera de rango en la teoría 02

    UBSan lo reporta como index out of bounds pero el texto lo presentaba
    como "funciona en la práctica". Verificado con GCC 14.2 y Clang 18.1.

docs(politica-versiones): sube Catch2 a v3.16.0
chore(scripts): compilar-starters acepta un preset como segundo argumento
```

## Reglas

- **Español**, imperativo, sin punto final en la primera línea.
- **Primera línea de 72 caracteres o menos.** Si no cabe, el commit hace demasiadas cosas.
- **El cuerpo explica el porqué**, no repite el diff. Solo si aporta algo.
- **Cuando corrijas algo del compilador o del estándar, di la versión** donde lo
  verificaste (`Verificado con GCC 14.2`).
- **Nunca** menciones tokens, rutas absolutas de una máquina ni datos personales.
- Un commit por unidad de trabajo. Una semana completa puede ser un commit; una semana
  a medias más un arreglo de otra, no.
- Termina con las líneas de atribución que el agente tenga configuradas para la sesión,
  si las hay.
