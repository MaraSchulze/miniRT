/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marschul <marschul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:07:59 by marschul          #+#    #+#             */
/*   Updated: 2024/02/11 21:11:02 by marschul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_color	*get_black(t_garbage_collector *gc)
{
	t_color	*col;

	col = color(0.0, 0.0, 0.0, gc);
	return (col);
}

t_color	*get_ambient(double ambient, t_computation *computation, t_garbage_collector *gc)
{
	t_color	*result;

	result = color_mult(computation->effective_color, ambient, gc);
	return (result);
}

t_color	*get_diffuse(double diffuse, t_computation *computation, t_garbage_collector *gc)
{
	t_color	*result;

	if (computation->dot_light_normal < 0)
		result = get_black(gc);
	else
		result = color_mult(computation->effective_color, diffuse * computation->dot_light_normal, gc);
	return (result);
}

t_color	*get_specular(double specular, t_computation *computation, t_garbage_collector *gc)
{
	t_color	*result;
	double	factor;

	if (computation->dot_light_normal < 0)
		result = get_black(gc);
	else
	{
		if (computation->dot_reflect_eye <= 0)
			result = get_black(gc);
		else
		{
			//factor = pow(computation->dot_reflect_eye, material.shininess);
			factor = 1.0;
			result = color_mult(computation->light_color, specular * factor, gc);
		}
	}
	return (result);
}

t_color *lighting(t_computation *computation, t_garbage_collector *gc)
{
	t_material	*material;
	t_color	*ambient;
	t_color	*diffuse;
	t_color	*specular;
	t_color	*result;

	material = computation->material;
	ambient = get_ambient(material->ambient, computation, gc);
	diffuse = get_diffuse(material->diffuse, computation, gc);
	specular = get_specular(material->specular, computation, gc);
	result = color_add(ambient, diffuse, gc);
	result = color_add(result, specular, gc);
	return (result);
}

t_matrix	*get_transformation_matrix(t_object *object)
{
	if (object->id == 's')
		return object->sphere->transformation_matrix;
	if (object->id == 'p')
		return object->plane->transformation_matrix;
	if (object->id == 'c')
		return object->cylinder->transformation_matrix;
	return (NULL);
}

t_material	*get_material(t_object *object)
{
	if (object->id == 's')
		return (&object->sphere->material);
	if (object->id == 'p')
		return (&object->plane->material);
	if (object->id == 'c')
		return (&object->cylinder->material);
	return (NULL);
}

t_vector	*compute_point(t_ray *ray, t_intersection *intersection, t_garbage_collector *gc)
{
	t_vector	*vector;

	vector = vector_add(ray->origin, ray->direction, gc);
	normalize(vector, gc);
	vector = scalar_mult(vector, intersection->t, gc);
	return (vector);
}

t_vector	*normal_at(t_matrix *transformation_matrix, t_vector *p, t_garbage_collector *gc)
{
	t_matrix	*inv;
	t_matrix	*transp;
	t_vector	*object_point;
	t_vector	*object_normal;
	t_vector	*world_normal;

	inv = inverse(transformation_matrix, gc);
	object_point = matrix_mult_v(inv, p, gc);
	object_normal = vector_subtract(object_point, point(0, 0, 0, gc), gc);
	transp = transpose(inv, gc);
	world_normal = matrix_mult_v(transp, object_normal, gc);
	world_normal->dim[3] = 0;
	world_normal = normalize(world_normal, gc);
	return (world_normal);
}

t_vector	*reflect(t_vector *in, t_vector *normal, t_garbage_collector *gc)
{
	t_vector	*result;
	double		dot_product;

	result = scalar_mult(normal, 2.0, gc);
	dot_product = dot(in, normal);
	result = scalar_mult(result, dot_product, gc);
	result = vector_subtract(in, result, gc);
	return (result);
}

t_computation	*prepare_computations(t_intersection *intersection, t_ray *ray, t_light light, t_garbage_collector *gc)
{
	t_computation	*comp;
	t_matrix		*transformation_matrix;

	comp = (t_computation *) malloc(sizeof(t_computation));
	if (comp == NULL)
		exit_function(gc, "malloc fail\n", 1, true);
	else
		add_pointer_node(gc, comp);
	transformation_matrix = get_transformation_matrix(intersection->object);
	comp->material = get_material(intersection->object);
	comp->point	= compute_point(ray, intersection, gc);
	comp->lightv = vector_subtract(light.position, comp->point, gc);
	comp->normalv = normal_at(transformation_matrix, comp->point, gc);
	comp->eyev = vector_negate(ray->direction, gc);
	comp->reflectv = reflect(vector_negate(comp->lightv, gc), comp->normalv, gc);
	comp->effective_color = color_mult(comp->material->color, light.intensity, gc);
	comp->light_color = color(light.intensity, light.intensity, light.intensity, gc);
	comp->dot_light_normal = dot(comp->lightv, comp->normalv);
	comp->dot_reflect_eye = dot(comp->reflectv, comp->eyev);
	return (comp);
}

t_color	*shade_hit(t_intersection *intersection, t_computation *computation, t_garbage_collector *gc)
{	
	return lighting(computation, gc);
}

t_color	*color_at(t_world *world, t_ray *ray, t_garbage_collector *gc)
{
	t_intersections	*intersections;
	t_intersection	*intersection;
	t_computation	*computation;
	t_color			*col;

	// intersections = intersect_world(world, ray);
	// intersection = hit(intersections);
	if (intersection == NULL)
		return (get_black(gc));
	computation = prepare_computations(intersection, ray, world->light, gc);
	col = shade_hit(intersection, computation, gc);
	return (col);
}