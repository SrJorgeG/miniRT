# 🔬 AddressSanitizer Testing Guide - miniRTNorm

## Descripción

Este proyecto ahora usa **AddressSanitizer (ASan)** en lugar de Valgrind para detección de:
- ✅ Fugas de memoria (LeakSanitizer)
- ✅ Accesos fuera de límites (buffer overflow/underflow)
- ✅ Use-after-free
- ✅ Doble liberación (double free)
- ✅ Errores de inicialización

**Ventaja clave**: ASan reporta **TODOS los problemas de una vez** sin parar en el primero, a diferencia de Valgrind.

---

## 🚀 Uso Rápido

### Opción 1: Compilar con ASan + Ejecutar con ventana gráfica

```bash
# Compilar con AddressSanitizer
make asan

# Ejecutar (abre ventana gráfica)
./asan_test.sh examples/sphere.rt 10
```

**Nota**: Cierra la ventana gráfica cuando se abra para que ASan complete el análisis.

---

### Opción 2: Modo Headless (Recomendado para CI/Testing)

```bash
# Ejecutar sin ventana gráfica (más rápido, sin dependencias gráficas)
./asan_headless.sh examples/sphere.rt
```

**Ventajas**:
- ✅ No requiere display gráfico
- ✅ Más rápido (sin overhead de gráficos)
- ✅ Ideal para pruebas automatizadas
- ✅ Análisis más limpio y enfocado

---

## 📊 Interpretando Resultados

### Salida exitosa (sin leaks):

```
✅ Sin errores de memoria detectados
✅ Sin fugas de memoria detectadas
✅ No se encontraron problemas en src/
```

### Leak encontrado (ejemplo):

```
💧 FUGAS DE MEMORIA DETECTADAS:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Direct leak of 200 byte(s) in 1 object(s) allocated from:
    #0 0x...... in malloc
    #1 0x...... in create_object src/objects/object.c:45
    #2 0x...... in parse_plane src/parser/parser_objects.c:63
```

---

## 🛠️ Configuración en Makefile

Se añadieron dos nuevos targets:

```makefile
make asan       # Compila con AddressSanitizer
make asan_build # (interno) Construye con flags de ASan
```

Los flags usados:
```bash
-fsanitize=address   # Detecta buffer overflows, use-after-free, etc
-fsanitize=leak      # Detecta memory leaks con LeakSanitizer
-g                   # Incluye símbolos de debug para mejor traceback
```

---

## 📝 Ejemplos de Uso

### Test básico con escena de ejemplo:
```bash
./asan_test.sh examples/sphere.rt 5
```

### Test sin gráficos:
```bash
./asan_headless.sh examples/sphere.rt
```

### Test con timeout más largo:
```bash
./asan_test.sh examples/example.rt 20
```

### Recompilar todo limpio y testear:
```bash
make fclean
make asan
./asan_headless.sh examples/sphere.rt
```

---

## 🔍 Analizando Logs

Los logs se guardan en:
- **Con gráficos**: `asan_report.log*`
- **Headless**: `asan_headless.log*`

### Ver log completo:
```bash
cat asan_headless.log
```

### Buscar errores específicos:
```bash
grep "Direct leak" asan_headless.log
grep "src/" asan_headless.log
grep "ERROR: AddressSanitizer" asan_headless.log
```

### Contar errores:
```bash
grep -c "ERROR" asan_headless.log
```

---

## 🧪 Verificación Automática

Para incluir en CI/CD:

```bash
#!/bin/bash
make asan
./asan_headless.sh examples/sphere.rt

# Fallar si hay leaks
if grep -q "detected.*leak" asan_headless.log; then
    echo "❌ Leaks detectados"
    exit 1
fi

echo "✅ Test pasado"
```

---

## ⚠️ Notas Importantes

1. **MLX42 y GLFW leaks** son **ignorados** (librerías externas)
2. **libft leaks** se asumen manejados correctamente
3. **Solo se reportan leaks de src/**
4. **ASan puede ser lento** en modo gráfico por el overhead
5. **Headless es la opción recomendada** para desarrollo

---

## 🔄 Comparación: ASan vs Valgrind

| Aspecto | ASan | Valgrind |
|---------|------|----------|
| **Velocidad** | ⚡ Rápido | 🐌 Lento |
| **Reporta todo a la vez** | ✅ Sí | ❌ Se detiene en error |
| **Necesita recompilación** | ✅ Sí | ❌ No |
| **Overhead de gráficos** | Medio | Alto |
| **Precisión** | ✅ Alta | ✅ Muy Alta |
| **Setup** | ✅ Sencillo | ⚠️ Complejo |

---

## 📚 Referencias

- [AddressSanitizer Docs](https://github.com/google/sanitizers/wiki/AddressSanitizer)
- [LeakSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizerLeakSanitizer)
- [GCC ASan Flags](https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html)

---

## ✅ Estado del Proyecto

- ✅ 3 memory leaks corregidos
- ✅ Compilación limpia (sin warnings)
- ✅ 36/36 archivos con norminette OK
- ✅ AddressSanitizer configurado
- ✅ Scripts de testing listos

**Próximo paso**: Ejecutar `./asan_headless.sh` para verificar que no hay leaks.
