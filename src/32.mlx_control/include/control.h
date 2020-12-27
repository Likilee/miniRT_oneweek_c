#ifndef CONTROL_H
# define CONTROL_H

# include "scene.h"
# include "mlx.h"
# include "trace.h"

void		my_mlx_control(t_cntl *cntl);
int			cntl_object_select(int button, int x, int y, t_cntl *cntl);
void		get_display_resolution(t_cntl *cntl);

#endif
