# miniRT Testing Guide

## Memory Leak Testing with Valgrind

### Prerequisites
```bash
sudo apt-get install valgrind
```

### Quick Start

#### Standard Memory Check (Summary only)
```bash
./test_valgrind.sh examples/sphere.rt
```

#### Full Memory Leak Check
```bash
./test_valgrind.sh examples/sphere.rt --full
```

#### Verbose Output (Most Detailed)
```bash
./test_valgrind.sh examples/sphere.rt --verbose
```

### Manual Valgrind Usage

#### Basic leak check with suppressions
```bash
valgrind --suppressions=valgrind.supp ./miniRT examples/sphere.rt
```

#### Full leak check with all details
```bash
valgrind --suppressions=valgrind.supp \
         --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         ./miniRT examples/sphere.rt
```

#### Generate detailed HTML report
```bash
valgrind --suppressions=valgrind.supp \
         --leak-check=full \
         --html=valgrind_report.html \
         ./miniRT examples/sphere.rt
```

#### Check for invalid memory access
```bash
valgrind --suppressions=valgrind.supp \
         --track-origins=yes \
         ./miniRT examples/sphere.rt
```

### Valgrind Options Explained

| Option | Description |
|--------|-------------|
| `--leak-check=no` | No leak checking (fastest) |
| `--leak-check=summary` | Count leaks, don't show where (default) |
| `--leak-check=yes` | Show each leak separately |
| `--leak-check=full` | Show each leak with all details |
| `--show-leak-kinds=all` | Show definite, indirect, and reachable leaks |
| `--track-origins=yes` | Show where leaked memory was allocated |
| `--suppressions=file` | Use suppression file to filter false positives |
| `--log-file=file` | Write output to file |
| `--html=file` | Generate HTML report |

### Understanding Valgrind Output

#### Clean Output
```
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: X from Y)
in use at exit: 0 bytes in 0 blocks
```
✅ This means no memory leaks (X suppressions are expected library behavior)

#### Memory Leak Example
```
==1234== 100 bytes in 1 blocks are definitely lost in loss record 1 of 5
==1234==    at 0x4C29F73: malloc (vg_replace_malloc.c:299)
==1234==    by 0x400550: allocate_memory (main.c:15)
==1234==    by 0x400560: main (main.c:25)
```
❌ This shows definite memory leak - needs fixing

#### Reachable Memory (Usually OK)
```
==1234== 50 bytes in 1 blocks are still reachable in loss record 1 of 3
```
⚠️ Reachable memory is usually system initialization that doesn't need freeing

### Test Scenes

| Scene | Description | Complexity |
|-------|-------------|-----------|
| `examples/sphere.rt` | Single sphere with lighting | Low |
| `examples/cone.rt` | Cone rendering test | Low |
| `examples/all_shapes.rt` | All object types together | High |
| `examples/lot_of.rt` | Many objects for stress test | Very High |

### Suppressions File

The `valgrind.supp` file contains suppressions for:
- MLX42 library (graphics framework)
- libft library (string utilities)
- System libraries (libc, libdl, pthread)
- Display servers (X11, Wayland)
- OpenGL initialization

These are **expected false positives** - memory allocated during initialization that remains in use for the lifetime of the program.

### Common Issues

#### "Can't find libc.so.6"
```bash
export LD_LIBRARY_PATH=/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
valgrind ./miniRT examples/sphere.rt
```

#### "Valgrind not found"
```bash
sudo apt-get install valgrind valgrind-dbg
```

#### X11/Wayland connection errors
These are normal - suppress them:
```bash
valgrind --suppressions=valgrind.supp ./miniRT examples/sphere.rt
```

### Continuous Testing

Run all scenes for comprehensive testing:
```bash
for scene in examples/*.rt; do
    echo "Testing $scene..."
    ./test_valgrind.sh "$scene"
    echo "---"
done
```

### Interpreting Results

**Definitely Lost** = Real memory leak ❌
- Must be fixed
- Memory allocated but pointer lost

**Indirectly Lost** = Often a side effect ⚠️
- Usually secondary to a definite leak
- Fix the parent leak

**Possibly Lost** = Maybe a leak ⚠️
- Could be false positive
- Check context

**Still Reachable** = Usually OK ✓
- Memory still accessible at exit
- Often system initialization

**Suppressed** = Expected false positive ✓
- Listed in suppressions file
- Safe to ignore

---

## AddressSanitizer Testing (Alternative to Valgrind)

AddressSanitizer is built into the compiler and runs during execution:

### Build with AddressSanitizer
```bash
CFLAGS="-fsanitize=address -g" make clean && make
```

### Run with ASan
```bash
./miniRT examples/sphere.rt
# Output appears in stderr
```

### Advantages of ASan over Valgrind
- Much faster
- No suppressions needed
- Better for development
- Works in CI/CD systems

---

## Norminette Compliance

```bash
norminette src/ include/
```

All source files must pass norminette (42 School coding standard).

---

## Build Verification

```bash
make clean && make
# Should compile with -Wall -Wextra -Werror with zero warnings
```

