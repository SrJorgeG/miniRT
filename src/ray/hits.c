
#include "../../include/minirt.h"


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
    const double EPS = 1e-6;

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


static double hit_cylinder_caps(t_ray ray, t_cylinder *cyl, double radius, double half_h)
{
    double  denom;
    double  t;
    double  dist;
    double  closest;
    t_vec   hit;
    t_vec   cap_center;
    
    denom = vector_dot_prod(ray.direction, cyl->axys);
    if (fabs(denom) < 1e-6)
        return (-1);
    
    closest = INFINITY;

    cap_center = vector_sum(cyl->center, 
                            vector_multiplication(cyl->axys, half_h));
    t = vector_dot_prod(vector_rest(cap_center, ray.origin), cyl->axys) / denom;
    
    if (t > 1e-6)
    {
        hit = vector_sum(ray.origin, vector_multiplication(ray.direction, t));
        dist = vector_lenght(vector_rest(hit, cap_center));
        if (dist <= radius)
            closest = t;
    }
    
    cap_center = vector_sum(cyl->center, 
                            vector_multiplication(cyl->axys, -half_h));
    t = vector_dot_prod(vector_rest(cap_center, ray.origin), cyl->axys) / denom;
    
    if (t > 1e-6 && t < closest)
    {
        hit = vector_sum(ray.origin, vector_multiplication(ray.direction, t));
        dist = vector_lenght(vector_rest(hit, cap_center));
        if (dist <= radius)
            closest = t;
    }
    
    return (closest == INFINITY ?  -1 : closest);
}

static double hit_cylinder_body(t_ray ray, t_cylinder *cyl, t_vec oc, 
                         double radius, double half_h)
{
    double  a, b, c;
    double  discriminant;
    double  t;
    double  h;
    
    
    a = vector_dot_prod(ray.direction, ray.direction) - 
        pow(vector_dot_prod(ray.direction, cyl->axys), 2);
    
    b = 2.0 * (vector_dot_prod(ray. direction, oc) - 
               vector_dot_prod(ray.direction, cyl->axys) * vector_dot_prod(oc, cyl->axys));
    
    c = vector_dot_prod(oc, oc) - 
        pow(vector_dot_prod(oc, cyl->axys), 2) - 
        radius * radius;

    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    
    t = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t > 1e-6)
    {
        h = vector_dot_prod(vector_sum(oc, vector_multiplication(ray.direction, t)), cyl->axys);
        if (fabs(h) <= half_h)
            return (t);
    }
    
    t = (-b + sqrt(discriminant)) / (2.0 * a);
    if (t > 1e-6)
    {
        h = vector_dot_prod(vector_sum(oc, vector_multiplication(ray.direction, t)), cyl->axys);
        if (fabs(h) <= half_h)
            return (t);
    }
    
    return (-1);
}

void get_cylinder_normal(t_hit *hit, t_cylinder *cyl, t_ray ray)
{
    t_vec   to_hit;
    double  h;
    double  half_h;
    t_vec   proj;
    
    to_hit = vector_rest(hit->p, cyl->center);
    h = vector_dot_prod(to_hit, cyl->axys);
    half_h = cyl->height / 2.0;
    
    if (fabs(fabs(h) - half_h) < 1e-3)
    {
        hit->normal = cyl->axys;
        if (h < 0)
            hit->normal = vector_multiplication(hit->normal, -1.0);
    }
    else
    {
        proj = vector_multiplication(cyl->axys, h);
        hit->normal = vector_normalize(vector_rest(to_hit, proj));
    }
    
    if (vector_dot_prod(ray.direction, hit->normal) > 0)
        hit->normal = vector_multiplication(hit->normal, -1.0);
}

int hit_cylinder(t_ray ray, t_cylinder *cyl, double *obj_distance)
{
    t_vec   oc;
    double  radius;
    double  half_h;
    double  t_body;
    double  t_cap;
    
    oc = vector_rest(ray.origin, cyl->center);
    radius = cyl->diameter / 2.0;
    half_h = cyl->height / 2.0;
    
    t_body = hit_cylinder_body(ray, cyl, oc, radius, half_h);
    t_cap = hit_cylinder_caps(ray, cyl, radius, half_h);
    
    if (t_body > 0 && t_cap > 0)
        *obj_distance = fmin(t_body, t_cap);
    else if (t_body > 0)
        *obj_distance = t_body;
    else if (t_cap > 0)
        *obj_distance = t_cap;
    else
        return (0);
    
    return (1);
}


