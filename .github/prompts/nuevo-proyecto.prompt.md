---
mode: agent
description: Genera el README y el starter del proyecto semanal (capa del hilo conductor) del bootcamp C++ Zero to Hero.
---

# Nuevo proyecto semanal

Genera `bootcamp/week-{{NN}}-{{SLUG}}/3-proyecto/README.md` y `3-proyecto/starter/`.

Lee antes [`.github/copilot-instructions.md`](../copilot-instructions.md),
[`docs/proyecto-hilo-conductor.md`](../../docs/proyecto-hilo-conductor.md) y
[`docs/dominios.md`](../../docs/dominios.md).

## Qué es el proyecto semanal

**Una capa nueva sobre el mismo sistema que el estudiante construye durante 20
semanas**, en su dominio. Nunca un proyecto desechable. El ejercicio se hace sobre
`Item` y se tira; el proyecto se hace sobre el dominio propio y se queda.

| | Prácticas | Proyecto |
| --- | --- | --- |
| Recurso | `Item` genérico | El del dominio (`Book`, `Medicine`, `Room`...) |
| Guía | Paso a paso, descomentar | Requisitos + `// TODO:` con firma y pista |
| Tests | Escritos en el starter | El estudiante los escribe (mínimo indicado) |
| Vida | Se tira | Se acumula 20 semanas en el repo del estudiante |

## Estructura obligatoria del README

```markdown
# Proyecto — Semana {{NN}}: qué capa añades

> Una línea: qué tendrá tu sistema al terminar esta semana que no tenía antes.

## 📦 Qué añade esta semana

Qué capa es y por qué va aquí y no antes ni después.

## 📋 Requisitos verificables

Numerados. Cada uno es comprobable: compila, existe la función con esa firma, pasa un
test con ese nombre, produce esa salida.

## 🧪 Tests mínimos

Tabla Test | Qué comprueba. El estudiante los escribe con Catch2. Mínimo tres.

## 🎨 Criterios de calidad

Lo que `ctest` no puede ver, escrito como algo observable.

## 💡 Adaptación a tu dominio

Tabla Dominio | Recurso | Cómo se concreta, para al menos cinco dominios de
`docs/dominios.md`.

## 🚦 Cómo entregarlo

## 🧯 Errores comunes

| Error | Por qué pasa | Solución |

## 🔗 Navegación
```

## Starter del proyecto

```
3-proyecto/starter/
├── CMakeLists.txt          # mismo molde que los ejercicios
├── CMakePresets.json
├── src/
│   ├── main.cpp
│   ├── item.hpp            # NOTA PARA EL APRENDIZ: renombra a tu dominio
│   └── item.cpp
└── tests/
    └── test_item.cpp       # un test de ejemplo; el resto los escribe el estudiante
```

Formato del código:

```cpp
// NOTA PARA EL APRENDIZ: adapta `Item` a tu dominio
// (Book, Medicine, Member, Dish, Room...). Renombra tipo, archivo y campos.

// TODO: implementar la búsqueda por nombre.
// Firma esperada:
//   [[nodiscard]] std::optional<Item> Repository::find_by_name(std::string_view name) const;
// Pista: recorre items_ y compara item.name() con name. Devuelve std::nullopt si no hay.
```

Reglas del starter:

- **`// TODO:` con firma esperada y pista.** Nunca un TODO desnudo.
- **Compila con todos los TODOs sin hacer.** Los TODOs devuelven un valor neutro
  (`std::nullopt`, `{}`, `0`) hasta que se implementan; el test de ejemplo falla.
- **Ningún concepto de una semana posterior.**
- **El starter de la semana N asume el estado del proyecto tras la semana N-1**, pero
  es autocontenido: incluye lo mínimo de las capas previas para compilar solo.

## Reglas

- **Requisitos, no pasos.** El proyecto no se guía paso a paso: eso ya lo hicieron los
  ejercicios. Aquí se dice qué tiene que existir, con qué firma y qué test lo prueba.
- **Los criterios de calidad son observables.** Nunca "que quede bien". Sí:
  - "Ninguna función pasa `std::string` por valor cuando solo lo lee"
  - "`ctest --preset asan` pasa sin un solo reporte"
  - "El `Repository` no expone su `std::vector` interno en ninguna firma pública"
- **La adaptación por dominio no es opcional.** El estudiante eligió su dominio en la
  Semana 01; el proyecto tiene que servir para todos los de `docs/dominios.md`. Da un
  ejemplo breve por dominio, no un párrafo.
- **Entrega**: rama `week-{{NN}}` en el repositorio del estudiante, con `ctest` en verde
  en `debug` y `asan`.

## Errores comunes

Tabla obligatoria con al menos tres filas, sacadas de lo que falla de verdad al aplicar
esa capa sobre un dominio propio (nombres que colisionan, ownership mal repartido,
tests que dependen del orden, etc.).

## Verificación antes de entregar

- [ ] Cada requisito es comprobable por compilación, test o salida
- [ ] Cada criterio de calidad es observable
- [ ] Hay adaptación para al menos cinco dominios
- [ ] El starter compila con los TODOs sin hacer y el test de ejemplo falla
- [ ] `./scripts/compilar-starters.sh week-{{NN}}` pasa
- [ ] La tabla de errores comunes tiene al menos tres filas reales
- [ ] La capa encaja con la fase: no pide algo que se enseña dos semanas después
