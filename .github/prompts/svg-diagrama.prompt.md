---
mode: agent
description: Genera un diagrama SVG para 0-assets/ del bootcamp C++ Zero to Hero.
---

# Diagrama SVG

Genera `bootcamp/week-{{NN}}-{{SLUG}}/0-assets/{{MM}}-{{TEMA}}.svg`.

## Cuándo hace falta un diagrama

Cuando la prosa no basta: el pipeline de compilación, stack frente a heap, el layout de
un objeto, una vtable, el bloque de control de `shared_ptr`, una máquina de estados de
coroutine, un grafo de targets de CMake, una jerarquía de caché, un handshake TCP.

**No** hagas un diagrama para decorar. Un SVG que no aporte información que el texto no
tiene es ruido, y encima hay que mantenerlo. El número de SVG por semana es el que el
contenido pida.

Un SVG no enlazado desde ningún `.md` es un error que reporta `verificar-enlaces.sh`.

## Paleta obligatoria

```
fondo             #0d1117      texto              #e6edf3
superficie        #161b22      texto secundario   #8b949e
superficie alta   #21262d      texto atenuado     #484f58
borde             #30363d      acento (azul C++)  #659ad2
acento oscuro     #00599c      código             #79c0ff
éxito             #3fb950      advertencia        #d29922
error             #f85149      violeta (templates)#a371f7
stack             #4ade80      heap               #f0883e
```

Sin degradados. Colores sólidos. Tema oscuro, siempre.

- `stack`/`heap` se reservan para diagramas de memoria: un lector que vea verde sabe
  que es stack y naranja que es heap en todo el bootcamp.
- `violeta` para todo lo que ocurre **en tiempo de compilación**: instanciación de
  templates, `constexpr`, conceptos, `if constexpr`.
- `error` para UB, dangling, data races. `advertencia` para lo que compila pero huele.

## Plantilla

```svg
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 880 420" width="880" height="420" role="img"
     aria-label="Descripción larga y concreta de lo que muestra el diagrama, para lectores de pantalla">
  <title>Título corto del diagrama</title>
  <style>
    .bg    { fill: #0d1117; }
    .surf  { fill: #161b22; stroke: #30363d; stroke-width: 1; }
    .t     { font-family: Inter, Roboto, "Segoe UI", system-ui, sans-serif; }
    .code  { font-family: ui-monospace, "JetBrains Mono", Consolas, monospace; fill: #79c0ff; }
    .h     { font-size: 15px; font-weight: 600; fill: #e6edf3; }
    .s     { font-size: 12px; fill: #8b949e; }
    .edge  { stroke: #30363d; stroke-width: 2; fill: none; marker-end: url(#arrow); }
  </style>
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="8" markerHeight="8" orient="auto-start-reverse">
      <path d="M 0 0 L 10 5 L 0 10 z" fill="#8b949e"/>
    </marker>
  </defs>
  <rect class="bg" width="880" height="420" rx="12"/>
  <!-- contenido -->
</svg>
```

## Reglas técnicas

- **`viewBox` siempre**, con `width` y `height` que coincidan (coordenadas 1:1).
- **Ancho objetivo 800-880 px.** Alto entre 260 y 560 según el contenido.
- **`role="img"`, `<title>` y `aria-label`.** El `aria-label` describe lo que se ve,
  no repite el título. Es lo único que oye quien usa lector de pantalla.
- **Tipografía sans-serif del sistema**; monoespaciada solo para código. Nunca una
  fuente externa: el SVG tiene que renderizar igual en GitHub.
- **Texto mínimo 12 px.** Por debajo no se lee en el markdown renderizado.
- **Sin JavaScript, sin imágenes embebidas, sin fuentes remotas.**
- **Clases CSS reutilizadas**, no estilos en línea repetidos. El SVG tiene que poder
  leerse y editarse a mano.
- **Flechas con `<marker>`** definido una vez y reutilizado.
- **El código dentro del diagrama es C++ válido** y coincide con el de la teoría que
  lo enlaza. Un diagrama con `std::unique_ptr<T> p = new T;` es un bug.

## Nombres

`NN-tema-en-kebab-case.svg`, numerado por **orden de aparición** en la teoría de esa
semana. Sin acentos, sin mayúsculas.

Ejemplos del estilo que se busca:
`01-pipeline-de-compilacion.svg`, `02-stack-y-heap.svg`,
`03-bloque-de-control-shared-ptr.svg`, `04-maquina-de-estados-coroutine.svg`.

## Cómo se enlaza

Desde un archivo de `1-teoria/`, con ruta relativa y descripción accesible:

```markdown
![Descripción accesible del diagrama](../0-assets/{{MM}}-{{TEMA}}.svg)
```

## Verificación antes de entregar

- [ ] Solo colores de la paleta, sin degradados
- [ ] `viewBox`, `role="img"`, `<title>` y `aria-label` presentes
- [ ] Todo el texto en 12 px o más
- [ ] Sin JavaScript, sin fuentes ni imágenes externas
- [ ] El código del diagrama es C++20 válido
- [ ] Enlazado desde al menos un `.md`
- [ ] `./scripts/verificar-enlaces.sh` no lo reporta como huérfano
