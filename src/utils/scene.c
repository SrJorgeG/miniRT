/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:05:17 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/06 13:20:57 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>

void setup_camera(t_camera *camera)
{
    t_vec *world_up;

    // En principio la orientacion viene normalizada si he entendido bien con lo que no se normaliza.
    camera->radial_fov = (camera->fov * M_PI) / 180;
    camera->focal = FOCAL;
    world_up = vector_constructor(0.0, 1.0, 0.0);
    // CASO ESPECIAL: Si la cámara mira justo hacia arriba o abajo, forward y world_up son paralelos.
    // Su producto vectorial sería cero, lo cual es un error.
    // Si eso pasa, usamos un 'world_up' temporal diferente para evitar el problema.
     if (fabs(vector_dot_prod(camera->orientation_nor, world_up)) > 0.999)
     {
         free(world_up);
         world_up = vector_constructor(0.0, 0.0, 1.0); // Usamos el eje Z como referencia temporal
     }
    camera->right = vector_dup(vector_normalize(vector_cross_prod(camera->orientation_nor, world_up)));
    camera->up = vector_dup(vector_cross_prod(camera->right, camera->orientation_nor));

}

void setup_scene(t_scene *scene, t_camera *camera)
{
    scene->aspect = (t_real)scene->screen_w / (t_real)scene->screen_h;
    scene->viewport_w = 2.0 * tan(camera->radial_fov * 2.0);
    scene->viewport_h = scene->viewport_w / scene->aspect;
}
