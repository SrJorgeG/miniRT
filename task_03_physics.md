# Task 3: Raytracing Physics Fixes

The `miniRT` project currently lacks hard shadows and cylinder caps. Both are mandatory requirements from `INSTRUCTIONS.md`.

## 1. Hard Shadows (Occlusion Check)

When calculating light intensity for a hit point, you must check if the path between the point and the light is obstructed by another object.

### Solution (Pseudo-code for `src/ray/lighting.c`)
Modify the `add_diffuse_lighting` function to trace a shadow ray:

```c
t_ray shadow_ray;
t_vec3 light_dir = vec3_sub(light->pos, hit->p);
double light_distance = vec3_length(light_dir);
light_dir = vec3_normalize(light_dir);

// Add an epsilon offset along the normal to prevent self-intersection (shadow acne)
shadow_ray.origin = vec3_add(hit->p, vec3_mult(hit->normal, 0.001));
shadow_ray.dir = light_dir;

t_hit shadow_hit = get_closest_hit(scene, &shadow_ray);

// If an object blocks the light BEFORE reaching the light source, no diffuse light is added
if (shadow_hit.hit && shadow_hit.t < light_distance) {
    return ambient_light; // Point is in shadow
}

// ... proceed with diffuse light calculation
```

## 2. Cylinder Caps (Top and Bottom Intersections)

Cylinders are infinite tubes unless capped. You must check intersection with the top and bottom circles.

### Solution (Math Concept for `hit_cylinder.c`)
A cylinder cap is a finite plane (a circle). A ray intersects a cap if:
1. It hits the infinite plane containing the cap.
2. The distance from the hit point to the cap's center is `<= radius`.

```c
// Pseudo-code to add to hit_cylinder.c
t_vec3 top_cap_center = vec3_add(cyl.center, vec3_mult(cyl.dir, cyl.height / 2.0));
t_vec3 bot_cap_center = vec3_sub(cyl.center, vec3_mult(cyl.dir, cyl.height / 2.0));

// Check intersection with TOP cap plane
double t_top = hit_plane(ray, top_cap_center, cyl.dir);
if (t_top > 0) {
    t_vec3 p = ray_at(ray, t_top);
    if (vec3_distance(p, top_cap_center) <= cyl.radius) {
        // We hit the top cap, update hit info
    }
}

// Check intersection with BOTTOM cap plane
double t_bot = hit_plane(ray, bot_cap_center, vec3_mult(cyl.dir, -1));
if (t_bot > 0) {
    t_vec3 p = ray_at(ray, t_bot);
    if (vec3_distance(p, bot_cap_center) <= cyl.radius) {
        // We hit the bottom cap, update hit info
    }
}
```

These checks must be done alongside the infinite tube check to find the closest valid hit `t`.
