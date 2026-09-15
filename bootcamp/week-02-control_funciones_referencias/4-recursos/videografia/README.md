# 🎬 Videografía — Semana 02: Control de flujo, funciones y referencias

Charlas y vídeos, con la razón de cada uno. Los enlaces apuntan al canal; busca el
título exacto ahí (los identificadores de vídeo de YouTube cambian y se rompen).

---

### Kate Gregory — *It's Complicated* (Meeting C++ 2017)

- **Canal**: Meeting C++ — https://www.youtube.com/@MeetingCPP
- **Duración**: ~1 h
- **Por qué verlo**: sobre cómo decidir qué va en una función, cómo nombrarla y por
  qué "una función hace una cosa" no es una regla de estilo sino de supervivencia.
  Míralo después de la Teoría 02, antes de repartir el proyecto en funciones.

---

### Klaus Iglberger — *Back to Basics: Designing Classes* (CppCon 2021), primeros 20 minutos

- **Canal**: CppCon — https://www.youtube.com/@CppCon
- **Duración**: ~1 h (esta semana, solo el principio)
- **Por qué verlo**: los primeros veinte minutos son sobre **funciones libres**
  frente a miembros, y explican por qué esta semana el proyecto se escribe con
  funciones que reciben el `vector` por referencia y no con una clase. El resto es
  de la Semana 04; párala cuando entre en clases.

---

### Herb Sutter — *Back to Basics! Essentials of Modern C++ Style* (CppCon 2014)

- **Canal**: CppCon — https://www.youtube.com/@CppCon
- **Duración**: ~1 h 40 min (esta semana, la primera media hora)
- **Por qué verlo**: la primera parte es la tabla de "¿cómo paso este parámetro?" de
  la Teoría 02 explicada por quien preside el comité del estándar: valor, `const&`,
  `&`, y por qué devolver por valor está bien. El resto (smart pointers, `auto`,
  movimiento) es de las Semanas 05 en adelante; vuelve a él entonces.

---

### Chandler Carruth — *Garbage In, Garbage Out: Arguing about Undefined Behavior with Nasal Demons* (CppCon 2016)

- **Canal**: CppCon — https://www.youtube.com/@CppCon
- **Duración**: ~1 h
- **Por qué verlo**: el mantenedor de Clang explica por qué el UB existe, qué gana el
  compilador con él y por qué "funciona en mi máquina" no es un argumento. Es la
  Teoría 06 contada por quien escribe el optimizador.

---

### The Cherno — *Functions in C++*, *Variables in C++*, *References in C++*

- **Canal**: The Cherno — https://www.youtube.com/@TheCherno
- **Duración**: ~10 min cada uno
- **Por qué verlo**: los tres vídeos cortos de su serie sobre lo de esta semana, con
  el depurador de Visual Studio mostrando la memoria en directo. El de referencias
  enseña visualmente que una referencia **es** la otra variable. Ojo: la serie usa
  `char*` y `new` en otros vídeos; quédate con estos tres.
