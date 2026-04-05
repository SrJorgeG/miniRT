# Pending Tasks for miniRT

## Mandatory Part Requirements Status

### ✅ Completed
- [x] Written in C with Norm compliance
- [x] Makefile with rules: $(NAME), all, clean, fclean, re, bonus
- [x] MiniLibX library integration
- [x] Window management (fluid, ESC key, red cross)
- [x] Three geometric objects: sphere, plane, cylinder
- [x] Cone implementation (bonus object already implemented)
- [x] Proper error handling with exit_error function
- [x] Scene file parsing (.rt format)
- [x] Basic ambient and diffuse lighting
- [x] Hard shadows implementation
- [x] Example scene files in examples/ directory
- [x] Memory management and leak prevention
- [x] README.md with proper format and AI usage description

### ❌ Requires Verification / Implementation

#### Translation and Rotation Transformations
- [ ] **Translation transformations**: Verify that objects, lights, and cameras support translation
  - Current scene files don't show translation syntax (e.g., `tx`, `ty`, `tz`)
  - Need to extend scene file format to support `tx`, `ty`, `tz` parameters
  - Implement transformation in parser (parser_objects.c)
  - Apply transformations in ray tracing calculations

- [ ] **Rotation transformations**: Verify that objects and cameras support rotation
  - Current scene files don't show rotation syntax (e.g., `rx`, `ry`, `rz`)
  - **Exception**: Spheres and lights cannot be rotated (per spec)
  - Need to extend scene file format to support `rx`, `ry`, `rz` parameters
  - Implement rotation matrices for cylinders, planes, cones
  - Update ray-object intersection calculations to handle rotations

#### Resizing Object Properties
- [ ] **Diameter resizing**: Verify sphere diameter and cylinder diameter can be modified
  - Check if parser correctly handles diameter/radius values
  - Test with various diameter values in scene files

- [ ] **Cylinder dimensions**: Verify width (diameter) and height resizing
  - Test with various dimension values

---

## Bonus Part Requirements Status

### ❌ Not Implemented (Must complete mandatory part first)
- [ ] **Specular reflection**: Implement full Phong reflection model with specular highlights
- [ ] **Color disruption**: Checkerboard pattern on objects
- [ ] **Colored and multi-spot lights**: Support for multiple lights with different colors
  - Current: Support for multiple lights exists, but color handling in mandatory part is "unused"
  - Need to implement and verify light color usage
- [ ] **Second-degree objects**: Cone, hyperboloid, paraboloid
  - Cone is already implemented (files exist: src/ray/hits_cone.c, src/objects/cone.c)
  - Verify cone implementation is complete and correct
  - Hyperboloid and paraboloid are NOT implemented
- [ ] **Bump map textures**: Implement bump mapping for realistic surface details

---

## Testing and Defense Preparation

- [ ] **Scene variety**: Create diverse test scenes for each mandatory feature
  - Simple sphere scene
  - Simple plane scene
  - Simple cylinder scene
  - Mixed geometry scene
  - Scene with multiple lights
  - Scene with various camera angles
  - Scene testing object transformations

- [ ] **Error handling tests**: Test invalid scene files
  - Missing required elements (A, C, L)
  - Invalid data types
  - Out-of-range values (FOV, brightness, colors)
  - Malformed vectors

- [ ] **Edge cases testing**:
  - Very small/large FOV values
  - Objects with extreme dimensions
  - Rays grazing object surfaces
  - Ray origins inside objects

---

## Documentation

- [x] README.md created with all required sections
- [x] AI usage documented in README
- [ ] Inline code documentation for complex algorithms
- [ ] Function documentation comments (if needed for clarity)

---

## Summary

**Status**: Mandatory part appears to be mostly implemented, but **CRITICAL ISSUE FOUND**:
- **Transformations (translation and rotation)** do not appear to be implemented or documented in scene files
  - This is a **MANDATORY REQUIREMENT** per the subject
  - Must be addressed before submission

**Bonus**: Not applicable until mandatory part is verified as complete and perfect.

---

## Next Steps

1. **Immediate Priority**: Verify and implement transformation support (translation/rotation)
2. Add transformation syntax to scene file format
3. Update parser to handle new transformation parameters
4. Implement rotation matrices and transformation calculations
5. Test with scenes using transformations
6. Create comprehensive test scene suite
7. Verify all mandatory requirements are fully functional
8. Only then consider bonus implementation
