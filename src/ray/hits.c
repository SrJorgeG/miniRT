
#include "../../include/minirt.h"
#define EPS 1e-6

// Gracias a https://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html Por este post que nos permitio hacer la función
int	hit_sphere(t_ray ray, t_sphere *sphere, double *obj_distance)
{
	t_vec	oc;
	t_vec	equation;

	oc = vector_rest(ray.origin, sphere->center);
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

int hit_plane(t_ray ray, t_plane *plane, double *obj_distance)
{
    double denom;
    double t;

    denom = vector_dot_prod(ray.direction, plane->vector);
  
    if (fabs(denom) > EPS)
    {
        t = vector_dot_prod(vector_rest(plane->point, ray.origin), plane->vector) / denom;
        if (t > EPS)
        {
            *obj_distance = t;
            return 1;
        }
    }
    return 0;
}

int hit_cylinder(t_ray ray, t_cylinder *cylinder, double *obj_distance)
{
    t_ray   local_ray;
    double  t_body = -1.0;
    double  t_cap = -1.0;
    int     hit_body = 0;
    int     hit_caps = 0;

    // Transformar rayo
    local_ray.origin = mat4_transform_point(cylinder->inverse_transform, 
                                            ray.origin);
    local_ray.direction = mat4_transform_direction(cylinder->inverse_transform, 
                                                   ray.direction);
    local_ray.direction = vector_normalize(local_ray.direction);

    // --- CUERPO DEL CILINDRO ---
    double a = local_ray.direction.x * local_ray.direction.x + 
               local_ray.direction.y * local_ray.direction.y;
    double b = 2.0 * (local_ray.origin.x * local_ray.direction.x + 
                      local_ray.origin.y * local_ray.direction.y);
    double c = local_ray.origin.x * local_ray.origin.x + 
               local_ray.origin.y * local_ray.origin.y - 1.0;
    
    double disc = b * b - 4.0 * a * c;
    
    if (disc >= 0.0)
    {
        double t0 = (-b - sqrt(disc)) / (2.0 * a);
        double t1 = (-b + sqrt(disc)) / (2.0 * a);
        double t_test;
        
        if (t0 > 0.001)
            t_test = t0;
        else if (t1 > 0.001)
            t_test = t1;
        else
            t_test = -1.0;
        
        if (t_test > 0)
        {
            t_vec p = vector_sum(local_ray.origin, 
                                vector_multiplication(local_ray.direction, t_test));
            if (p.z >= -1.0 && p.z <= 1.0)
            {
                t_body = t_test;
                hit_body = 1;
            }
        }
    }

    // --- TAPAS DEL CILINDRO ---
    if (fabs(local_ray.direction.z) > 0.0001)
    {
        // Tapa inferior (z = -1)
        double t_bottom = (-1.0 - local_ray.origin.z) / local_ray.direction.z;
        if (t_bottom > 0.001)
        {
            t_vec p = vector_sum(local_ray.origin, 
                                vector_multiplication(local_ray.direction, t_bottom));
            double radius_sq = p.x * p.x + p.y * p.y;
            if (radius_sq <= 1.0)
            {
                if (!hit_caps || t_bottom < t_cap)
                {
                    t_cap = t_bottom;
                    hit_caps = 1;
                }
            }
        }
        
        // Tapa superior (z = +1)
        double t_top = (1.0 - local_ray.origin.z) / local_ray.direction.z;
        if (t_top > 0.001)
        {
            t_vec p = vector_sum(local_ray.origin, 
                                vector_multiplication(local_ray.direction, t_top));
            double radius_sq = p.x * p.x + p.y * p.y;
            if (radius_sq <= 1.0)
            {
                if (!hit_caps || t_top < t_cap)
                {
                    t_cap = t_top;
                    hit_caps = 1;
                }
            }
        }
    }

    // Elegir el hit más cercano
    if (hit_body && hit_caps)
        *obj_distance = fmin(t_body, t_cap);
    else if (hit_body)
        *obj_distance = t_body;
    else if (hit_caps)
        *obj_distance = t_cap;
    else
        return (0);
    
    return (1);
}

