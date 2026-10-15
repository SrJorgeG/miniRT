#!/usr/bin/env bash
# Runs every scene in examples/ (must render and quit with ESC) and every
# scene in examples/invalid/ (must print "Error" first and exit 1).
# Usage: tests/run_scenes.sh            (needs an X display; uses xdotool)
#        VALGRIND=1 tests/run_scenes.sh (also fails on invalid accesses/leaks;
#          build with "make re EXTRA=-g" so stacks point into src/)
#        HEADLESS=1 tests/run_scenes.sh (starts its own Xvfb)
cd "$(dirname "$0")/.." || exit 1
BIN=./miniRT
WAIT=${WAIT:-5}
[ -x "$BIN" ] || make || exit 1
if [ -n "$HEADLESS" ]; then
	Xvfb :87 -screen 0 800x800x24 >/dev/null 2>&1 & XVFB=$!
	export DISPLAY=:87; sleep 1
	trap 'kill $XVFB' EXIT
fi
VG=()
if [ -n "$VALGRIND" ]; then
	VG=(valgrind -q --leak-check=full --errors-for-leak-kinds=definite
		--error-exitcode=42)
	WAIT=$((WAIT * 8))
fi
pass=0; fail=0
report() { if [ "$1" = ok ]; then pass=$((pass + 1)); printf "  OK    %s\n" "$2";
	else fail=$((fail + 1)); printf "  FAIL  %s (%s)\n" "$2" "$3"; fi; }
# Leaks inside GLFW/Mesa are not ours: only count errors whose stack hits src/
project_errors() { grep -A25 -E "Invalid|definitely lost in" "$1" | grep -c "src/"; }

echo "Valid scenes"
for f in examples/*.rt; do
	log=$(mktemp)
	"${VG[@]}" "$BIN" "$f" >"$log" 2>&1 & pid=$!
	sleep "$WAIT"
	xdotool search --pid "$pid" >/dev/null 2>&1 || xdotool key Escape 2>/dev/null
	xdotool key Escape 2>/dev/null
	wait "$pid"; rc=$?
	if [ -n "$VALGRIND" ] && [ "$(project_errors "$log")" -gt 0 ]; then
		report fail "$f" "valgrind errors in project code"
	elif [ $rc -ne 0 ] && [ $rc -ne 42 ]; then
		report fail "$f" "exit $rc"
	else report ok "$f"; fi
	rm -f "$log"
done

echo "Invalid scenes / arguments"
check_invalid() {
	log=$(mktemp)
	timeout 120 "${VG[@]}" "$BIN" "$@" >/dev/null 2>"$log"; rc=$?
	first=$(grep -v "^==" "$log" | head -1)
	if [ -n "$VALGRIND" ] && [ "$(project_errors "$log")" -gt 0 ]; then
		report fail "$*" "valgrind errors in project code"
	elif [ $rc -ne 1 ] && [ $rc -ne 42 ] || [ "$first" != "Error" ]; then
		report fail "$*" "exit $rc, first line '$first'"
	else report ok "$* -> $(grep -v '^==' "$log" | sed -n 2p)"; fi
	rm -f "$log"
}
check_invalid
check_invalid a.rt b.rt
check_invalid examples/README_missing.txt
check_invalid examples/does_not_exist.rt
for f in examples/invalid/*.rt; do check_invalid "$f"; done
echo "Passed: $pass  Failed: $fail"
[ $fail -eq 0 ]
