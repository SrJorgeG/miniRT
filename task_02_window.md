# Task 2: Window Management (ESC Key)

The codebase currently does not correctly handle the `ESC` key to close the window cleanly.

## Solution

Modify your key hook function (likely in `src/hooks/keyboard.c` or similar) to check for `MLX_KEY_ESCAPE` and call `mlx_close_window`.

### Example Fix:

```c
#include "MLX42/MLX42.h"
#include "minirt.h" // Replace with your actual header

void custom_key_hook(mlx_key_data_t keydata, void *param)
{
    t_data *data = (t_data *)param;

    // Check if ESC is pressed and close the window cleanly
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
    {
        mlx_close_window(data->mlx);
    }
}
```

Make sure this function is hooked to your `mlx` instance inside your main loop initialization:

```c
mlx_key_hook(data->mlx, &custom_key_hook, data);
```

### Why it matters
The instructions clearly state: `Pressing ESC closes the window and exits cleanly.` This is a mandatory feature, otherwise you will lose points for a non-functional interface.
