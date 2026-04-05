# Task 1: README Requirements Fixes

The current `README.md` fails multiple 42 curriculum requirements from `INSTRUCTIONS.md` (it is in Spanish, missing the mandatory header, and missing the Resources/AI section).

## Solution

Replace the contents of `README.md` with the following structure, customized for your project:

```markdown
*This project has been created as part of the 42 curriculum by krusty*

# miniRT - Ray Tracing Engine

## Description
miniRT is my first RayTracer developed in C using the MiniLibX library. It implements mathematical formulas to render simple computer-generated images using the ray tracing technique. It handles primitive geometric objects like planes, spheres, and cylinders, applying ambient and diffuse lighting along with hard shadows.

## Instructions

### Compilation
To compile the project, simply run:
```bash
make
```

### Execution
Run the executable passing a valid `.rt` scene file as an argument:
```bash
./miniRT scenes/example.rt
```

### Controls
*   **ESC / Red Cross**: Close the window and exit cleanly.

## Resources
The following resources were instrumental in developing this ray tracer:
*   [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) - Fundamental concepts.
*   [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - For window and image management.
*   [Scratchapixel](https://www.scratchapixel.com/) - Understanding ray-object intersections.

### AI Usage
During this project, Artificial Intelligence (LLMs) was used to:
1.  **Reduce repetitive tasks**: Generating boilerplate code for vector math operations (`vec3_add`, `vec3_dot`, etc.).
2.  **Debugging Assistance**: AI helped identify precision errors (shadow acne) and suggested using an *epsilon* offset for shadow rays.
3.  **Code Review**: Analyzing the codebase for Norminette compliance and spotting potential memory leaks in the parser before peer evaluation.
```
