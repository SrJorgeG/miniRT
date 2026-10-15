/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:05:17 by dcid-san          #+#    #+#             */
/*   Updated: 2026/02/06 02:44:23 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static uint32_t	trace_pixel(t_scene *scene, int x, int y, int *obj_id)
{
	t_hit	hit;
	t_ray	ray;
	t_vec	pixel_center;

	pixel_center = find_pixel_on_viewport(x, y, scene);
	ray = get_ray_from_pixel(scene, scene->image_center, pixel_center);
	hit = get_hits(scene, ray);
	*obj_id = -1;
	if (!hit.hit)
		return (color_to_int_no_alpha((t_color){0, 0, 0}));
	*obj_id = hit.object->id;
	return (color_to_int_no_alpha(calculate_lighting(&hit, scene)));
}

static void	fill_block(t_rjob *job, int x, int y, uint32_t color)
{
	int	bx;
	int	by;

	by = y;
	while (by < y + job->step && by < job->scene->screen_h)
	{
		bx = x;
		while (bx < x + job->step && bx < job->scene->screen_w)
			mlx_put_pixel(job->img, bx++, by, color);
		by++;
	}
}

static void	*render_rows(void *arg)
{
	t_rjob		*job;
	int			x;
	int			y;
	int			obj_id;
	uint32_t	color;

	job = arg;
	y = job->id * job->step;
	while (y < job->scene->screen_h)
	{
		x = 0;
		while (x < job->scene->screen_w)
		{
			color = trace_pixel(job->scene, x, y, &obj_id);
			fill_block(job, x, y, color);
			if (job->ids)
				job->ids[y * job->scene->screen_w + x] = obj_id;
			x += job->step;
		}
		y += NTHREADS * job->step;
	}
	return (NULL);
}

static void	run_threads(t_scene *scene, mlx_image_t *img, int *ids, int step)
{
	pthread_t	tid[NTHREADS];
	t_rjob		jobs[NTHREADS];
	int			created[NTHREADS];
	int			i;

	i = -1;
	while (++i < NTHREADS)
	{
		jobs[i] = (t_rjob){scene, img, ids, i, step};
		created[i] = (pthread_create(&tid[i], NULL, render_rows,
					&jobs[i]) == 0);
		if (!created[i])
			render_rows(&jobs[i]);
	}
	i = -1;
	while (++i < NTHREADS)
		if (created[i])
			pthread_join(tid[i], NULL);
	i = -1;
	while (ids && ++i < scene->screen_w * scene->screen_h)
		if (ids[i] >= 0)
			add_pixel_to_cache(&scene->pixel_cache[ids[i]],
				i % scene->screen_w, i / scene->screen_w);
}

void	render_frame(t_scene *scene, mlx_t *mlx, mlx_image_t *img, int step)
{
	int	*ids;

	scene->is_rendered = 0;
	prepare_objects(scene);
	scene->image_center = vector_sum(scene->map->camera.view_point,
			scene->map->camera.orientation_nor);
	ids = NULL;
	if (step == 1)
	{
		clear_cache(scene);
		ids = malloc(sizeof(int) * scene->screen_w * scene->screen_h);
		if (!ids)
			exit_error("Error. render malloc\n", scene);
	}
	run_threads(scene, img, ids, step);
	free(ids);
	if (DEBUG)
		printf("Render finished (step %d)\n", step);
	if (!scene->on_window && mlx_image_to_window(mlx, img, 0, 0) < 0)
		exit_error("Error. mlx_image_to_window\n", scene);
	scene->on_window = 1;
	scene->is_rendered = 1;
}
