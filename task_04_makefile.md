# Task 4: Makefile & Norminette Fixes

The Makefile contains minor errors, and the Norminette tool found 46 violations.

## Makefile Fixes

The `Makefile` requires updating to match the folder structure and properly handle bonus targets.

1.  **Typo fix:**
    ```make
    CFLAGS = -Wall -Wextra -Werror -Iincludes
    ```
    Change to `-Iinclude` to match the actual header directory.

2.  **Bonus Target Fix:**
    The `bonus` rule must compile the `*_bonus.c` versions (or build an executable that complies with bonus features without breaking the mandatory rules).

    ```make
    bonus: $(BONUS_OBJS)
        $(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(MLX) -o $(NAME)_bonus
    ```

3.  **`.PHONY` Rules:**
    Ensure `all, clean, fclean, re, bonus` are properly declared as `.PHONY`.

## Norminette Fixes

You have 46 style errors scattered across `src/` and `include/`.

To fix them quickly:
1.  Run `norminette src/ include/`.
2.  Fix lines longer than 80 characters (split arguments across lines).
3.  Fix function limits (maximum 5 functions per `.c` file).
4.  Ensure headers start with `#ifndef HEADER_H` guards.
5.  Check variable declarations (they must be at the top of the function block).

## Why it matters
The instructions state: `The project must be written in C, following the Norm`. You will instantly fail if the code does not pass `norminette`.
