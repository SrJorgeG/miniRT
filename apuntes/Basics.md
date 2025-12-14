# miniRT - Complete Ray Tracing Project Guide

## Table of Contents
1. [Core Concepts](#core-concepts)
2. [Mathematical Foundations](#mathematical-foundations)
3. [Ray Tracing Fundamentals](#ray-tracing-fundamentals)
4. [3D Objects and Primitives](#3d-objects-and-primitives)
5. [Light and Shading](#light-and-shading)
6. [Camera and Viewport](#camera-and-viewport)
7. [Scene Parsing](#scene-parsing)
8. [Performance Optimization](#performance-optimization)
9. [Advanced Techniques](#advanced-techniques)

---

## Core Concepts

### Ray Tracing
**Definition**: A rendering technique that simulates the physical behavior of light by tracing the path of rays from the camera through pixels into the scene.

**Key Principle**: For each pixel, shoot a ray from the camera through that pixel into the scene and determine what color that ray sees by checking intersections with objects.

### Ray
**Definition**: A mathematical representation of a line with an origin and a direction.

**Formula**: `Ray(t) = Origin + t * Direction`
- `Origin`: Starting point (camera position)
- `Direction`: Normalized vector indicating ray direction
- `t`: Parameter (distance along ray, t ≥ 0)

### Intersection
**Definition**: The point where a ray meets a 3D object in the scene.

**Purpose**: Determines which object is visible at each pixel and where lighting calculations should occur.

---

## Mathematical Foundations

### Vectors

#### 3D Vector
**Definition**: A mathematical entity with magnitude and direction in 3D space, represented as (x, y, z).

**Common Operations**:
```c
// Addition
Vector3 add(Vector3 a, Vector3 b) {
    return (Vector3){a.x + b.x, a.y + b.y, a.z + b.z};
}

// Subtraction
Vector3 subtract(Vector3 a, Vector3 b) {
    return (Vector3){a.x - b.x, a.y - b.y, a.z - b.z};
}

// Scalar multiplication
Vector3 scale(Vector3 v, double scalar) {
    return (Vector3){v.x * scalar, v.y * scalar, v. z * scalar};
}
```

#### Dot Product
**Definition**: A scalar value representing the projection of one vector onto another.

**Formula**: `a · b = ax*bx + ay*by + az*bz = |a||b|cos(θ)`

**Uses**:
- Calculating angles between vectors
- Determining if vectors are perpendicular (dot product = 0)
- Computing projections

```c
double dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
```

#### Cross Product
**Definition**: A vector perpendicular to two input vectors, with magnitude equal to the area of the parallelogram they span.

**Formula**: `a × b = (ay*bz - az*by, az*bx - ax*bz, ax*by - ay*bx)`

**Uses**:
- Finding surface normals
- Determining coordinate system orientation
- Calculating orthogonal vectors

```c
Vector3 cross(Vector3 a, Vector3 b) {
    return (Vector3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
```

#### Vector Magnitude (Length)
**Definition**: The length or size of a vector.

**Formula**:  `|v| = √(x² + y² + z²)`

```c
double magnitude(Vector3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
```

#### Normalized Vector (Unit Vector)
**Definition**: A vector with magnitude 1, pointing in the same direction as the original. 

**Formula**: `v̂ = v / |v|`

**Purpose**: Used for directions to ensure consistent calculations regardless of scale.

```c
Vector3 normalize(Vector3 v) {
    double mag = magnitude(v);
    return (Vector3){v.x / mag, v.y / mag, v.z / mag};
}
```

### Coordinate Systems

#### World Space
**Definition**: The global coordinate system where all objects in the scene are positioned.

#### Camera Space
**Definition**:  Coordinate system relative to the camera's position and orientation. 

#### Screen Space
**Definition**: 2D coordinate system of the output image (pixel coordinates).

---

## Ray Tracing Fundamentals

### Ray-Object Intersection

#### Ray-Sphere Intersection
**Definition**: Finding where a ray intersects with a sphere. 

**Mathematical Approach**:
- Sphere equation: `|P - C|² = r²` (all points P at distance r from center C)
- Ray equation: `P(t) = O + tD` (O = origin, D = direction)
- Substitute ray into sphere equation and solve quadratic equation

**Formula**:
```
|O + tD - C|² = r²
(O + tD - C) · (O + tD - C) = r²

Expand to:  at² + bt + c = 0
where: 
    a = D · D = 1 (if D is normalized)
    b = 2D · (O - C)
    c = (O - C) · (O - C) - r²

Discriminant:  Δ = b² - 4ac
- If Δ < 0: no intersection
- If Δ = 0: one intersection (tangent)
- If Δ > 0: two intersections

t = (-b ± √Δ) / 2a
```

```c
bool intersect_sphere(Ray ray, Sphere sphere, double *t) {
    Vector3 oc = subtract(ray.origin, sphere.center);
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(oc, ray.direction);
    double c = dot(oc, oc) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return false;
    
    *t = (-b - sqrt(discriminant)) / (2.0 * a);
    return (*t > 0);
}
```

#### Ray-Plane Intersection
**Definition**: Finding where a ray intersects an infinite plane.

**Plane Equation**: `(P - P₀) · N = 0`
- P₀:  point on the plane
- N: plane normal (perpendicular vector)

**Formula**:
```
Substitute ray:  (O + tD - P₀) · N = 0
Solve for t: t = (P₀ - O) · N / (D · N)

Special case: If D · N = 0, ray is parallel to plane (no intersection)
```

```c
bool intersect_plane(Ray ray, Plane plane, double *t) {
    double denom = dot(ray.direction, plane.normal);
    
    if (fabs(denom) < 1e-6)  // Parallel
        return false;
    
    Vector3 p0_to_origin = subtract(plane.point, ray.origin);
    *t = dot(p0_to_origin, plane.normal) / denom;
    
    return (*t > 0);
}
```

#### Ray-Cylinder Intersection
**Definition**: Finding where a ray intersects a finite or infinite cylinder.

**Approach**:  
1. Solve for intersection with infinite cylinder (quadratic equation)
2. Check if intersection height is within cylinder bounds

**Formula** (for cylinder along axis A through point C):
```
Project ray onto plane perpendicular to cylinder axis
Solve resulting 2D circle intersection
Check height constraint:  |((P - C) · A)| ≤ height/2
```

#### Ray-Triangle Intersection
**Definition**: Finding where a ray intersects a triangle (fundamental for mesh rendering).

**Möller-Trumbore Algorithm**:
```
Given triangle with vertices V0, V1, V2:

E1 = V1 - V0
E2 = V2 - V0
P = D × E2
det = E1 · P

If det ≈ 0, ray is parallel to triangle

u = (T · P) / det  where T = O - V0
if u < 0 or u > 1, intersection is outside triangle

Q = T × E1
v = (D · Q) / det
if v < 0 or u + v > 1, intersection is outside triangle

t = (E2 · Q) / det
```

### Closest Hit
**Definition**: Among all intersections found for a ray, the one closest to the ray origin (smallest positive t value).

**Algorithm**:
```c
Object* find_closest_hit(Ray ray, Scene scene, double *closest_t) {
    Object *hit_object = NULL;
    *closest_t = INFINITY;
    
    for (int i = 0; i < scene.object_count; i++) {
        double t;
        if (intersect(ray, scene.objects[i], &t)) {
            if (t > 0 && t < *closest_t) {
                *closest_t = t;
                hit_object = &scene.objects[i];
            }
        }
    }
    return hit_object;
}
```

---

## 3D Objects and Primitives

### Sphere
**Definition**: Set of all points equidistant from a center point. 

**Properties**:
- Center:  (cx, cy, cz)
- Radius: r
- Equation: `(x-cx)² + (y-cy)² + (z-cz)² = r²`

**Surface Normal** at point P: `N = normalize(P - Center)`

### Plane
**Definition**: Flat, infinite 2D surface in 3D space.

**Properties**:
- Point on plane: P₀
- Normal vector: N (perpendicular to surface)
- Equation: `(P - P₀) · N = 0`

**Surface Normal**:  Constant (the plane's normal N)

### Cylinder
**Definition**: Surface formed by all points at a fixed distance from a line (axis).

**Properties**:
- Center point: C
- Axis direction: A (normalized)
- Radius: r
- Height: h (for finite cylinder)

**Surface Normal** at point P: 
```
Vector from axis to point: 
V = P - (C + ((P-C)·A)*A)
Normal = normalize(V)
```

### Cone
**Definition**: Surface formed by lines connecting a point (apex) to a circular base.

**Properties**: 
- Apex: A
- Axis direction: D
- Half-angle: α

---

## Light and Shading

### Ambient Light
**Definition**:  Constant, directionless illumination that simulates indirect light bouncing in the scene.

**Formula**: `Ambient = Ia * Ka`
- Ia: ambient light intensity
- Ka: material's ambient reflection coefficient

**Properties**:
- Ratio:  0.0-1.0 (brightness level)
- Color: RGB values

### Diffuse Reflection (Lambertian)
**Definition**: Light scattering equally in all directions from a rough surface.

**Formula (Lambert's Law)**: `Diffuse = Kd * I * max(0, N · L)`
- Kd: diffuse reflection coefficient
- I: light intensity
- N: surface normal
- L: direction to light source

**Key**:  Brightness depends on angle between surface normal and light direction. 

```c
double diffuse_intensity(Vector3 normal, Vector3 light_dir) {
    return fmax(0.0, dot(normal, light_dir));
}
```

### Specular Reflection (Phong)
**Definition**: Mirror-like reflection creating bright highlights on shiny surfaces.

**Phong Formula**:  `Specular = Ks * I * max(0, R · V)ⁿ`
- Ks: specular reflection coefficient
- R: reflected light direction
- V: view direction (toward camera)
- n: shininess exponent (larger = sharper highlight)

**Reflection Vector**: `R = 2(N · L)N - L`

```c
Vector3 reflect(Vector3 incident, Vector3 normal) {
    return subtract(incident, 
                   scale(normal, 2.0 * dot(incident, normal)));
}

double specular_intensity(Vector3 normal, Vector3 light_dir, 
                         Vector3 view_dir, double shininess) {
    Vector3 reflect_dir = reflect(scale(light_dir, -1), normal);
    return pow(fmax(0.0, dot(reflect_dir, view_dir)), shininess);
}
```

### Blinn-Phong Shading
**Definition**: Alternative to Phong that uses halfway vector instead of reflection vector.

**Formula**: `Specular = Ks * I * max(0, N · H)ⁿ`
- H: halfway vector between light and view directions
- H = normalize(L + V)

**Advantage**: More efficient and fixes Phong's issues at grazing angles.

### Point Light
**Definition**: Light source that emits equally in all directions from a single point.

**Properties**:
- Position: (x, y, z)
- Intensity: brightness
- Color: RGB values

**Attenuation**: `Intensity_at_distance = I₀ / (1 + d²)`

### Directional Light
**Definition**: Light source infinitely far away with parallel rays (like the sun).

**Properties**:
- Direction: normalized vector
- Intensity: brightness
- Color: RGB values

**Note**: No position, no attenuation (distance doesn't matter)

### Shadows
**Definition**: Areas where direct light is blocked by objects.

**Shadow Ray**: Ray from intersection point toward light source. 

**Algorithm**:
```c
bool is_in_shadow(Vector3 point, Vector3 light_pos, Scene scene) {
    Vector3 light_dir = normalize(subtract(light_pos, point));
    double light_distance = magnitude(subtract(light_pos, point));
    
    Ray shadow_ray = {
        . origin = add(point, scale(normal, 0.001)),  // Offset to avoid self-intersection
        .direction = light_dir
    };
    
    for (int i = 0; i < scene.object_count; i++) {
        double t;
        if (intersect(shadow_ray, scene.objects[i], &t)) {
            if (t > 0 && t < light_distance)
                return true;  // Object blocks light
        }
    }
    return false;
}
```

### Phong Reflection Model
**Definition**: Complete lighting model combining ambient, diffuse, and specular components.

**Complete Formula**:
```
Color = Ka*Ia + Kd*I*max(0, N·L) + Ks*I*max(0, R·V)ⁿ
```

**Implementation**:
```c
Color compute_lighting(Intersection hit, Scene scene, Ray ray) {
    Color final_color = {0, 0, 0};
    
    // Ambient
    final_color = add_colors(final_color, 
                            scale_color(scene.ambient, hit.material.ka));
    
    // For each light
    for (int i = 0; i < scene.light_count; i++) {
        Light light = scene.lights[i];
        Vector3 light_dir = normalize(subtract(light.position, hit. point));
        
        // Shadow check
        if (is_in_shadow(hit.point, light. position, scene))
            continue;
        
        // Diffuse
        double diffuse = fmax(0.0, dot(hit.normal, light_dir));
        final_color = add_colors(final_color,
                                scale_color(light.color, 
                                          hit.material.kd * diffuse));
        
        // Specular
        Vector3 view_dir = normalize(scale(ray.direction, -1));
        Vector3 reflect_dir = reflect(scale(light_dir, -1), hit.normal);
        double specular = pow(fmax(0.0, dot(reflect_dir, view_dir)), 
                            hit.material.shininess);
        final_color = add_colors(final_color,
                                scale_color(light.color,
                                          hit.material.ks * specular));
    }
    
    return clamp_color(final_color);
}
```

---

## Camera and Viewport

### Camera
**Definition**: Virtual device that determines the viewpoint and viewing direction for rendering.

**Properties**:
- Position: (x, y, z) - where camera is located
- Look-at point / Direction: where camera points
- FOV: Field of View angle
- Up vector: defines camera orientation

### Field of View (FOV)
**Definition**: The extent of the observable scene visible through the camera, measured as an angle.

**Types**:
- Horizontal FOV: angle across width
- Vertical FOV:  angle across height

**Typical Values**:  60-90 degrees for realistic rendering

**Effect**: 
- Smaller FOV = zoomed in (telephoto)
- Larger FOV = zoomed out (wide angle)

### Viewport
**Definition**: The 2D plane in 3D space through which rays are cast, representing the final image.

**Setup**:
```c
typedef struct {
    double width;         // Viewport width in world units
    double height;        // Viewport height in world units
    Vector3 lower_left;   // Bottom-left corner position
    Vector3 horizontal;   // Horizontal edge vector
    Vector3 vertical;     // Vertical edge vector
} Viewport;

Viewport create_viewport(Camera cam, double aspect_ratio) {
    double viewport_height = 2.0 * tan(cam.fov / 2.0);
    double viewport_width = aspect_ratio * viewport_height;
    
    Vector3 w = normalize(subtract(cam.position, cam.look_at));  // Camera's back direction
    Vector3 u = normalize(cross(cam.up, w));  // Camera's right direction
    Vector3 v = cross(w, u);  // Camera's up direction
    
    Viewport vp;
    vp.horizontal = scale(u, viewport_width);
    vp.vertical = scale(v, viewport_height);
    
    // Lower left corner
    vp.lower_left = subtract(cam.position, scale(vp.horizontal, 0.5));
    vp.lower_left = subtract(vp.lower_left, scale(vp.vertical, 0.5));
    vp.lower_left = subtract(vp.lower_left, w);
    
    return vp;
}
```

### Camera Coordinate System
**Definition**: Orthonormal basis defining camera orientation. 

**Vectors**:
- **u**: Right (x-axis in camera space)
- **v**: Up (y-axis in camera space)  
- **w**: Back (negative z-axis in camera space, opposite of view direction)

**Construction**:
```
w = normalize(camera_position - look_at_point)
u = normalize(up_vector × w)
v = w × u
```

### Ray Generation
**Definition**: Creating rays from camera through each pixel.

**Formula**:
```c
Ray get_ray(Camera cam, Viewport vp, double u, double v) {
    // u, v are normalized pixel coordinates [0, 1]
    Vector3 pixel_pos = add(vp.lower_left,
                           add(scale(vp.horizontal, u),
                               scale(vp.vertical, v)));
    
    Ray ray;
    ray.origin = cam. position;
    ray.direction = normalize(subtract(pixel_pos, cam.position));
    
    return ray;
}

// For pixel (i, j) in image of width W and height H:
double u = (double)i / (W - 1);
double v = (double)j / (H - 1);
Ray ray = get_ray(camera, viewport, u, v);
```

### Aspect Ratio
**Definition**: Ratio of image width to height.

**Formula**: `aspect_ratio = width / height`

**Common Values**:
- 16:9 = 1.778 (widescreen)
- 4:3 = 1.333 (standard)
- 1:1 = 1.0 (square)

---

## Scene Parsing

### Scene File Format
**Definition**: Text file describing all elements in the scene (objects, lights, camera).

**Common Structure** (. rt format for miniRT):
```
# Resolution
R 1920 1080

# Ambient light
A 0.2 255,255,255

# Camera
c -50. 0,0,20 0,0,1 70

# Light
l -40. 0,50. 0,0.0 0. 6 10,0,255

# Sphere
sp 0.0,0.0,20.6 12.6 10,0,255

# Plane
pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225

# Cylinder
cy 50.0,0.0,20.6 0.0,0.0,1.0 14. 2 21.42 10,0,255
```

### Parser Components

#### Tokenization
**Definition**: Breaking input file into meaningful pieces (tokens).

```c
typedef enum {
    TOKEN_IDENTIFIER,  // R, A, c, sp, pl, etc.
    TOKEN_NUMBER,      // Integers and floats
    TOKEN_COLOR,       // R,G,B format
    TOKEN_VECTOR,      // x,y,z format
    TOKEN_NEWLINE
} TokenType;
```

#### Validation
**Definition**: Checking that scene data meets requirements.

**Checks**:
- Value ranges (e.g., ambient ratio 0.0-1.0, RGB 0-255)
- Normalized vectors where required
- Required elements present (camera, ambient light)
- No duplicate unique elements
- Valid number formats

```c
bool validate_color(int r, int g, int b) {
    return (r >= 0 && r <= 255 &&
            g >= 0 && g <= 255 &&
            b >= 0 && b <= 255);
}

bool validate_normalized(Vector3 v) {
    double mag = magnitude(v);
    return (fabs(mag - 1.0) < 0.001);
}

bool validate_ratio(double ratio) {
    return (ratio >= 0.0 && ratio <= 1.0);
}
```

### Error Handling
**Definition**: Gracefully managing invalid input.

**Best Practices**:
- Clear error messages with line numbers
- Specific descriptions of what's wrong
- Suggest corrections when possible
- Exit cleanly without leaks

```c
void parse_error(int line_num, const char *message) {
    fprintf(stderr, "Error on line %d: %s\n", line_num, message);
    cleanup_resources();
    exit(1);
}
```

---

## Performance Optimization

### Bounding Volumes
**Definition**: Simple shapes that enclose complex objects for fast intersection culling.

**Types**:
- **Axis-Aligned Bounding Box (AABB)**: Box aligned with coordinate axes
- **Bounding Sphere**:  Sphere enclosing object

**Purpose**: Quick rejection of rays that can't possibly hit object. 

```c
typedef struct {
    Vector3 min;  // Minimum corner
    Vector3 max;  // Maximum corner
} AABB;

bool intersect_aabb(Ray ray, AABB box) {
    double tmin = -INFINITY, tmax = INFINITY;
    
    for (int i = 0; i < 3; i++) {
        double inv_d = 1.0 / ray.direction. data[i];
        double t0 = (box.min.data[i] - ray.origin.data[i]) * inv_d;
        double t1 = (box.max.data[i] - ray. origin.data[i]) * inv_d;
        
        if (inv_d < 0.0) {
            double temp = t0; t0 = t1; t1 = temp;
        }
        
        tmin = fmax(t0, tmin);
        tmax = fmin(t1, tmax);
        
        if (tmax < tmin)
            return false;
    }
    return true;
}
```

### Spatial Data Structures

#### Bounding Volume Hierarchy (BVH)
**Definition**: Tree structure that hierarchically groups objects by spatial proximity.

**Concept**:
- Root contains bounding box of entire scene
- Children subdivide space
- Leaves contain actual objects

**Benefit**: Avoid testing every object for every ray (O(log n) instead of O(n))

#### Octree
**Definition**: Tree structure where each node has 8 children, subdividing 3D space into octants.

#### k-d Tree
**Definition**: Binary tree that partitions space along coordinate axes.

### Early Ray Termination
**Definition**: Stop tracing a ray once sufficient information is gathered.

**Examples**:
- After finding first intersection (for primary rays without transparency)
- When accumulated color is opaque enough
- When ray exits scene bounds

### Multi-threading
**Definition**: Parallel processing of multiple pixels/rays simultaneously.

**Approach**:
- Each thread processes subset of pixels
- No data dependencies between pixels in basic ray tracing
- Linear speedup with CPU cores

```c
void *render_chunk(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    
    for (int j = data->y_start; j < data->y_end; j++) {
        for (int i = 0; i < data->width; i++) {
            Ray ray = generate_ray(i, j);
            Color color = trace_ray(ray, data->scene);
            set_pixel(data->image, i, j, color);
        }
    }
    return NULL;
}
```

---

## Advanced Techniques

### Reflection
**Definition**: Simulating mirror-like surfaces by recursively tracing reflected rays.

**Algorithm**:
1. Compute reflection direction:  `R = D - 2(D·N)N`
2. Cast new ray from intersection point in direction R
3. Multiply returned color by surface reflectivity
4. Add to final color

**Recursive Implementation**:
```c
Color trace_ray(Ray ray, Scene scene, int depth) {
    if (depth <= 0)
        return BLACK;
    
    Intersection hit;
    if (! find_intersection(ray, scene, &hit))
        return BACKGROUND_COLOR;
    
    Color local_color = compute_lighting(hit, scene, ray);
    
    if (hit.material.reflectivity > 0) {
        Ray reflected_ray;
        reflected_ray.origin = hit.point;
        reflected_ray.direction = reflect(ray. direction, hit.normal);
        
        Color reflected_color = trace_ray(reflected_ray, scene, depth - 1);
        local_color = blend(local_color, reflected_color, 
                           hit.material.reflectivity);
    }
    
    return local_color;
}
```

### Refraction (Transparency)
**Definition**: Simulating light passing through transparent materials (glass, water).

**Snell's Law**: `n₁ sin(θ₁) = n₂ sin(θ₂)`
- n₁, n₂:  refractive indices of materials
- θ₁, θ₂: angles from surface normal

**Implementation**:
```c
Vector3 refract(Vector3 incident, Vector3 normal, double eta) {
    double cos_i = -dot(normal, incident);
    double sin_t2 = eta * eta * (1.0 - cos_i * cos_i);
    
    if (sin_t2 > 1.0)  // Total internal reflection
        return reflect(incident, normal);
    
    double cos_t = sqrt(1.0 - sin_t2);
    return add(scale(incident, eta), 
              scale(normal, eta * cos_i - cos_t));
}
```

### Fresnel Effect
**Definition**: Varying reflectivity based on viewing angle (more reflective at grazing angles).

**Schlick's Approximation**:
```c
double fresnel_schlick(double cos_theta, double ior) {
    double r0 = (1.0 - ior) / (1.0 + ior);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow(1.0 - cos_theta, 5);
}
```

### Anti-Aliasing
**Definition**: Reducing jagged edges by averaging multiple samples per pixel.

**Techniques**: 

#### Supersampling (SSAA)
Render at higher resolution, then downsample. 

#### Multi-Sample Anti-Aliasing (MSAA)
Cast multiple rays per pixel with slight offsets.

```c
Color render_pixel_aa(int x, int y, int samples_per_pixel) {
    Color accumulated = {0, 0, 0};
    
    for (int s = 0; s < samples_per_pixel; s++) {
        double u = (x + random_double()) / image_width;
        double v = (y + random_double()) / image_height;
        
        Ray ray = get_ray(camera, viewport, u, v);
        accumulated = add_colors(accumulated, trace_ray(ray, scene, MAX_DEPTH));
    }
    
    return scale_color(accumulated, 1.0 / samples_per_pixel);
}
```

### Texture Mapping
**Definition**: Applying 2D images onto 3D surfaces for detail.

**UV Coordinates**:  2D parametric coordinates (u, v) mapping surface to texture.

**For Sphere**:
```c
void get_sphere_uv(Vector3 point, Vector3 center, double *u, double *v) {
    Vector3 p = normalize(subtract(point, center));
    double phi = atan2(p.z, p.x);
    double theta = asin(p.y);
    
    *u = 1.0 - (phi + M_PI) / (2.0 * M_PI);
    *v = (theta + M_PI / 2.0) / M_PI;
}
```

### Normal Mapping
**Definition**: Perturbing surface normals based on texture to simulate detailed geometry.

### Bump Mapping
**Definition**: Similar to normal mapping but using height maps to calculate normal perturbations.

### Depth of Field
**Definition**: Simulating camera focus by varying sharpness based on distance.

**Technique**:  
- Define focal distance and aperture size
- Jitter ray origins within aperture disk
- Converge rays at focal plane

### Motion Blur
**Definition**: Simulating camera or object movement during exposure.

**Technique**:  Sample object positions at different times during shutter interval.

---

## Implementation Tips

### Memory Management
- Use structures for organized data
- Free all allocated memory
- Avoid memory leaks (use valgrind)
- Consider object pools for frequently allocated objects

### Debugging Techniques
- Visualize normals as colors:  `color = (normal + 1.0) * 0.5`
- Visualize depth: `color = 1.0 / distance`
- Render bounding boxes
- Test with simple scenes first
- Check one object type at a time

### Code Organization
```
miniRT/
├── src/
│   ├── main.c
│   ├── parser/
│   │   ├── parse_scene.c
│   │   ├── parse_objects.c
│   │   └── validate.c
│   ├── ray_tracing/
│   │   ├── ray. c
│   │   ├── intersections.c
│   │   └── trace. c
│   ├── lighting/
│   │   ├── phong.c
│   │   └── shadows.c
│   ├── objects/
│   │   ├── sphere.c
│   │   ├── plane.c
│   │   └── cylinder. c
│   ├── math/
│   │   ├── vector.c
│   │   └── matrix.c
│   └── utils/
│       ├── color. c
│       └── image.c
├── include/
│   └── miniRT.h
└── scenes/
    └── *.rt
```

### Testing Strategy
1. **Unit Tests**: Test individual functions (vector operations, intersections)
2. **Simple Scenes**: Single object, single light
3. **Progressive Complexity**: Add objects, lights, features incrementally
4. **Edge Cases**:  Parallel rays, tangent intersections, coincident objects
5. **Validation**: Compare output with reference renders

---

## Common Formulas Reference

### Distance from Point to Plane
`distance = |(P - P₀) · N| / |N|`

### Distance from Point to Line
`distance = ||(P - A) × direction|| / ||direction||`

### Reflection
`R = I - 2(I · N)N`

### Refraction (Snell's Law)
`η₁ sin θ₁ = η₂ sin θ₂`

### Quadratic Formula
`x = (-b ± √(b² - 4ac)) / 2a`

---

## Glossary

- **Albedo**: Base color/reflectivity of a surface
- **Attenuation**: Reduction of light intensity over distance
- **Bias/Epsilon**: Small offset to prevent self-intersection artifacts
- **Illumination Model**: Mathematical formula for computing surface lighting
- **Ray Origin**: Starting point of a ray
- **Ray Direction**: Normalized vector indicating ray direction
- **Surface Normal**: Vector perpendicular to surface at a point
- **Parametric t**: Distance parameter along a ray

---

## Additional Resources

### Books
- "Ray Tracing in One Weekend" by Peter Shirley
- "Physically Based Rendering" by Pharr, Jakob, and Humphreys
- "Real-Time Rendering" by Akenine-Möller, Haines, and Hoffman

### Online Resources
- Scratchapixel (scratchapixel.com)
- Ray Tracing Gems (free online)
- ShaderToy (practical examples)

### Mathematical Background
- Linear algebra (vectors, matrices)
- Trigonometry
- Calculus (basic derivatives for optimization)

---

## Project Checklist

### Minimum Features (miniRT)
- [ ] Parse scene file (. rt format)
- [ ] Implement camera with FOV
- [ ] Ray-sphere intersection
- [ ] Ray-plane intersection
- [ ] Ray-cylinder intersection
- [ ] Ambient lighting
- [ ] Point light sources
- [ ] Diffuse shading (Lambert)
- [ ] Specular highlights
- [ ] Shadows
- [ ] Multiple objects and lights
- [ ] Window management (display image)
- [ ] Clean exit and error handling

### Bonus Features
- [ ] Reflection
- [ ] Transparency/Refraction
- [ ] Multiple light types
- [ ] Texture mapping
- [ ] Normal/Bump mapping
- [ ] Anti-aliasing
- [ ] Multi-threading
- [ ] Additional primitives (cone, torus)
- [ ] Spatial acceleration structures

---

*This guide provides the fundamental concepts needed to implement a ray tracer like miniRT. Start with basic ray-sphere intersection and build up incrementally! *