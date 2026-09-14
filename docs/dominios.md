# 🏛️ Política de dominios únicos

Cada estudiante construye **su** sistema durante 20 semanas sobre **un dominio de
negocio propio**. Los ejercicios usan siempre un `Item` genérico; el proyecto semanal se
hace sobre el dominio del estudiante.

## Por qué

- **Anticopia**: dos proyectos de dominios distintos no se pueden copiar y pegar. Un
  `Book` con `isbn` y un `Room` con `floor` obligan a pensar, no a renombrar.
- **Transferencia**: adaptar `Item` a `Medicine` es exactamente el trabajo real de
  llevar un patrón a un problema concreto.
- **Motivación**: un dominio que el estudiante conoce da contexto a cada decisión de
  diseño.

## Cómo se asigna

- **Autoestudio**: el estudiante elige uno en la Semana 01 y lo escribe en el README
  de su repositorio. No se cambia después: el sistema se acumula 20 semanas.
- **Con instructor**: el instructor asigna un dominio distinto a cada estudiante del
  grupo. Con más de 15 estudiantes se combinan dominio + variante (por ejemplo
  "Biblioteca universitaria" y "Biblioteca municipal").

## Catálogo

| # | Dominio | Recurso principal | Campos típicos | Relaciones que aparecerán |
| - | ------- | ----------------- | -------------- | ------------------------- |
| 1 | 📚 Biblioteca | `Book` | `isbn`, `title`, `author`, `year`, `available` | `Loan`, `Member` |
| 2 | 💊 Farmacia | `Medicine` | `code`, `name`, `lab`, `expires_on`, `stock` | `Batch`, `Prescription` |
| 3 | 🏋️ Gimnasio | `Member` | `id`, `name`, `plan`, `joined_on`, `active` | `Session`, `Trainer` |
| 4 | 🏫 Escuela | `Student` | `id`, `name`, `grade`, `enrolled_on` | `Course`, `Grade` |
| 5 | 🐾 Tienda de mascotas | `Pet` | `id`, `species`, `name`, `age`, `price` | `Sale`, `Supplier` |
| 6 | 🍽️ Restaurante | `Dish` | `id`, `name`, `category`, `price`, `available` | `Order`, `Table` |
| 7 | 🏦 Banco | `Account` | `iban`, `owner`, `balance`, `opened_on` | `Transaction`, `Customer` |
| 8 | 🚕 Taxis | `Ride` | `id`, `origin`, `destination`, `distance_km`, `fare` | `Driver`, `Vehicle` |
| 9 | 🏥 Hospital | `Patient` | `id`, `name`, `birth_date`, `blood_type` | `Appointment`, `Doctor` |
| 10 | 🎬 Cine | `Movie` | `id`, `title`, `duration_min`, `rating` | `Screening`, `Ticket` |
| 11 | 🏨 Hotel | `Room` | `number`, `floor`, `kind`, `price_per_night`, `free` | `Booking`, `Guest` |
| 12 | ✈️ Viajes | `Trip` | `id`, `destination`, `departure`, `seats`, `price` | `Booking`, `Traveler` |
| 13 | 🚗 Concesionario | `Vehicle` | `vin`, `brand`, `model`, `year`, `price` | `Sale`, `Customer` |
| 14 | 👕 Ropa | `Garment` | `sku`, `name`, `size`, `color`, `stock` | `Order`, `Supplier` |
| 15 | 🔧 Taller | `Repair` | `id`, `plate`, `description`, `hours`, `done` | `Mechanic`, `Part` |
| 16 | 🎮 Videojuegos | `Game` | `id`, `title`, `platform`, `price`, `stock` | `Rental`, `Customer` |
| 17 | 🌱 Vivero | `Plant` | `id`, `species`, `pot_size`, `price`, `stock` | `Order`, `Supplier` |
| 18 | 📦 Mensajería | `Parcel` | `tracking`, `sender`, `recipient`, `weight_kg`, `status` | `Route`, `Courier` |
| 19 | 🎵 Escuela de música | `Instrument` | `id`, `kind`, `brand`, `rented` | `Lesson`, `Student` |
| 20 | 🏟️ Club deportivo | `Player` | `id`, `name`, `position`, `number` | `Match`, `Team` |

## Reglas

- **El recurso principal se define en la Semana 01** y el resto de tipos van
  apareciendo cuando la semana los pida (relaciones en la 05-06, jerarquías en la 06,
  índices en la 08...).
- **Los nombres son del dominio, en inglés**: `Book`, no `Item`; `isbn`, no `code`.
- **Los ejemplos del material siempre muestran al menos cinco dominios** en la sección
  `💡 Adaptación a tu dominio`, para que ninguno se quede sin referencia.
- **Copiar el proyecto de otro dominio** es 0 en Producto esa semana. Ver
  [`CODE_OF_CONDUCT.md`](../CODE_OF_CONDUCT.md).
