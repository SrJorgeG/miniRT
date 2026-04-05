*This project has been created as part of the 42 curriculum by dcid-san, jgomez-d.*

## Description

miniRT is a ray tracing engine written in C as part of the 42 curriculum. The project introduces the fundamentals of ray tracing—a rendering technique that simulates light propagation to generate photorealistic 3D images. Unlike rasterization used in modern graphics engines, ray tracing is computationally more expensive but produces superior visual quality by accurately modeling light interactions.

The goal of miniRT is to demonstrate the ability to implement complex mathematical and physical formulas while maintaining clean, normalized C code. The engine supports multiple geometric objects (spheres, planes, and cylinders), realistic lighting calculations (ambient and diffuse), shadow casting, and object transformations.

## Instructions

### Compilation

The project uses a Makefile that automates the build process:

```bash
make            # Build the executable
make clean      # Remove object files
make fclean     # Remove object files and executable
make re         # Rebuild from scratch
```

### Requirements

- GCC or Clang compiler
- GNU Make
- MiniLibX42 library (automatically cloned and built)
- libft library (included in the project)
- POSIX-compliant system (Linux/macOS)
- Math library (`-lm` flag)

### Execution

Run the ray tracer with a scene file:

```bash
./miniRT <scene_file.rt>
```

Example:

```bash
./miniRT examples/scene.rt
```

### Scene File Format

Scene files use the `.rt` extension and define the 3D world. Elements can appear in any order and are separated by whitespace or newlines.

#### Required Elements

- **Ambient Light (A)**: `A 0.2 255,255,255`
  - Ratio: [0.0, 1.0]
  - Color: R,G,B [0, 255] each

- **Camera (C)**: `C -50,0,20 0,0,1 70`
  - Position: x,y,z coordinates
  - Orientation: normalized vector
  - FOV: horizontal field of view in degrees [0, 180]

- **Light (L)**: `L -40,0,30 0.7 255,255,255`
  - Position: x,y,z coordinates
  - Brightness: [0.0, 1.0]
  - Color: R,G,B [0, 255] each

#### Geometric Objects

- **Sphere (sp)**: `sp 0,0,20 20 255,0,0`
  - Position, diameter, color

- **Plane (pl)**: `pl 0,0,0 0,1,0 255,0,225`
  - Position, normal vector, color

- **Cylinder (cy)**: `cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255`
  - Position, axis vector, diameter, height, color

#### Example Scene

```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255
pl 0,0,0 0,1,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255
```

### Controls

- **ESC**: Close the window and exit
- **Mouse Click**: Window close button exits the application

## Resources

### Ray Tracing References

- [Ray Tracing in One Weekend](https://raytracing.github.io/) - Essential guide to ray tracing fundamentals
- [MiniLibX Documentation](https://github.com/codam-coding-college/MLX42) - Graphics library used for window management and rendering
- [3D Graphics Mathematics](https://www.3dgep.com/) - Vector and matrix operations essential for ray tracing
- [Phong Reflection Model](https://en.wikipedia.org/wiki/Phong_reflection_model) - Light reflection calculations

### Implementation References

- Vector mathematics: dot product, cross product, normalization
- Ray-object intersection algorithms: sphere, plane, cylinder
- Lighting model: ambient light, diffuse reflection, specular highlights
- Memory management: dynamic allocation and deallocation patterns in C

### AI Usage

AI tools were utilized strategically to enhance productivity while maintaining code ownership:

- **Vector Mathematics**: AI generated boilerplate vector operation functions (add, subtract, normalize) which were verified mathematically and integrated after peer review.
- **Debugging Optimization**: AI suggestions for structuring debug output and memory leak detection using Valgrind.
- **README**: AI was used to create a README.md template that match our project requirements and we edit it with our ideas.
All AI-generated code was critically examined, tested for correctness, and adapted to ensure it met 42 Norm standards and project requirements. No code was used without full understanding and validation.

## Project Structure

```
miniRT/
├── src/
│   ├── main.c                  # Entry point
│   ├── init.c                  # Initialization
│   ├── render.c                # Rendering loop
│   ├── exit.c                  # Exit handlers
│   ├── parser/                 # Scene file parsing
│   │   ├── parser.c
│   │   ├── parser_scene.c
│   │   └── parser_objects.c
│   ├── ray/                    # Ray tracing core
│   │   ├── ray.c
│   │   ├── hits.c
│   │   ├── hit_cylinder.c
│   │   ├── hits_cone.c
│   │   ├── lighting.c
│   │   ├── raycasting.c
│   │   └── ray_utils.c
│   ├── objects/                # Geometric objects
│   │   ├── sphere.c
│   │   ├── plane.c
│   │   ├── cylinder.c
│   │   └── cone.c
│   ├── vector/                 # Vector operations
│   │   ├── vector.c
│   │   ├── vector_aux.c
│   │   ├── vector_basic.c
│   │   └── vector_utils.c
│   ├── utils/                  # Utilities
│   │   ├── color.c
│   │   ├── scene.c
│   │   ├── textures.c
│   │   └── str.c
│   ├── hooks/                  # Input handling
│   │   ├── keyboard.c
│   │   └── mouse.c
│   ├── cache/                  # Performance optimization
│   │   └── cache.c
│   └── debug/                  # Debugging utilities
│       ├── debug_parser.c
│       └── debug_helpers.c
├── include/                    # Header files
├── libs/
│   ├── libft/                  # Custom C library
│   └── MLX42/                  # Graphics library
├── examples/                   # Example scene files
├── Makefile
└── README.md
```

## Technical Highlights

- **Ray-Object Intersection**: Efficient algorithms for computing ray intersections with spheres, planes, and cylinders
- **Lighting Model**: Proper implementation of ambient and diffuse lighting with shadow calculations
- **Memory Safety**: Strict adherence to the 42 Norm with complete memory cleanup and no leaks
- **Vector Mathematics**: Custom vector library supporting all necessary 3D transformations
- **Performance**: Caching mechanisms to optimize repeated calculations

## Notes

- This project must comply with the 42 Norm coding standard
- All memory must be properly freed (no leaks tolerated)
- The program must not crash under any circumstances (no segfaults, bus errors, or double frees)
- Window management must remain responsive (minimize, maximize, switch windows)
