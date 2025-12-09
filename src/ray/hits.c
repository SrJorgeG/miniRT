
#include "../../include/minirt.h"


// Gracias a https://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html Por este post que nos permitio hacer la función
int	hit_sphere(t_ray ray, t_sphere *sphere, double *obj_distance)
{
	t_vec	oc;
	t_vec	equation;

	oc = vector_rest(ray.origin, *sphere->center);
	equation.y = 2.0 * vector_dot_prod(oc, ray.direction);
    equation.z = vector_dot_prod(oc, oc) - sphere->radius * sphere->radius;
    double  discriminant = equation.y * equation.y - 4.0 * equation.z;
    if (discriminant < 0)
           return (0);
    double sqrt_disc = sqrt(discriminant);
    double t1 = (-equation.y - sqrt_disc) / 2.0;
    double t2 = (-equation.y + sqrt_disc) / 2.0;

    if (t1 > 0.0001)
    {
        *obj_distance = t1;
        return (1);
    }
    if (t2 > 0.0001)
    {
        *obj_distance = t2;
        return (1);
    }
    return (0);
}
