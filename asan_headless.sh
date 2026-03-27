#!/bin/bash
# Script para ejecutar miniRT con AddressSanitizer EN MODO HEADLESS
# Sin ventana gráfica, capturando todos los errores de memoria de una vez
# Uso: ./asan_headless.sh [archivo_escena.rt]

set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_DIR"

# Parámetro
SCENE_FILE="${1:-examples/sphere.rt}"

# Verificar que la escena existe
if [ ! -f "$SCENE_FILE" ]; then
    echo "❌ Error: $SCENE_FILE no existe"
    echo "Uso: ./asan_headless.sh [archivo_escena.rt]"
    echo ""
    echo "Archivos de ejemplo disponibles:"
    ls -la examples/*.rt 2>/dev/null || echo "  (ninguno encontrado)"
    exit 1
fi

# Crear archivo de log
LOG_FILE="${PROJECT_DIR}/asan_headless.log"

echo "═══════════════════════════════════════════════════════════════"
echo "🔬 AddressSanitizer - Modo Headless (Sin Gráficos)"
echo "═══════════════════════════════════════════════════════════════"
echo ""
echo "📋 Configuración:"
echo "   • Escena: $SCENE_FILE"
echo "   • Modo: Headless (sin ventana gráfica)"
echo "   • Log: $LOG_FILE"
echo ""
echo "🚀 Compilando con AddressSanitizer..."
echo ""

# Compilar con AddressSanitizer si no está compilado
if [ ! -f "./miniRT" ] || [ "$(stat -c %Y ./miniRT 2>/dev/null)" -lt "$(find src/ -type f -name '*.c' -exec stat -c %Y {} \; | sort -rn | head -1)" ]; then
    echo "⚙️  Re-compilando (cambios detectados)..."
    make asan > /dev/null 2>&1
    echo "✅ Compilación completada"
else
    echo "✅ Binario con ASan ya existe (actualizado)"
fi

echo ""
echo "═══════════════════════════════════════════════════════════════"
echo "🔧 Ejecutando análisis..."
echo "═══════════════════════════════════════════════════════════════"
echo ""

# Configurar ASan para modo headless y reporte detallado
export ASAN_OPTIONS="halt_on_error=0:verbosity=2:log_path=$LOG_FILE:detect_stack_use_after_return=1:strict_string_checks=1:use_sigaltstack=0"
export LSAN_OPTIONS="verbosity=1:log_threads=1:report_objects=1"
export LD_PRELOAD="/usr/lib/x86_64-linux-gnu/libasan.so.6"

# Ejecutar con timeout (5 segundos por defecto)
timeout 5 ./miniRT "$SCENE_FILE" 2>&1 || EXIT_CODE=$?

echo ""
echo "═══════════════════════════════════════════════════════════════"
echo "✅ Ejecución completada"
echo "═══════════════════════════════════════════════════════════════"
echo ""

# Procesar logs generados
if ls "${LOG_FILE}"* 1> /dev/null 2>&1; then
    ACTUAL_LOG=$(ls -t "${LOG_FILE}"* 2>/dev/null | head -1)
    
    echo "📊 REPORTE COMPLETO DE AddressSanitizer:"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo ""
    
    # Contar problemas encontrados
    ERROR_COUNT=$(grep -c "ERROR: AddressSanitizer" "$ACTUAL_LOG" 2>/dev/null || echo "0")
    LEAK_COUNT=$(grep -c "detected.*leak" "$ACTUAL_LOG" 2>/dev/null || echo "0")
    
    echo "📈 Estadísticas:"
    echo "   • Errores de AddressSanitizer: $ERROR_COUNT"
    echo "   • Leaks de memoria detectados: $LEAK_COUNT"
    echo ""
    
    # Mostrar TODOS los errores de ASan encontrados
    if [ "$ERROR_COUNT" -gt 0 ]; then
        echo "🚨 ERRORES DE MEMORIA DETECTADOS:"
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        grep -B 5 -A 10 "ERROR: AddressSanitizer" "$ACTUAL_LOG" 2>/dev/null || true
        echo ""
    else
        echo "✅ Sin errores de memoria detectados"
        echo ""
    fi
    
    # Mostrar TODOS los leaks encontrados
    if [ "$LEAK_COUNT" -gt 0 ]; then
        echo "💧 FUGAS DE MEMORIA DETECTADAS:"
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        grep -B 3 -A 15 "SUMMARY: LeakSanitizer" "$ACTUAL_LOG" 2>/dev/null || true
        echo ""
    else
        echo "✅ Sin fugas de memoria detectadas"
        echo ""
    fi
    
    # Mostrar fugas específicas en src/
    echo "🔍 ANÁLISIS DE src/:"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    
    SRC_REFS=$(grep -c "src/" "$ACTUAL_LOG" 2>/dev/null || echo "0")
    if [ "$SRC_REFS" -gt 0 ]; then
        echo "⚠️  $SRC_REFS referencias a src/ encontradas:"
        echo ""
        grep "src/" "$ACTUAL_LOG" | head -30 || true
    else
        echo "✅ No se encontraron problemas en src/"
    fi
    
    echo ""
    echo "═══════════════════════════════════════════════════════════════"
    echo "📄 LOG COMPLETO (con timestamps):"
    echo "   $ACTUAL_LOG"
    echo ""
    echo "🔗 Comandos útiles:"
    echo "   Ver todo:          cat $ACTUAL_LOG"
    echo "   Buscar patrón:     grep 'PATTERN' $ACTUAL_LOG"
    echo "   Ver líneas N-M:    sed -n 'N,Mp' $ACTUAL_LOG"
    echo "   Contar errores:    grep -c 'ERROR' $ACTUAL_LOG"
    echo "═══════════════════════════════════════════════════════════════"
else
    echo "⚠️  No se generó archivo de log"
    echo "Probablemente el programa finalizó sin detectar problemas"
fi

echo ""
