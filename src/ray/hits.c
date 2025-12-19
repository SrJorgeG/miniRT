
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
    t_vec   oc;
    double  a;
    double  b;
    double  c;
    t_vec   poi[4];
    double  t[4];
    bool    t_valid[4];

    local_ray.origin = mat4_transform_point(cylinder->inverse_transform, ray.origin);
    local_ray.direction = mat4_transform_direction(cylinder->inverse_transform, ray.direction);
    local_ray.direction = vector_normalize(local_ray.direction);

    oc = local_ray.origin;
    a = pow(local_ray.direction.x, 2) + pow(local_ray.direction.y, 2);
    b = 2 * (oc.x * local_ray.direction.x + oc.y * local_ray.direction.y);
    c = pow(oc.x, 2) + pow(oc.y, 2) - 1;
    
    // COMPUTE b² - 4ac
    double  denom = sqrtf(pow(b, 2) - 4 * a * c);
    if (denom > 0.0)
    {
        // COMPUTE INTERSECTION VALUES
        t[0] = (-b + denom) / (2 * a);
        t[1] = (-b - denom) / (2 * a);
        // COMPUTE INTERSECTION POINTS
        poi[0] = vector_sum(local_ray.origin, vector_multiplication(local_ray.direction, t[0]));
        poi[1] = vector_sum(local_ray.origin, vector_multiplication(local_ray.direction, t[1]));
        // VALIDATE I. P. 
        if ((t[0] > 0.0) && (fabs(poi[0].z) < 1.0)) 
        {
           t_valid[0] = true;
        }
        else
        {
           t_valid[0] = false;
           t[0] = 100e6; 
        }
        if ((t[1] > 0.0) && (fabs(poi[1].z) < 1.0))
        {
           t_valid[1] = true;
        }
        else
        {
           t_valid[1] = false;
           t[1] = 100e6; 
        }
    }
    else
    {
        t_valid[0] = false;
        t_valid[1] = false;
        t[0] = 100e6;
        t[1] = 100e6; 
    }
    if (fabs(local_ray.direction.z - 0.0) < EPS)
    {
        t_valid[2] = false;
        t_valid[3] = false;
        t[0] = 100e6;
        t[1] = 100e6;
    }
    else
    {
        t[2] = (local_ray.origin.z - 1.0) / -local_ray.direction.z;
        t[3] = (local_ray.origin.z + 1.0) / -local_ray.direction.z;
        
        poi[2] = vector_sum(local_ray.origin ,vector_multiplication(local_ray.direction, t[2]));
        poi[3] = vector_sum(local_ray.origin ,vector_multiplication(local_ray.direction, t[3]));

        if ((t[2] > 0.0) && (sqrtf(pow(poi[2].x, 2) + pow(poi[2].y, 2)) < 1.0))
        {
            t_valid[2] = true;
        }
        else
        {
            t_valid[2] = false;
            t[2] = 100e6;
        }
        if ((t[3] > 0.0) && (sqrtf(pow(poi[3].x, 2) + pow(poi[3].y, 2)) < 1.0))
        {
            t_valid[3] = true;
        }
        else
        {
            t_valid[3] = false;
            t[3] = 100e6;
        }
    }
    if ((!t_valid[0]) && (!t_valid[1]) && (!t_valid[2]) && (!t_valid[3]))
        return (0);
    
    int     min_index = 0;
    double  min_value = 10e6;
    int i = -1;
    while (t[++i])
        if (t[i] < min_value)
        {
            min_value = t[i];
            min_index = i;
        }
    t_vec   intersection;
    t_vec   valid_poi = poi[min_index];
    if (min_index < 2)
    {
        intersection = mat4_transform_point(cylinder->inverse_transform, valid_poi);
        t_vec   org_normal;
        t_vec   new_normal;
        t_vec   local_origin = {0, 0, 0};
        t_vec   global_origin = mat4_transform_point(cylinder->transform, local_origin);;
        org_normal.x = valid_poi.x;
        org_normal.y = valid_poi.y;
        org_normal.z = 0.0;
        new_normal = mat4_transform_normal(cylinder->transform, org_normal);
        new_normal = vector_normalize(new_normal);
        
        *obj_distance = min_value;
        return 1;
    }
}

