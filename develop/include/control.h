#ifndef CONTROL_H
# define CONTROL_H

# define DEFM 0
# define OBJM 1
# define CAMM 2
# define LIGM 3
# define RENM 4
# define SAVM 5

# define LIGHT_ON 0
# define LIGHT_OFF 1

# include "scene.h"
# include "mlx.h"
# include "trace.h"
# include "bitmap.h"
# include "parse.h"
# include "key_macos.h"

void		my_mlx_control(t_cntl *cntl);
int			cntl_key_press(int keycode, t_cntl *cntl);
int			cntl_key_release(int keycode, t_cntl *cntl);
int			cntl_mouse_click(int button, int x, int y, t_cntl *cntl);
int	        cntl_close(t_cntl *cntl);
void		cntl_default_mode_on(t_cntl *cntl);

// init
void		my_mlx_welcome(t_cntl *cntl);
void		cntl_init(t_cntl *cntl, char *filepath);
void		cntl_display_resolution(t_cntl *cntl);


// object
void		cntl_object_mode_on(t_cntl *cntl);
void		cntl_object(int keycode, t_cntl *cntl);
void		cntl_rotate_on_and_off(t_cntl *cntl);
void		cntl_object_select(int button, int x, int y, t_cntl *cntl);
void		cntl_object_deselect(t_cntl *cntl);
void		cntl_object_scale(t_cntl *cntl, int keycode);
void		cntl_object_scale_sp(t_cntl *cntl, double scale);
void		cntl_object_scale_sq(t_cntl *cntl, double scale);
void		cntl_object_scale_cy(t_cntl *cntl, double scale);
void		cntl_object_scale_cb(t_cntl *cntl, double scale);
void		cntl_object_scale_pm(t_cntl *cntl, double scale);
void		cntl_object_translate(t_cntl *cntl, int keycode);
void		cntl_object_translate2(t_cntl *cntl, t_vec3 *move);
void		cntl_object_translate_sp(t_cntl *cntl, t_vec3 *move);
void		cntl_object_translate_pl(t_cntl *cntl, t_vec3 *move);
void		cntl_object_translate_sq(t_cntl *cntl, t_vec3 *move);
void		cntl_object_translate_cy(t_cntl *cntl, t_vec3 *move);
void		cntl_object_translate_tr(t_cntl *cntl, t_vec3 *move);
void		cntl_object_translate_cb(t_cntl *cntl, t_vec3 *move);
void		cntl_object_translate_pm(t_cntl *cntl, t_vec3 *move);
void		cntl_object_rotate(t_cntl *cntl, int keycode);
// camera
void		cntl_camera_mode_on(t_cntl *cntl);
void		cntl_camera_select(t_cntl *cntl);
void		cntl_cam_rotate(int keycode, t_cntl *cntl);
void		cntl_camera_translate(int keycode, t_cntl *cntl);
void		cntl_camera(t_cntl *cntl, int keycode);
void		cntl_camera_hfov(int keycode, t_cntl *cntl);
// light
void		cntl_light_deselect(t_cntl *cntl);
void		cntl_light_translate(t_cntl *cntl, int keycode);
void		cntl_light_bright_up(t_cntl *cntl);
void		cntl_light_bright_down(t_cntl *cntl);
void		cntl_light(t_cntl *cntl, int keycode);
void		cntl_light_select(t_cntl *cntl);
void		cntl_light_mode_on(t_cntl *cntl);
void		cntl_light_on_and_off(t_cntl *cntl);

// save
void		cntl_save(t_cntl *cntl, int	keycode);
void		bmp_save(t_scene *scene);
void		bmp_save_direct(t_cntl *cntl);
void		cntl_save_phong(t_cntl *cntl);
void		cntl_save_path_trace(t_cntl *cntl);

// render
void		cntl_render_mode_on(t_cntl *cntl);
void		cntl_render_start(t_cntl *cntl);
void		cntl_render(t_cntl *cntl, int keycode);
void		cntl_render_phong(t_cntl *cntl);
void		cntl_render_path_trace(t_cntl *cntl);
void		cntl_render_filter_change(t_cntl *cntl);

// console message
void		console_msg_welcome(void);
void		console_msg_camera_mode(void);
void		console_msg_light_mode(void);
void		console_msg_object_mode(void);
void		console_msg_render_mode(void);

#endif
