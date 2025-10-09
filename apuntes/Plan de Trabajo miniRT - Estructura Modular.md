## 🎯 Objetivo

Dividir el proyecto en módulos independientes que permitan trabajar en paralelo, con interfaces claras entre ellos.

---

## 📊 Fase 0: Definiciones Compartidas (HACER JUNTOS - 1 día)

**Qué**: Acordar las estructuras de datos principales que usarán todos los módulos.

**Estructuras necesarias**:

- Vector 3D (x, y, z)
- Color RGB
- Rayo (origen + dirección)
- Cámara (posición, orientación, FOV)
- Luz ambiental
- Luz puntual
- Cada tipo de objeto (esfera, plano, cilindro)
- Estructura principal de la escena

**Entregable**: Headers con todas las estructuras documentadas.

---

## 🧩 MÓDULO 1: Parsing (Persona A)

**Dependencias**: Solo las estructuras base  
**Puede empezar**: Inmediatamente después de Fase 0

### Tareas:

1. **Parser del archivo .rt**
    
    - Leer y validar el formato del archivo
    - Detectar elementos: C (cámara), A (luz ambiental), L (luz), sp, pl, cy
2. **Validación de datos**
    
    - Rangos de valores (FOV, ratios, colores 0-255)
    - Vectores normalizados donde corresponda
    - Números válidos
3. **Construcción de la escena**
    
    - Llenar la estructura de escena con todos los elementos parseados
    - Lista/array de objetos
    - Manejo de errores descriptivos

**Input**: Archivo .rt  
**Output**: Estructura de escena completa y validada

---

## 🧮 MÓDULO 2: Matemáticas Vectoriales (Persona B)

**Dependencias**: Solo la estructura de Vector3D  
**Puede empezar**: Inmediatamente después de Fase 0

### Tareas:

1. **Operaciones básicas**
    
    - Suma, resta, multiplicación por escalar
    - División por escalar
2. **Operaciones avanzadas**
    
    - Producto punto (dot product)
    - Producto cruz (cross product)
    - Normalización de vectores
    - Magnitud/longitud del vector
3. **Utilidades**
    
    - Calcular distancia entre puntos
    - Interpolación
    - Reflexión de vectores (para iluminación especular)

**Input**: Vectores  
**Output**: Funciones matemáticas reutilizables

---

## 🔫 MÓDULO 3: Sistema de Rayos (Persona A o B)

**Dependencias**: Módulo 2 (matemáticas)  
**Puede empezar**: Cuando termine Módulo 2

### Tareas:

1. **Generación de rayos**
    
    - Crear rayo desde cámara para cada píxel
    - Calcular dirección correcta según FOV
    - Sistema de coordenadas de cámara
2. **Transformaciones**
    
    - Rotar rayos según orientación de cámara
    - Calcular punto en el rayo dado un parámetro t

**Input**: Posición de píxel, datos de cámara  
**Output**: Rayo generado

---

## 🎱 MÓDULO 4: Intersecciones Geométricas (Persona A o B)

**Dependencias**: Módulo 2 (matemáticas)  
**Puede empezar**: Cuando termine Módulo 2

### Tareas:

1. **Intersección rayo-esfera**
    
    - Resolver ecuación cuadrática
    - Devolver punto de intersección más cercano
    - Calcular normal en el punto
2. **Intersección rayo-plano**
    
    - Detectar si el rayo intersecta
    - Punto de intersección
    - Normal (ya definida en el plano)
3. **Intersección rayo-cilindro**
    
    - Cuerpo del cilindro
    - Tapas superior e inferior
    - Calcular normal según la parte intersectada

**Input**: Rayo + objeto específico  
**Output**: Distancia t, punto de intersección, normal en ese punto

---

## 💡 MÓDULO 5: Iluminación (Persona A o B)

**Dependencias**: Módulos 2 y 4  
**Puede empezar**: Cuando terminen Módulos 2 y 4

### Tareas:

1. **Luz ambiental**
    
    - Componente constante de iluminación
