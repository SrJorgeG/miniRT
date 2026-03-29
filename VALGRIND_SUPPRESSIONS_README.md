# Valgrind Suppressions Configuration

## Overview

El archivo `valgrind.supp` ha sido generado automáticamente para **suprimir SOLO** los memory issues provenientes de librerías externas (MLX42, X11, GLFW, LLVM, etc.), mientras que **mantiene visibles todos los leaks de tu código**.

## Statistics

- **Total suppressions en el archivo**: 2,248
- **Todas las suppressions**: De librerías externas (NOT de tu código)
- **Tu código seguirá mostrando leaks**: SÍ ✓

## Librerías Suprimidas

Las siguientes librerías tienen sus memory issues suprimidos:

- `libX11` - X11 display library
- `libglfw` - GLFW windowing library
- `libdxcore` - WSL DX core compatibility
- `libLLVM-15` - LLVM compiler infrastructure
- `libstdc++` - C++ standard library
- `swrast_dri` - Software rasterizer
- Dynamic linker (`dl_*` functions)

## Cómo Usar

### Ejecutar Valgrind con las suppressions:

```bash
valgrind --leak-check=full --suppressions=valgrind.supp ./miniRT <file.rt>
```

### Ver el reporte sin las suppressions externas:

```bash
valgrind --leak-check=full ./miniRT <file.rt>
```

## Qué Verás

Con `valgrind.supp` activo:

✓ **Leaks DE TU CÓDIGO se mostrarán**:
- `ft_realloc` (get_next_line)
- `parse_ambient_light` 
- `ft_lstnew` (parse_light)
- `vector_constructor` (setup_camera)
- Y cualquier otro leak de tu código

✗ **Leaks de librerías externas serán suprimidos**:
- Errores en X11, GLFW, LLVM initialization
- Memory reachable from system libraries
- Dynamic linker memory operations

## Generación del Archivo

El archivo fue generado usando un script Python que:

1. Parsea `val_log.log` para extraer todas las suppressions
2. Identifica cuales son de librerías externas usando keywords conocidas
3. Escribe SOLO las suppressions externas al archivo
4. Mantiene intactos los leaks del código fuente

## Mantenimiento

Si necesitas actualizar las suppressions después de cambios mayores:

```bash
# Regenerar el archivo
valgrind --leak-check=full --suppressions=valgrind.supp ./miniRT > val_log.log 2>&1
python3 scripts/generate_suppressions.py
```

## Notas Importantes

⚠️ **NO** se pueden ignorar leaks internos manualmente agregando suppressions aquí
- Cualquier suppression que agregues debe ser verificada
- Si agregaste una suppression de tu código por error, Valgrind seguirá mostrándola

✓ Para ver TODOS los leaks (incluyendo librerías):
```bash
valgrind --leak-check=full ./miniRT <file.rt>
```

✓ Para ver SOLO leaks de tu código:
```bash
valgrind --leak-check=full --suppressions=valgrind.supp ./miniRT <file.rt>
```
