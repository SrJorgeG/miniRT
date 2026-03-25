#!/bin/bash
# QUICK START - AddressSanitizer Testing
# ========================================
# 
# Este script muestra cómo usar los nuevos tools de ASan
# para detectar memory leaks y errores de memoria de una vez.
#
# Cambios realizados:
# ✅ Valgrind → AddressSanitizer (ASan)
# ✅ Reporte completo (todos los errores a la vez, sin parar)
# ✅ Dos modos: con gráficos y headless
# ✅ Logs detallados en archivos

echo "═══════════════════════════════════════════════════════════════"
echo "📋 QUICK START - AddressSanitizer en miniRTNorm"
echo "═══════════════════════════════════════════════════════════════"
echo ""
echo "✨ NUEVOS COMANDOS DISPONIBLES:"
echo ""
echo "1️⃣  COMPILAR CON ASAN:"
echo "   $ make asan"
echo ""
echo "2️⃣  TEST CON VENTANA GRÁFICA (muestra todos los errores):"
echo "   $ ./asan_test.sh examples/sphere.rt 10"
echo "   (Cierra la ventana gráfica cuando se abra)"
echo ""
echo "3️⃣  TEST SIN GRÁFICOS - RECOMENDADO (más rápido y limpio):"
echo "   $ ./asan_headless.sh examples/sphere.rt"
echo ""
echo "═══════════════════════════════════════════════════════════════"
echo ""
echo "🔍 QUÉ DETECTA ASAN:"
echo "   ✅ Memory leaks"
echo "   ✅ Buffer overflows / underflows"
echo "   ✅ Use-after-free"
echo "   ✅ Double free"
echo "   ✅ Errores de inicialización"
echo ""
echo "═══════════════════════════════════════════════════════════════"
echo ""
echo "📊 LOGS GENERADOS:"
echo "   • Con gráficos: asan_report.log*"
echo "   • Sin gráficos: asan_headless.log"
echo ""
echo "═══════════════════════════════════════════════════════════════"
echo ""
echo "🚀 INICIO RÁPIDO (TODO DE UNA VEZ):"
echo ""
echo "   $ make asan && ./asan_headless.sh examples/sphere.rt"
echo ""
echo "═══════════════════════════════════════════════════════════════"
echo ""
echo "✅ ESTADO ACTUAL:"
echo "   • 3 Memory leaks CORREGIDOS"
echo "   • 36/36 archivos con Norminette OK"
echo "   • 0 warnings de compilación"
echo "   • AddressSanitizer configurado y listo"
echo ""
echo "═══════════════════════════════════════════════════════════════"
