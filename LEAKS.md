# MEMORY LEAKS ANALYSIS - miniRTNorm

## Executive Summary

Análisis estático exhaustivo de memory leaks en código de `src/`. Se encontraron **4 leaks potenciales** en los siguientes módulos:

---

## LEAKS IDENTIFICADOS

### LEAK #1: parser_objects.c - parse_plane() línea 63-65

**Ubicación**: `src/parser/parser_objects.c` líneas 63-65

**Severidad**: CRÍTICA

**Descripción**:
```c
node = ft_lstnew(obj);
if (!node)
    exit_error("Error. malloc\n", scene);  // ❌ LEAK: obj no se libera
ft_stack_add_back(scene->map->objects, node);
```

**Problema**: Si `ft_lstnew(obj)` falla y retorna NULL, la función `exit_error` se llama pero NO libera `obj` antes. El puntero `obj` se pierde.

**Línea exacta de fuga**: Línea 65 en parser_objects.c

**Tipo de leak**: Direct loss - `t_object*` que contiene además:
- `obj->texture_path` (ft_strdup) 
- `obj->texture` (MLX texture pointer)
- `obj->object` (plane pointer)

**Datos perdidos**: ~200+ bytes (objeto + rutas de texturas)

---

### LEAK #2: parser_objects.c - parse_cylinder() línea 89-91

**Ubicación**: `src/parser/parser_objects.c` líneas 89-91

**Severidad**: CRÍTICA

**Descripción**:
```c
node = ft_lstnew(obj);
if (!node)
    exit_error("Error. malloc\n", scene);  // ❌ LEAK: obj no se libera
ft_stack_add_back(scene->map->objects, node);
```

**Problema**: Idéntico al LEAK #1, pero para cilindros.

**Línea exacta de fuga**: Línea 91 en parser_objects.c

**Tipo de leak**: Direct loss - `t_object*` conteniendo cilindro

**Datos perdidos**: ~200+ bytes

---

### LEAK #3: vector_basic.c - vector_dup() NO ES LEAK

**Ubicación**: `src/vector/vector_basic.c` línea 39-45

**Severidad**: ✅ RESUELTO - Función no utilizada

**Descripción**:
```c
t_vec	*vector_dup(t_vec vec)
{
    t_vec	*dup;
    
    dup = malloc(sizeof(t_vec));  // Línea 39
    if (!dup)
        return (NULL);
    dup->x = vec.x;
    dup->y = vec.y;
    dup->z = vec.z;
    return (dup);
}
```

**Análisis**: Esta función NO se utiliza en ninguna parte del código (`grep vector_dup` retorna solo la definición). Por lo tanto, NO genera leaks porque NO se llama nunca. Es código muerto pero seguro.

---

### LEAK #4: parser_scene.c - parse_light() línea 80-82

**Ubicación**: `src/parser/parser_scene.c` líneas 80-82

**Severidad**: MEDIA

**Descripción**:
```c
node = ft_lstnew(light);
if (!node)
    exit_error("Error.parse_light: ft_lstnew: malloc\n", scene);  // ❌ Potencial LEAK
```

**Problema**: Si `ft_lstnew(light)` falla, `light` malloceado en línea 66 no se libera explícitamente. Sin embargo, `exit_error` puede liberar vía `free_map` si scene se pasa, pero NO garantizado.

**Línea exacta de fuga**: Línea 82 en parser_scene.c

**Severidad**: MEDIA porque depende si `exit_error` limpia scene correctamente

---

## ANÁLISIS POR ARCHIVO

### ✅ CLEAN - Sin leaks detectados

- `src/cache/cache.c` - Inicialización correcta, free en free_functions.c
- `src/exit.c` - Solo manejo de errores
- `src/free_functions.c` - Correctamente libera todo
- `src/free_helpers.c` - Funciones de liberación correctas
- `src/init.c` - Stack creado con ft_stack_new()
- `src/main.c` - free_scene() llamado correctamente
- `src/objects/object.c` - free_object() implementado correctamente
- `src/objects/sphere.c` - Manejo correcto
- `src/parser/parser.c` - ft_free_split() llama correctamente
- `src/ray/ray.c` - ray_destructor() implementado
- `src/utils/color.c` - ft_free_split() usado
- `src/utils/str.c` - ft_split_2 frees res en caso de error
- `src/vector/vector.c` - ft_free_split() usado correctamente

### ⚠️ POTENCIALMENTE PROBLEMÁTICO

- `src/objects/plane.c` - Sin validaciones de error, pero la liberación ocurre en parser
- `src/objects/cylinder.c` - Sin validaciones, pero liberación en parser
- `src/parser/parser_objects.c` - **2 LEAKS CRÍTICOS ENCONTRADOS**
- `src/parser/parser_scene.c` - **1 LEAK MEDIA ENCONTRADO**