2. **Luz difusa (Lambert)**
    
    - Calcular intensidad según ángulo luz-normal
    - Aplicar color de la luz
3. **Luz especular (Phong/Blinn-Phong)**
    
    - Brillos/reflejos
    - Calcular reflexión
4. **Sombras**
    
    - Lanzar rayo desde punto de intersección hacia cada luz
    - Detectar si hay objetos bloqueando

**Input**: Punto de intersección, normal, datos de luces, material  
**Output**: Color final del píxel

---

## 🖼️ MÓDULO 6: Motor de Renderizado (INTEGRACIÓN - Ambos)

**Dependencias**: TODOS los módulos anteriores  
**Puede empezar**: Cuando estén listos los demás módulos

### Tareas:

1. **Loop principal de renderizado**
    
    - Para cada píxel de la imagen
    - Generar rayo (Módulo 3)
    - Buscar intersección más cercana con todos los objetos (Módulo 4)
    - Si hay intersección, calcular iluminación (Módulo 5)
    - Pintar píxel
2. **Optimizaciones**
    
    - Solo calcular intersecciones necesarias
    - Límite de rebotes/profundidad

**Input**: Escena completa  
**Output**: Imagen renderizada

---

## 🛠️ MÓDULO 7: Utilidades y MiniLibX (Persona A o B)

**Dependencias**: Ninguna  
**Puede empezar**: En cualquier momento

### Tareas:

1. **Gestión de ventana**
    
    - Inicializar MiniLibX
    - Crear ventana
    - Manejar eventos (cerrar ventana, ESC)
2. **Gestión de imagen**
    
    - Crear buffer de imagen
    - Escribir píxeles
    - Mostrar imagen en ventana
3. **Utilidades generales**
    
    - Conversión de colores (float 0-1 a int 0-255)
    - Clamp de valores
    - Manejo de errores y memoria

---

## 📅 Plan de Desarrollo Sugerido

### Semana 1: Fundamentos

- **Día 1-2**: Fase 0 (juntos) - Definir estructuras
- **Día 3-5**:
    - Persona A → Módulo 1 (Parsing)
    - Persona B → Módulo 2 (Matemáticas)

### Semana 2: Rayos y Geometría

- **Día 1-3**:
    - Persona A → Módulo 3 (Rayos)
    - Persona B → Módulo 4 (Intersecciones)
- **Día 4-5**: Testing e integración de rayos + intersecciones

### Semana 3: Iluminación y Renderizado

- **Día 1-3**:
    - Persona A/B → Módulo 5 (Iluminación)
    - Persona B/A → Módulo 7 (MiniLibX)
- **Día 4-5**: Módulo 6 (Integración final - ambos)

### Semana 4: Pulido

- Testing exhaustivo
- Corrección de bugs
- Optimizaciones
- Norminette
- Escenas de prueba

---

## ✅ Checklist de Integración

Para cada módulo, antes de integrarlo:

- [ ] Compila sin errores
- [ ] Pasa la norminette
- [ ] Tiene casos de prueba básicos
- [ ] Está documentado (comentarios en funciones principales)
- [ ] No tiene memory leaks
- [ ] Las interfaces están claras y acordadas

---

## 🔗 Interfaces Críticas (Acordar antes de empezar)

### Parser → Renderizado

El parser debe entregar una estructura de escena lista para usar.

### Matemáticas → Todo

Las funciones matemáticas deben ser puras (sin efectos secundarios).

### Rayos + Intersecciones → Iluminación

Devolver punto, normal y objeto intersectado.

### Todo → Renderizado

El motor de renderizado orquesta todo, debe tener APIs claras.

---

## 💡 Consejos de Trabajo en Equipo

1. **Comunicación diaria**: Sincronización de 10 minutos al empezar
2. **Git branches**: Cada módulo en su rama
3. **Testing incremental**: No esperar a tener todo para probar
4. **Pair programming**: En las partes de integración críticas
5. **Documentar interfaces**: Antes de implementar, acordar qué recibe y qué devuelve cada función principal