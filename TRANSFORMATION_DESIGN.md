# Transformation Implementation Design
## Branch: feature/transformations

### Current Status Analysis

#### ✅ What's Already Done
- Structs have transformation fields:
  - `t_sphere`: trans_x, trans_y, trans_z
  - `t_plane`: rot_x, rot_y, rot_z, trans_x, trans_y, trans_z
  - `t_cylinder`: rot_x, rot_y, rot_z, trans_x, trans_y, trans_z
  - `t_cone`: rot_x, rot_y, rot_z, trans_x, trans_y, trans_z
  - `t_light`: trans_x, trans_y, trans_z
- Parser functions exist but are **INCOMPLETE**

#### ❌ What's Wrong
1. **parse_sphere_translation()**: 
   - Line 32: Assigns CENTER to trans fields instead of OFFSET
   - Should NOT overwrite sphere->center
   
2. **parse_plane_translation()**:
   - Lines 121-123: Only assigns trans_x, trans_y/z set to 0
   - Should parse full vector or individual values
   
3. **parse_cylinder_translation()**:
   - Lines 204-206: Does NOTHING (all set to 0)
   - Should parse translation vector
   
4. **parse_cone_translation()**:
   - Lines 283-285: Does NOTHING (all set to 0)
   - Should parse translation vector

5. **Camera rotations**: NOT implemented in t_camera struct
6. **Light parsing**: Probably missing translation support
7. **Transformations NOT applied**: Ray-object intersection doesn't use these values

### Scene File Format

#### Expected Format (with transformations)
```
# Sphere with translation
sp x,y,z diameter r,g,b [tx,ty,tz]

# Plane with rotation and translation
pl x,y,z nx,ny,nz r,g,b [rx,ry,rz] [tx,ty,tz]

# Cylinder with rotation and translation
cy x,y,z ax,ay,az diameter height r,g,b [rx,ry,rz] [tx,ty,tz]

# Cone with rotation and translation
cn x,y,z ax,ay,az diameter height r,g,b [rx,ry,rz] [tx,ty,tz]

# Light with translation
L x,y,z brightness r,g,b [tx,ty,tz]

# Camera with rotation
C x,y,z nx,ny,nz fov [rx,ry,rz]
```

### Implementation Plan

#### Phase 1: Fix Parser (parser_objects.c)
1. Fix `parse_sphere_translation()`: Store OFFSET, not center
2. Fix `parse_plane_translation()`: Properly parse vector
3. Fix `parse_cylinder_translation()`: Actually parse and assign values
4. Fix `parse_cone_translation()`: Actually parse and assign values

#### Phase 2: Extend Camera & Light Parsing
1. Add rotation fields to t_camera (if not present)
2. Implement camera rotation parsing in parser_scene.c
3. Implement light translation parsing in parser_scene.c

#### Phase 3: Create Transformation Functions
- Location: src/functions/objects_helpers.c or new file
- Functions needed:
  - `apply_rotation_x()`, `apply_rotation_y()`, `apply_rotation_z()`
  - `apply_rotations()` (rx, ry, rz in order)
  - `apply_translation()`
  - `transform_vector()` (apply rotation only)
  - `transform_point()` (apply rotation then translation)

#### Phase 4: Apply Transformations in Ray-Object Intersections
- Files to update:
  - src/ray/hits.c (sphere, plane)
  - src/ray/hit_cylinder.c (cylinder)
  - src/ray/hits_cone.c (cone)
- Strategy: Apply inverse transformations to ray, then compute intersection

#### Phase 5: Test Scenes
Create scene files demonstrating transformations:
- `examples/translation_test.rt`: Translated spheres
- `examples/rotation_test.rt`: Rotated cylinders
- `examples/mixed_transforms.rt`: Both rotation and translation

#### Phase 6: Norminette Compliance
- Run norminette on all modified files
- Fix any violations

### Files to Modify
1. src/parser/parser_objects.c (FIX parsing functions)
2. src/parser/parser_scene.c (ADD camera/light transforms if needed)
3. include/minirt.h (ADD camera rotation fields if missing)
4. src/functions/objects_helpers.c (ADD transform functions)
5. src/ray/hits.c (APPLY transforms)
6. src/ray/hit_cylinder.c (APPLY transforms)
7. src/ray/hits_cone.c (APPLY transforms)
8. examples/*.rt (CREATE test scenes)

### Key Decisions
1. **Transformation order**: Rotation THEN Translation (standard in 3D graphics)
2. **Angle units**: Degrees (convert to radians internally if needed)
3. **Backward compatibility**: Scenes without transforms should work as-is
4. **Optional parameters**: Transform params should be optional in scene files
