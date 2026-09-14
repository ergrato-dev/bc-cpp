---
name: verificar-estructura
description: Comprueba que una semana del bootcamp C++ Zero to Hero está completa, bien enlazada y compila antes de publicarla. Úsalo al terminar una semana o antes de abrir un pull request.
---

# Verificar estructura de una semana

Comprueba que `bootcamp/week-NN-*/` cumple el molde antes de darla por terminada.

## 1. Lo automático primero

```bash
./scripts/verificar-enlaces.sh
./scripts/compilar-starters.sh week-NN
```

El primero cubre: nombres de carpeta `week-NN-slug`, enlaces relativos que resuelven,
sección `Navegación` en cada README de semana, SVG huérfanos y ausencia de `solution/`.
El segundo configura, compila y ejecuta `ctest` en cada `starter/` de la semana, en
`debug` y `asan`.

Tienen que salir `OK: sin problemas detectados.` y `OK: N starters compilados.`. Si
no, arréglalo antes de seguir.

## 2. Archivos que tienen que existir

```
week-NN-slug/
├── README.md                              ← obligatorio
├── rubrica-evaluacion.md                  ← obligatorio
├── 0-assets/*.svg                         ← al menos uno, todos enlazados
├── 1-teoria/*.md                          ← los que pida el temario (4-6 normal)
├── 2-practicas/ejercicio-NN-tema/
│   ├── README.md                          ← obligatorio
│   └── starter/{CMakeLists.txt, CMakePresets.json, src/, tests/}
├── 3-proyecto/README.md                   ← obligatorio
├── 3-proyecto/starter/{CMakeLists.txt, CMakePresets.json, src/, tests/}
├── 4-recursos/ebooks-free/README.md
├── 4-recursos/videografia/README.md
├── 4-recursos/webgrafia/README.md
└── 5-glosario/README.md                   ← obligatorio
```

Y que **no** exista: ninguna carpeta `solution/`, ningún `build/` comiteado.

## 3. Las 10 secciones del README, en orden

1. `# Semana NN — Título` + blockquote gancho de una línea
2. `## 🎯 Objetivos de la Semana`
3. `## 📋 Prerrequisitos`
4. `## 🗂️ Estructura de la Semana`
5. `## 📝 Contenidos`
6. `## ⏱️ Distribución del Tiempo (10 horas)`
7. `## 🎩 Trucos y atajos`
8. `## 📌 Entregables`
9. `## ✅ Verificación`
10. `## 🔗 Navegación`

Opcional entre 6 y 7 si la semana toca C++23:
`## 🧪 Qué necesita C++23 esta semana`.

## 4. Comprobaciones que los scripts no hacen

- **Las horas suman 10 exactas** en la sección 6, y cuadran con las duraciones de la 5.
- **Cada teoría mide entre 200 y 300 líneas**:

  ```bash
  wc -l bootcamp/week-NN-*/1-teoria/*.md
  ```

- **Cada ejercicio** tiene, en cada paso, su **Por qué** y su **Verifica**, y los tests
  del starter están etiquetados por paso.
- **Cada ejercicio falla en tests, no en compilación**, con todo comentado. Y pasa al
  100 % con todo descomentado (el skill `compilar-starters` lo comprueba).
- **Ningún `// TODO:` en ejercicios; ningún código comentado "para descomentar" en
  proyectos.**
- **Las firmas** que exige `3-proyecto/README.md` coinciden con los `// TODO:` del
  `starter/`, carácter a carácter.
- **La rúbrica** tiene el cuestionario con sus respuestas en `<details>` y la tabla de
  penalizaciones estándar.
- **El glosario** es A-Z y da el término inglés del estándar entre paréntesis.
- **Los trucos** del README están replicados en `docs/trucos-cpp.md`.
- **Los recursos** llevan cada uno su línea de por qué vale la pena.
- **Todo UB** en la teoría está marcado con `// ❌ UB:` y su sanitizer.
- **Todo C++23** lleva su bloque `> [!NOTE] **C++23**` con alternativa en C++20.
- **La navegación** apunta a las semanas contiguas anterior y siguiente, y existen.

## 5. Informe

Lista de lo que falta, con la ruta. Sin elogios y sin proponer contenido: solo lo que
impide dar la semana por publicada.
