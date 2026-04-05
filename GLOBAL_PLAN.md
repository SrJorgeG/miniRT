# Global Task Plan: miniRT Fixes

This document serves as the master checklist for all required fixes to bring the `miniRT` project into 100% compliance with the 42 curriculum requirements.

## 📋 Task List

1. **[Task 1: Fix README Requirements](./task_01_readme.md)**
   - Translate to English.
   - Add mandatory 42 curriculum header.
   - Add `Resources` and `AI Usage` sections.

2. **[Task 2: Window Management (ESC Key)](./task_02_window.md)**
   - Implement the `ESC` key hook to close the window cleanly.

3. **[Task 3: Raytracing Physics (Shadows & Cylinders)](./task_03_physics.md)**
   - Implement Hard Shadows (Shadow rays with epsilon).
   - Implement Cylinder Caps (Top and bottom plane intersections).

4. **[Task 4: Makefile & Norminette](./task_04_makefile.md)**
   - Fix `-Iincludes` typo.
   - Implement proper `bonus` rule.
   - Fix the 46 Norminette errors.

5. **[Task 5: Memory Management & Leaks](./task_05_memory.md)**
   - Ensure deep freeing of the scene struct during parser errors.
   - Audit with AddressSanitizer/Valgrind.

---
*Follow the links above to see the detailed code solutions and explanations for each task.*