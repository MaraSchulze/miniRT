
Library functions:
------------------
double		discriminant(t_ray ray)
t_vector	translation(t_vector vector)
t_vector	scaling(t_vector vector)
t_vector	normalize(t_vector vector)
t_vector	transpose
double		dot(t_vector a, t_vector b)

//************************************************

t_ray	ray(t_vector origin, t_vector direction)
{
	creates the ray object
	return ray 
}

t_vector	position(t_ray ray, double t)
{
	computes point on ray in distance t
	return point 
}

t_intersections intersect(t_sphere sphere, t_ray ray)
{
	computes intersections with this object 
	ray2 = transform(ray, inverse(sphere.transformation_matrix))
	return intersections
}

t_intersection intersection(double t, t_sphere sphere)
{
	creates an intersection object 
	return intersection 
}

t_intersection	hit(t_intersections intersections)
{
	computes the hit, that is the smallest positive distance
	return intersection 
}

t_ray transform(t_ray ray, t_matrix matrix)
{
	applies transformation matrix to ray
	return ray 
}

void	set_transform(t_sphere sphere, t_matrix matrix)
{
	sets the transformation matrix field in the sphere
}

//************************************************

t_vector	normal_at(t_sphere sphere, t_vector point)
{
	Code p.82
	computes the normal vector 
	return world_normal
}

t_vector	reflect(t_vector in, t_vector normal)
{
	computes the reflection
	reflect_vector = in - normal * 2 * dot(in, normal)
	return reflect_vector
}

t_material	material(t_vector color, double ambient, double diffuse, double specular, double shininess)
{
	creates material object 
	return material
}

t_color lighting(t_material material, t_light light, t_vector point, t_vector eye, t_vector normal)
{
	computes the color at a point 
	Code p.88-89
	return color 
}

//************************************************

t_intersections	intersect_world(t_world world, t_ray)
{
	iterates over all objects and returns all intersections
	return intersections
}

t_computation prepare_computations(t_intersection intersection, t_ray ray)
{
	code p.94
	computes values for later use
	return computation
}

t_color	shade_hit(t_world world, t_computation computation)
{	
	return lighting(comps.object.material, world.light, comps.point, comps.eyev, comps.normalv)
}

t_color	color_at(t_world world, t_ray ray)
{
	Code p.97
	intersections = intersect_world(world, ray)
	intersection = hit(intersections)
	if there is no hit:
		return black
	computation = prepare_computations(intersection, ray)
	color = shade_hit(world, computation)
	return color 
}

t_matrix	view_transform(t_vector to, t_vector from, t_vector up)
{
	Code p. 99-100
	returns transformation_matrix for camera 
	return matrix 
}

t_camera	camera(int hsize, int vsize, int field_of_view)
{
	initializes camera
	transformation_matrix = view_transform(from, up, to)
	return camera 
}

t_ray	ray_for_pixel(t_camera camera, px, py)
{
	computes the ray from the pixel
	Code p.104
	return ray 
}

void	render(t_camera camera, t_world world)
{
	loop over x and y:
		ray = ray_for_pixel(camera, x, y)
		color = color_at(world, ray)
		write_pixel(x, y, color)
}