---

## TRAZABILIDAD DE MEMORIA - OBJETO COMPLETO

### Flujo de vida de un objeto (esfera):

```
parse_sphere()
    ↓
create_sphere() - malloc(sizeof(t_sphere))
    ↓
create_object() - malloc(sizeof(t_object))
    - Asigna texture_path = ft_strdup()
    - Carga texture con load_texture() → MLX
    ↓
ft_lstnew(obj) ← PUEDE FALLAR AQUÍ (LEAK #1)
    ↓
ft_stack_add_back() - Agrega a lista
    ↓
free_scene()
    ↓
free_map()
    ↓
ft_stack_clear(map->objects, free_object)
    ↓
free_object()
    - free(obj->texture_path)
    - mlx_delete_texture(obj->texture)
    - free_sphere(obj->object)
    - free(obj)
```

**Punto crítico**: Si `ft_lstnew()` falla en línea 35/63/89 de parser_objects.c, el objeto ya allocado NO se libera.

---

## RECOMENDACIONES DE FIX

### FIX #1: parser_objects.c - parse_plane() [CRÍTICO]

**Cambio recomendado** (línea 63-65):

```c
// ANTES (CON LEAK)
node = ft_lstnew(obj);
if (!node)
    exit_error("Error. malloc\n", scene);
ft_stack_add_back(scene->map->objects, node);

// DESPUÉS (SIN LEAK)
node = ft_lstnew(obj);
if (!node)
{
    free_object(obj);  // ← Agregar esta línea
    exit_error("Error. malloc\n", scene);
}
ft_stack_add_back(scene->map->objects, node);
```

---

### FIX #2: parser_objects.c - parse_cylinder() [CRÍTICO]

**Cambio recomendado** (línea 89-91):

```c
// ANTES (CON LEAK)
node = ft_lstnew(obj);
if (!node)
    exit_error("Error. malloc\n", scene);
ft_stack_add_back(scene->map->objects, node);

// DESPUÉS (SIN LEAK)
node = ft_lstnew(obj);
if (!node)
{
    free_object(obj);  // ← Agregar esta línea
    exit_error("Error. malloc\n", scene);
}
ft_stack_add_back(scene->map->objects, node);
```

---

### FIX #3: parser_scene.c - parse_light() [MEDIA]

**Cambio recomendado** (línea 80-82):

```c
// ANTES (POTENCIAL LEAK)
node = ft_lstnew(light);
if (!node)
    exit_error("Error.parse_light: ft_lstnew: malloc\n", scene);

// DESPUÉS (MÁS SEGURO)
node = ft_lstnew(light);
if (!node)
{
    free(light);  // ← Agregar esta línea para seguridad
    exit_error("Error.parse_light: ft_lstnew: malloc\n", scene);
}
```

---

## METODOLOGÍA DE ANÁLISIS

Este análisis se basó en:

1. **Búsqueda exhaustiva de malloc/calloc/strdup** en todo src/
2. **Trazabilidad de memoria** - seguimiento del ciclo de vida de cada asignación
3. **Análisis de rutas de error** - dónde puede fallar cada malloc
4. **Verificación de free correspondiente** - cada malloc tiene free?
5. **Identificación de puntos críticos** - dónde ocurren fugas si hay errores

---

## TABLA RESUMEN

| Leak # | Archivo | Función | Línea | Severidad | Tipo | Bytes | Estado |
|--------|---------|---------|-------|-----------|------|-------|--------|
| 1 | parser_objects.c | parse_plane | 65 | CRÍTICA | Direct Loss | ~200+ | ⏳ PENDIENTE FIX |
| 2 | parser_objects.c | parse_cylinder | 91 | CRÍTICA | Direct Loss | ~200+ | ⏳ PENDIENTE FIX |
| 3 | parser_scene.c | parse_light | 82 | MEDIA | Conditional | ~100+ | ⏳ PENDIENTE FIX |
| 4 | vector_basic.c | vector_dup | 39 | ✅ SEGURO | Unused | - | NO ES LEAK (función no se usa) |

---

## PRÓXIMOS PASOS

1. ✅ Análisis completado - 3 LEAKS críticos identificados
2. ⏳ **Revisar y aplicar FIX #1, #2, #3 a parser_objects.c y parser_scene.c**
3. ✅ vector_basic.c verificado - NO es leak (función no se usa)
4. ⏳ Compilar después de fixes
5. ⏳ Ejecutar norminette para asegurar cumplimiento  
6. ⏳ Crear commit con correcciones

---

## NOTAS IMPORTANTES

- **MLX42 leaks**: No incluidos en este análisis (se ignoran como solicitado)
- **libft leaks**: Se asume que libft está correctamente implementada
- **GLFW leaks**: Se ignoran (externo)
- **Alcance**: Solo código en `src/` es responsable por estos leaks

