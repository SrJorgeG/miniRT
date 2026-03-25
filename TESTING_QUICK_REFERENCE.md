# 🧪 Testing Quick Reference

## One-Line Commands

```bash
# Run all validation checks
./run_tests.sh

# Quick memory test
./test_valgrind.sh examples/sphere.rt

# Full leak check
./test_valgrind.sh examples/all_shapes.rt --full

# Build + test in one command
make clean && make && ./run_tests.sh && ./test_valgrind.sh examples/sphere.rt

# Manual Valgrind with all details
valgrind --suppressions=valgrind.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./miniRT examples/sphere.rt
```

## Test Scripts

| Command | Purpose | Time | Output |
|---------|---------|------|--------|
| `./run_tests.sh` | Build + style + norminette | 10s | Summary + results |
| `./test_valgrind.sh FILE.rt` | Memory leaks (summary) | 20s | valgrind_report.txt |
| `./test_valgrind.sh FILE.rt --full` | All memory details | 25s | valgrind_report.txt |
| `./test_valgrind.sh FILE.rt --verbose` | Full + verbose output | 30s | Full log + report |

## Expected Results

### ✅ Clean Results
```
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 50+ from ...)
in use at exit: 0 bytes in 0 blocks
```

### ⚠️ Normal (Reachable Memory)
```
in use at exit: 100+ bytes in 5+ blocks
still reachable: 100+ bytes in 5+ blocks
```
These are OK - system initialization that remains allocated.

### ❌ Real Leak (Must Fix)
```
definitely lost: X bytes in Y blocks
```
This indicates an actual memory leak that needs fixing.

## Scene Files

- `examples/sphere.rt` - Basic test (fast)
- `examples/cone.rt` - Test cone rendering
- `examples/all_shapes.rt` - All objects together
- `examples/lot_of.rt` - Stress test (slow)

## Common Issues & Solutions

| Issue | Solution |
|-------|----------|
| "Valgrind not found" | `sudo apt-get install valgrind` |
| "Permission denied" | `chmod +x *.sh` |
| Window won't open | Add `--timeout 60` to valgrind command |
| Slow testing | Use `examples/sphere.rt` (smaller) |
| Too much output | Use `--leak-check=summary` (default) |

## Testing Workflow

```
1. Development
   └─> make clean && make
   └─> ./miniRT examples/cone.rt  (visual test)

2. Code Review
   └─> ./run_tests.sh  (checks all standards)

3. Before Submission
   └─> ./run_tests.sh  (must PASS)
   └─> ./test_valgrind.sh examples/sphere.rt --full  (check leaks)
   └─> norminette src/ include/  (code style)

4. Debugging Memory Issues
   └─> ./test_valgrind.sh examples/sphere.rt --verbose
   └─> Check TESTING.md for interpretation
```

## Suppression File

The `valgrind.supp` file suppresses known false positives from:
- **MLX42**: Graphics library (GLFW, OpenGL)
- **libft**: String utilities
- **System**: libc, libdl, pthread, X11, Wayland
- **Display**: X11, Wayland, XCB, OpenGL vendors

These suppressions are **normal and expected** - not a sign of problems.

## Git Integration

```bash
# Before committing
./run_tests.sh  # Must pass all 5 tests
git add .
git commit -m "..."

# Check specific commit
git show --stat HEAD

# See full changes
git log -p HEAD~1..HEAD
```

## Performance Tips

- Use `sphere.rt` for quick tests (fast)
- Use `all_shapes.rt` for comprehensive tests
- Use `--leak-check=summary` for speed
- Use `--leak-check=full` before submission only
- Redirect to file for large outputs: `... > output.txt 2>&1`

---

**Last Updated**: 2026-03-25  
**Version**: 1.0  
**Status**: ✅ All tests passing
