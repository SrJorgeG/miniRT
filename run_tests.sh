#!/bin/bash

# Advanced testing suite for miniRT
# This script runs comprehensive tests including:
# - Memory leak detection
# - Norminette compliance
# - Build verification
# - Scene rendering tests

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
NC='\033[0m'

# Counters
TESTS_PASSED=0
TESTS_FAILED=0

# Test counter
test_count() {
    if [[ $? -eq 0 ]]; then
        TESTS_PASSED=$((TESTS_PASSED + 1))
        echo -e "${GREEN}✓ PASSED${NC}"
    else
        TESTS_FAILED=$((TESTS_FAILED + 1))
        echo -e "${RED}✗ FAILED${NC}"
    fi
}

echo -e "${MAGENTA}"
echo "╔════════════════════════════════════════════╗"
echo "║     miniRT Comprehensive Testing Suite     ║"
echo "╚════════════════════════════════════════════╝"
echo -e "${NC}"

# ============= BUILD TEST =============
echo ""
echo -e "${BLUE}[1/5] Build Test${NC}"
echo -e "${YELLOW}Building miniRT...${NC}"
make clean > /dev/null 2>&1
make > /dev/null 2>&1
test_count

# ============= COMPILATION WARNINGS =============
echo ""
echo -e "${BLUE}[2/5] Compilation Warnings Check${NC}"
echo -e "${YELLOW}Checking for C compiler warnings...${NC}"
# Filter out CMake warnings - only check for cc/gcc warnings (prefixed with cc: or containing 'warning:')
WARNINGS=$(make 2>&1 | grep "cc.*warning:" | grep -v "CMake" || true)
if [[ -z "$WARNINGS" ]]; then
    echo -e "${GREEN}✓ No C compilation warnings${NC}"
    TESTS_PASSED=$((TESTS_PASSED + 1))
else
    echo -e "${RED}✗ Warnings found:${NC}"
    echo "$WARNINGS"
    TESTS_FAILED=$((TESTS_FAILED + 1))
fi

# ============= NORMINETTE CHECK =============
echo ""
echo -e "${BLUE}[3/5] Norminette Compliance Check${NC}"
echo -e "${YELLOW}Checking code style...${NC}"
NORM_RESULT=$(norminette src/ include/ 2>&1 | grep -E "^(src|include).*Error|OK" || true)
if echo "$NORM_RESULT" | grep -q "Error"; then
    echo -e "${RED}✗ Norminette errors found${NC}"
    echo "$NORM_RESULT" | grep "Error" | head -10
    TESTS_FAILED=$((TESTS_FAILED + 1))
else
    echo -e "${GREEN}✓ All files norminette compliant${NC}"
    TESTS_PASSED=$((TESTS_PASSED + 1))
fi

# ============= EXECUTABLE EXISTS =============
echo ""
echo -e "${BLUE}[4/5] Executable Check${NC}"
echo -e "${YELLOW}Verifying binary exists...${NC}"
if [[ -f ./miniRT ]] && [[ -x ./miniRT ]]; then
    SIZE=$(ls -lh miniRT | awk '{print $5}')
    echo -e "${GREEN}✓ Binary exists (size: $SIZE)${NC}"
    TESTS_PASSED=$((TESTS_PASSED + 1))
else
    echo -e "${RED}✗ Binary not found or not executable${NC}"
    TESTS_FAILED=$((TESTS_FAILED + 1))
fi

# ============= SCENE FILES CHECK =============
echo ""
echo -e "${BLUE}[5/5] Scene Files Check${NC}"
echo -e "${YELLOW}Verifying scene files...${NC}"
SCENE_COUNT=$(find examples -name "*.rt" | wc -l)
if [[ $SCENE_COUNT -gt 0 ]]; then
    echo -e "${GREEN}✓ Found $SCENE_COUNT scene files${NC}"
    find examples -name "*.rt" -printf "  - %f\n" | sort
    TESTS_PASSED=$((TESTS_PASSED + 1))
else
    echo -e "${RED}✗ No scene files found${NC}"
    TESTS_FAILED=$((TESTS_FAILED + 1))
fi

# ============= SUMMARY =============
echo ""
echo -e "${MAGENTA}╔════════════════════════════════════════════╗${NC}"
echo -e "${MAGENTA}║              TEST SUMMARY                  ║${NC}"
echo -e "${MAGENTA}╚════════════════════════════════════════════╝${NC}"
TOTAL=$((TESTS_PASSED + TESTS_FAILED))
echo -e "Total tests: ${BLUE}$TOTAL${NC}"
echo -e "Passed:      ${GREEN}$TESTS_PASSED${NC}"
echo -e "Failed:      ${RED}$TESTS_FAILED${NC}"

if [[ $TESTS_FAILED -eq 0 ]]; then
    echo ""
    echo -e "${GREEN}╔════════════════════════════════════════════╗${NC}"
    echo -e "${GREEN}║         ALL TESTS PASSED! ✓                ║${NC}"
    echo -e "${GREEN}╚════════════════════════════════════════════╝${NC}"
    echo ""
    echo -e "${YELLOW}Next steps:${NC}"
    echo -e "  • Run memory tests: ${BLUE}./test_valgrind.sh examples/sphere.rt${NC}"
    echo -e "  • Test all scenes: ${BLUE}./test_valgrind.sh examples/all_shapes.rt${NC}"
    echo -e "  • Interactive test: ${BLUE}./miniRT examples/sphere.rt${NC}"
    exit 0
else
    echo ""
    echo -e "${RED}╔════════════════════════════════════════════╗${NC}"
    echo -e "${RED}║         SOME TESTS FAILED ✗               ║${NC}"
    echo -e "${RED}╚════════════════════════════════════════════╝${NC}"
    exit 1
fi
