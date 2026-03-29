# miniRT - Ray Tracing Engine

Un proyecto de ray tracing desarrollado en C como parte del currículo de 42. El objetivo es crear un motor de renderizado capaz de generar imágenes 3D mediante trazado de rayos.

## 📋 Características

- **Trazado de rayos (Ray Tracing)**: Algoritmo de renderizado que simula la propagación de luz
- **Soporte de múltiples objetos**: Esferas, planos, cilindros y más
- **Iluminación realista**: Cálculo de sombras, reflexiones y reflejos
- **Manejo de archivos .rt**: Parser para escenas definidas en archivos
- **Optimización de rendimiento**: Algoritmos eficientes para cálculos de intersecciones

## 🛠️ Requisitos

- GCC/Clang
- Make
- Librerías estándar de C (POSIX)
- MLX42 (para renderizado gráfico)

## 📦 Instalación

```bash
git clone <repository_url>
cd miniRT
make
```

## 🚀 Uso

```bash
./miniRT <archivo_escena.rt>
```

### Formato de archivo .rt

El archivo de configuración define la escena:

```
R 800 600              # Resolución (Ancho Alto)
A 0.2 255,255,255    # Luz ambiental (intensidad, color RGB)
c -50,0,20 0,0,0 70  # Cámara (posición, dirección, FOV)
l -40,0,30 0.7 255,255,255  # Luz (posición, intensidad, color)
sp 0,0,0 20 255,0,0   # Esfera (posición, radio, color)
pl 0,0,-30 0,0,1 0,255,0    # Plano (posición, normal, color)
cy 0,0,0 0,1,0 5 20 255,255,0  # Cilindro (posición, eje, radio, altura, color)
```

## 📁 Estructura del Proyecto

```
miniRT/
├── src/
│   ├── main.c           # Punto de entrada
│   ├── parser/          # Parser de archivos .rt
│   ├── render/          # Motor de ray tracing
│   ├── math/            # Operaciones matemáticas (vectores, matrices)
│   ├── objects/         # Definición de objetos 3D
│   ├── lighting/        # Cálculos de iluminación
│   ├── utils/           # Funciones utilitarias
│   └── ...
├── include/
│   └── minirt.h         # Headers principales
├── Makefile
├── valgrind.supp        # Supresor de falsos positivos de Valgrind
└── README.md
```

## 🔍 Funciones Clave

### Parser
- `parse_scene()`: Parsea el archivo de configuración
- `parse_object()`: Procesa cada línea del archivo

### Matemáticas
- `vector_add()`, `vector_sub()`: Operaciones vectoriales
- `dot_product()`, `cross_product()`: Productos escalar y vectorial
- `normalize()`: Normalización de vectores

### Ray Tracing
- `trace_ray()`: Traza un rayo a través de la escena
- `intersect_sphere()`: Calcula intersección rayo-esfera
- `intersect_plane()`: Calcula intersección rayo-plano
- `compute_lighting()`: Calcula iluminación en un punto

### Utilidades
- `ft_split_2()`: Divide strings por múltiples delimitadores
- `free_split_2()`: Libera memoria de split_2

## 🧪 Pruebas

```bash
make test           # Ejecutar pruebas (si están implementadas)
valgrind ./miniRT scene.rt  # Verificar fugas de memoria
```

## 📊 Validación de Memoria

El proyecto utiliza Valgrind para detectar fugas de memoria:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./miniRT scene.rt
```

Consulta `valgrind.supp` para los supresores configurados.

## 🤝 Autor

- **dcid-san** - Estudiante de 42 Madrid

## 📝 Licencia

Este proyecto es parte del currículo de 42 y sigue sus normas de código.

## 🎯 Próximas Mejoras

- [ ] Soporte para texturas
- [ ] Reflejos y refracciones mejorados
- [ ] Objetos adicionales (conos, toros)
- [ ] Optimización con BVH tree
- [ ] Parallelización del renderizado

---

**Nota**: Este proyecto es parte de la escuela 42 y debe cumplir con sus normas de codificación (Norminette).
