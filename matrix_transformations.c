#include "minirt.h"


static t_matrix create_orientation(t_vector left_direction, t_vector up_direction, t_vector forward_direction)
{
    t_matrix orientation;

    orientation = identity_matrix(); // Initialize the orientation matrix as an identity matrix.

    // Set the orientation matrix values based on the input vectors representing directions.
    orientation.elements[0][0] = left_direction.x;
    orientation.elements[0][1] = left_direction.y;
    orientation.elements[0][2] = left_direction.z;
    orientation.elements[1][0] = up_direction.x;
    orientation.elements[1][1] = up_direction.y;
    orientation.elements[1][2] = up_direction.z;
    orientation.elements[2][0] = -forward_direction.x;
    orientation.elements[2][1] = -forward_direction.y;
    orientation.elements[2][2] = -forward_direction.z;

    return (orientation);
}
static t_matrix create_transformation(
    t_vector left_direction, t_vector up_direction, t_vector forward_direction, t_point camera_position)
{
    t_matrix orientation;
    t_matrix view_transformation;
    t_matrix translated;

    // Create the orientation matrix using create_orientation.
    orientation = create_orientation(left_direction, up_direction, forward_direction);

    // Create a translation matrix that moves the camera to the 'camera_position'.
    translated = translation(-camera_position.x, -camera_position.y, -camera_position.z);

    // Multiply the orientation matrix and the translation matrix to obtain the view transformation matrix.
    view_transformation = matrix_multiply(orientation, translated);

    return (view_transformation);
}

t_matrix view_transformation(t_point camera_position, t_point look_at_point, t_vector up_direction)
{
    t_vector left_direction;
    t_vector normalized_up_direction;
    t_vector true_up_direction;

    // Normalize the 'up_direction' vector.
    normalized_up_direction = tuple_normalize(up_direction);

    // Calculate the 'left_direction' vector and 'true_up_direction' vector using cross products.
    left_direction = vector_cross(look_at_point, normalized_up_direction);
    true_up_direction = vector_cross(left_direction, look_at_point);

    // Create the view transformation matrix using create_transformation.
    return (create_transformation(left_direction, true_up_direction, look_at_point, camera_position));
}
