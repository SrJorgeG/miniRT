#!/bin/bash

# Valgrind testing script for miniRT
# Usage: ./test_valgrind.sh [scene_file] [options]
# Examples:
#   ./test_valgrind.sh examples/sphere.rt
#   ./test_valgrind.sh examples/all_shapes.rt --full
#   ./test_valgrind.sh examples/cone.rt --verbose

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Default values
SCENE_FILE="${1:-examples/sphere.rt}"
VALGRIND_OPTS=""
OUTPUT_FILE="valgrind_report.txt"
VERBOSE=false

# Parse arguments
if [[ "$2" == "--full" ]]; then
    VALGRIND_OPTS="--leak-check=full --show-leak-kinds=all"
    echo -e "${BLUE}Running FULL memory leak check...${NC}"
elif [[ "$2" == "--verbose" ]]; then
    VALGRIND_OPTS="--leak-check=full --show-leak-kinds=all -v"
    VERBOSE=true
    echo -e "${BLUE}Running VERBOSE memory check...${NC}"
else
    VALGRIND_OPTS="--leak-check=summary"
    echo -e "${BLUE}Running standard memory check...${NC}"
fi

# Check if scene file exists
if [[ ! -f "$SCENE_FILE" ]]; then
    echo -e "${RED}Error: Scene file not found: $SCENE_FILE${NC}"
    exit 1
fi

# Build the project first
echo -e "${YELLOW}Building miniRT...${NC}"
make clean > /dev/null 2>&1
make > /dev/null 2>&1
echo -e "${GREEN}✓ Build successful${NC}"

# Run valgrind
echo ""
echo -e "${YELLOW}Running Valgrind with suppressions...${NC}"
echo -e "${BLUE}Command: valgrind $VALGRIND_OPTS --suppressions=valgrind.supp ./miniRT $SCENE_FILE${NC}"
echo ""

# Run with timeout (60 seconds to let the window appear and close)
timeout 60 valgrind \
    $VALGRIND_OPTS \
    --suppressions=valgrind.supp \
    --log-file="$OUTPUT_FILE" \
    ./miniRT "$SCENE_FILE" \
    > /dev/null 2>&1 || true

# Check if report was generated
if [[ -f "$OUTPUT_FILE" ]]; then
    echo -e "${YELLOW}=== Valgrind Report ===${NC}"
    cat "$OUTPUT_FILE"
    echo ""
    echo -e "${GREEN}✓ Full report saved to: $OUTPUT_FILE${NC}"
else
    echo -e "${RED}Error: Valgrind report not generated${NC}"
    exit 1
fi

# Summary
echo ""
echo -e "${BLUE}=== Summary ===${NC}"
if grep -q "ERROR SUMMARY: 0 errors" "$OUTPUT_FILE"; then
    echo -e "${GREEN}✓ No memory errors detected!${NC}"
else
    ERRORS=$(grep "ERROR SUMMARY" "$OUTPUT_FILE" || echo "Unknown")
    echo -e "${RED}⚠ Memory issues detected:${NC}"
    echo "$ERRORS"
fi

if grep -q "in use at exit: 0 bytes" "$OUTPUT_FILE"; then
    echo -e "${GREEN}✓ No memory leaks at exit!${NC}"
elif grep -q "in use at exit:" "$OUTPUT_FILE"; then
    LEAKED=$(grep "in use at exit:" "$OUTPUT_FILE")
    echo -e "${YELLOW}⚠ $LEAKED${NC}"
fi
