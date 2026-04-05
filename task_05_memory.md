# Task 5: Memory Management Fixes

The `miniRT` parser correctly throws the required `Error\n<message>` on syntax errors or bad data. However, there are potential memory leaks when freeing partially built scene structures.

## Solution

When encountering a parsing error (like an invalid `.rt` format mid-file), you must clean up the `t_scene` structure fully before calling `exit`. This includes:

1. Freeing the linked list of geometric objects.
2. Freeing the list of lights.
3. Freeing any camera dynamically allocated properties.
4. Calling `mlx_terminate(data->mlx)`.

### Example Fix: `src/parser/parser_utils.c` or similar

```c
void free_scene(t_scene *scene)
{
    // Free Object List
    t_list *tmp_obj = scene->objects;
    while (tmp_obj)
    {
        t_list *next = tmp_obj->next;
        free(tmp_obj->content); // Free the plane, sphere, or cylinder struct
        free(tmp_obj);
        tmp_obj = next;
    }

    // Free Light List
    t_list *tmp_lgt = scene->lights;
    while (tmp_lgt)
    {
        t_list *next = tmp_lgt->next;
        free(tmp_lgt->content); // Free the light struct
        free(tmp_lgt);
        tmp_lgt = next;
    }

    // Free the main scene struct if dynamically allocated
}

void exit_error(t_scene *scene, char *msg)
{
    printf("Error\n%s\n", msg);
    free_scene(scene);
    exit(1);
}
```

## Why it matters
The instructions state: `All heap-allocated memory must be properly freed. Memory leaks are not tolerated.` The parser test suite used by evaluators will run malformed `.rt` files to check if memory is freed before aborting. You can test this using `Valgrind` or `-fsanitize=address`.
