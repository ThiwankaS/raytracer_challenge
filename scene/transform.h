# ifndef FT_TRANSFORM_H
# define FT_TRANSFORM_H

# include "matrix.h"

# define PI 3.14159

t_matrix *translator(double x, double y, double z);
t_matrix *scalor(double x, double y, double z);
t_matrix *rotate_x_axis(double radian);
t_matrix *rotate_y_axis(double radian);
t_matrix *rotate_z_axis(double radian);
t_matrix *shearing(double xy, double xz, double yx, double yz, double zx, double zy);

# endif
