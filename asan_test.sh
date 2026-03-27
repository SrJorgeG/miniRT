#!/bin/bash
# Script para ejecutar miniRT con AddressSanitizer (reporte completo sin parar)
# Uso: ./asan_test.sh [archivo_escena.rt] [timeout_segundos]
# Ejemplo: ./asan_test.sh examples/sphere.rt 10

set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_DIR"

# Parámetros
SCENE_FILE="${1:-examples/sphere.rt}"
TIMEOUT="${2:-10}"

# Verificar que la escena existe
if [ ! -f "$SCENE_FILE" ]; then
    echo "❌ Error: $SCENE_FILE no existe"
    echo "Uso: ./asan_test.sh [archivo_escena.rt] [timeout_segundos]"
    exit 1
fi

# Crear archivo de log
LOG_FILE="${PROJECT_DIR}/asan_report.log"

echo "═══════════════════════════════════════════════════════════════"
echo "🔧 AddressSanitizer - Memory Leak & Error Detection"
echo "═══════════════════════════════════════════════════════════════"
echo ""
echo "📋 Configuración:"
echo "   • Escena: $SCENE_FILE"
echo "   • Timeout: ${TIMEOUT}s"
echo "   • Log: $LOG_FILE"
echo ""
echo "🚀 Iniciando ejecución..."
echo ""
echo "⏱️  Nota: La aplicación se ejecutará por ${TIMEOUT} segundos"
echo "🪟 Si se abre la ventana gráfica, ciérrala para finalizar"
echo ""
echo "═══════════════════════════════════════════════════════════════"
echo ""

# Exportar variables para AddressSanitizer
export ASAN_OPTIONS="halt_on_error=0:verbosity=2:log_path=$LOG_FILE:detect_stack_use_after_return=1:strict_string_checks=1"
export LSAN_OPTIONS="verbosity=1:log_threads=1:report_objects=1"

# Ejecutar con timeout
timeout "$TIMEOUT" ./miniRT "$SCENE_FILE" 2>&1 || true

# Esperar a que se complete el análisis
sleep 2

echo ""
echo "═══════════════════════════════════════════════════════════════"
echo "✅ Ejecución completada"
echo "═══════════════════════════════════════════════════════════════"
echo ""

# Si el log fue creado (puede estar numerado por ASan)
if ls "${LOG_FILE}"* 1> /dev/null 2>&1; then
    # Buscar el archivo de log más reciente
    ACTUAL_LOG=$(ls -t "${LOG_FILE}"* 2>/dev/null | head -1)
    
    echo ""
    echo "📊 ANÁLISIS DE RESULTADOS:"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo ""
    
    # Mostrar resumen de LeakSanitizer
    echo "🔍 RESUMEN DE FUGAS DE MEMORIA (LeakSanitizer):"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    grep -A 200 "SUMMARY: LeakSanitizer" "$ACTUAL_LOG" 2>/dev/null || echo "ℹ️  No se encontraron fugas detectadas"
    
    echo ""
    echo "🛡️  ERRORES DE MEMORIA DETECTADOS (AddressSanitizer):"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    grep -A 20 "ERROR: AddressSanitizer" "$ACTUAL_LOG" 2>/dev/null || echo "✅ Sin errores de memoria detectados"
    
    echo ""
    echo "📍 FUGAS ESPECÍFICAS EN src/:"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    
    # Buscar líneas que contengan referencias a src/
    if grep -q "src/" "$ACTUAL_LOG" 2>/dev/null; then
        grep "src/" "$ACTUAL_LOG" | head -20 || echo "✅ No se encontraron referencias a src/"
    else
        echo "✅ No se encontraron fugas en código de src/"
    fi
    
    echo ""
    echo "═══════════════════════════════════════════════════════════════"
    echo "📄 LOG COMPLETO: $ACTUAL_LOG"
    echo "Para ver todo: cat $ACTUAL_LOG"
    echo "Para buscar un patrón: grep 'PATTERN' $ACTUAL_LOG"
    echo "═══════════════════════════════════════════════════════════════"
else
    echo "⚠️  No se generó archivo de log de ASan"
    echo "Probablemente no se detectaron problemas o el programa finalizó demasiado rápido"
fi
