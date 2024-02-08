
Library functions:
------------------
t_vector	*vector_add(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, t_vector b);
t_vector	vector_negate(t_vector vector);
t_vector	scalar_mult(t_vector vector, double c);
t_vector	scalar_div(t_vector vector, double c);
double		magnitude(t_vector vector);
t_vector	normalize(t_vector vector);
double		dot(t_vector a, t_vector b);
t_vector	cross(t_vector a, t_vector b);
t_color		color_add(t_color a, t_color b);
t_color		color_mult(t_color a, t_color b);
t_color		hadamard_product(t_color a, t_color b);
int			double_equal(double a, double b);
int			matrix_equal(t_matrix a, t_matrix b);
t_matrix	identity_matrix();
t_matrix	matrix_mult_m(t_matrix a, t_matrix b);
t_vector	matrix_mult_v(t_matrix m, t_vector v);
t_matrix	transpose(t_matrix m);
t_matrix	inverse(t_matrix m);
double		determinant(t_matrix m);
t_matrix	submatrix(t_matrix m, int i, int j);
double		minor(t_matrix m, int i, int j);
double		cofactor(t_matrix m, int i, int j);
t_matrix	translation(t_vector vector);
t_matrix	scaling(t_vector vector);
t_vector	rotation_x(t_vector vector);
t_vector	rotation_y(t_vector vector);
t_vector	rotation_z(t_vector vector);
// shearing: I dont know if we need that for planes
double		discriminant(double a, double b, double c);

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

// This is one intersect_* function out of 3 for the 3 different types
t_intersections intersect_sphere(t_sphere sphere, t_ray ray)
{
	computes intersections with this object 
	ray2 = transform(ray, inverse(object.transformation_matrix))
	return intersections
}

t_intersection intersection(double t, t_object object)
{
	creates an intersection object 
	return intersection 
}

t_intersection	hit(t_intersections intersections)
{
	computes the hit, that is the smallest positive distance
	Here we search for the right intersection 
	return intersection 
}

t_ray transform(t_ray ray, t_matrix matrix)
{
	applies transformation matrix to ray
	return ray 
}

void	set_transform(t_object object t_matrix matrix)
{
	Determines the object type and 
	sets the transformation matrix field in the object
}

//************************************************

t_vector	normal_at(t_object object, t_vector point)
{
	Code p.82
	Determines object type and calls the specific normal_at function 
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
	iterates over all objects and returns all intersections (we can 
		add all intersections objects into one)
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

//************************************************

Initialisierungen:
------------------
camera
world
objects must be initialized: for instance material field must be created 
