// #include "control.h"

// void		cntl_object_translate_x_pos(t_cntl *cntl)
// {
// 	if (cntl->selected->type == SP)
// 			((t_sphere *)(cntl->selected->element))->center.x += 0.1;
// 		// else if (cntl->selected->type == PL)
// 		// 	((t_plane *)(cntl->selected))->p.x += 1.0;
// 		// else if (cntl->selected->type == SQ)
// 		// 	((t_square *)(cntl->selected))->center.x += 1.0;
// 		// else if (cntl->selected->type == CY)
// 		// 	((t_cylinder *)(cntl->selected))->center_bottom.x += 1.0;
// 		// else if (cntl->selected->type == TR)
// 		// {
// 		// 	((t_triangle *)(cntl->selected))->p0.x += 1.0;
// 		// 	((t_triangle *)(cntl->selected))->p1.x += 1.0;
// 		// 	((t_triangle *)(cntl->selected))->p2.x += 1.0;
// 		// }
// 		// else if (cntl->selected->type == CB)
// 		// 	((t_cube *)(cntl->selected))->center.x += 1.0;
// 		// else if (cntl->selected->type == PM)
// 		// 	((t_pyramid *)(cntl->selected))->center.x += 1.0;
// 	render_preview(cntl->scene, cntl->img);
// 	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
// }

// void		cntl_object_translate_y_pos(t_cntl *cntl)
// {
// 	if (cntl->mode != 1)
// 		return ;
// 	if (cntl->selected->type == SP)
// 			((t_sphere *)(cntl->selected->element))->center.y += 0.1;
// 	render_preview(cntl->scene, cntl->img);
// 	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
// }

// void		cntl_object_scale(t_cntl *cntl)
// {
// 	if (cntl->selected->type == SP)
// 	{
// 		((t_sphere *)(cntl->selected->element))->radius += 0.05;
// 		((t_sphere *)(cntl->selected->element))->radius2 = ((t_sphere *)(cntl->selected->element))->radius * ((t_sphere *)(cntl->selected->element))->radius;
// 	}
// 	// else if (cntl->selected->type == SQ)
// 	// 	((t_square *)(cntl->selected))->side_len += 0.2;
// 	// else if (cntl->selected->type == CY)
// 	// {
// 	// 	((t_cylinder *)(cntl->selected))->height += 0.2;
// 	// 	((t_cylinder *)(cntl->selected))->radius += 0.1;
// 	// }
// 	// // else if (cntl->selected->type == TR)
// 	// // 	{
// 	// // 		((t_triangle *)(cntl->selected))->p0.x += 1.0;
// 	// // 		((t_triangle *)(cntl->selected))->p1.x += 1.0;
// 	// // 		((t_triangle *)(cntl->selected))->p2.x += 1.0;
// 	// // 	}
// 	// else if (cntl->selected->type == CB)
// 	// 	((t_cube *)(cntl->selected))->side_len += 0.1;
// 	// else if (cntl->selected->type == PM)
// 	// 	((t_pyramid *)(cntl->selected))->center.x += 0.1;
// 	render_preview(cntl->scene, cntl->img);
// 	mlx_put_image_to_window(cntl->mlx, cntl->win, cntl->img->img, 0, 0);
// }

// //kilee
// void	cntl_cam_rotate(int button, t_cntl *cntl)
// {
// 	printf("camera rotate mode on!\n use arrow key if you want see another direction\n");
// 	cntl->mode = 3;
// }

// void		cntl_cam_rotate_off(t_cntl *cntl)
// {
// 	printf("camera rotate mode off!\n now just camera mode\n");
// 	cntl->mode = 2;
// }

// // mijeong2

// void	cntl_cam_rotate(int keycode, t_cntl *cntl)
// {
// 	t_vec3		world;
// 	t_camera	*camera;
// 	int			y;
// 	double		theta;

// 	camera = cntl->scene->cam_onair;
// 	world = camera->dir;
// 	theta = deg_to_rad(5);
// 	if (keycode == 124)
// 	t_matrix44	*cam_rotate;
// 	t_camera	*cam;

// 	cam = cntl->scene->cam_onair;
// 	if (button == 1 || button == 7) // -> 좌클릭
// 		cam_rotate = rotate(vec3(0,5,0));
// 	else if (button == 2 || button == 6) // -> 방향키 왼쪽
// 		cam_rotate = rotate(vec3(0,-5,0));
// 	else if (button == 5) // up
// 		cam_rotate = rotate(vec3(+5,0,0));
// 	else if (button == 4) // down
// 		cam_rotate = rotate(vec3(-5,0,0));
// 	else
// 	{
// 		printf("you click button : %d\n", button);
// 		return ;
// 	}
// 	printf("%f, %f, %f\n", camera->dir.x, camera->dir.y, camera->dir.z);
// }

// // mijeong
// // void	cntl_cam_rotate(int keycode, t_cntl *cntl)
// // {
// // 	// t_vec3		offset;
// // 	t_vec3		world;
// // 	t_camera	*camera;
// // 	double		theta;
// // 	double		a;
// // 	double		b;

// 	theta = deg_to_rad(40);
// 	// offset = cntl->scene->cam_onair->orig;
// 	// cntl->scene->cam_onair->orig = vminus(cntl->scene->cam_onair->orig, offset);
// 	if (keycode == 124)
// 	{
// 		printf("you press right arrow key\n");
// 		cntl->scene->cam_onair->dir.x = cntl->scene->cam_onair->dir.x * cos(theta)
// 									+ cntl->scene->cam_onair->dir.x * sin(theta);
// 		cntl->scene->cam_onair->dir.z = cntl->scene->cam_onair->dir.z * -sin(theta)
// 									+ cntl->scene->cam_onair->dir.z * cos(theta);
// 	}
// 	// cntl->scene->cam_onair->orig = vplus(cntl->scene->cam_onair->orig, offset);
// }

// void	cntl_light_on(t_cntl *cntl)
// {
// 	cntl->mode = 3;
// 	printf("< light mode >!\n[right arrow] key : next light\n");
// }

// void	cntl_light_off(t_cntl *cntl)
// {
// 	cntl->mode = 0;
// 	cntl->selected = NULL;
// 	printf("< Now default mode >\n");
// }

// void	cntl_light_select(t_cntl *cntl)
// {
// 	t_objects	*temp;

// 	if (cntl->selected == 0 || cntl->selected->next == 0)
// 		temp = (t_objects *)cntl->scene->world;
// 	else
// 		temp = (t_objects *)cntl->selected->next;
// 	while (temp && temp->type != LIGHT)
// 		temp = temp->next;
// 	if (temp == 0)
// 	{
// 		temp = (t_objects *)cntl->scene->world;
// 		while (temp && temp->type != LIGHT)
// 			temp = temp->next;
// 		cntl->selected = temp;	
// 		printf("마지막 조명입니다.\n");
// 	}
// 	else
// 	{
// 		cntl->selected = temp;
// 		printf("다음 조명입니다.\n");
// 	}
// 	printf("%f %f %f\n", ((t_light *)(cntl->selected->element))->p.x, ((t_light *)(cntl->selected->element))->p.y, ((t_light *)(cntl->selected->element))->p.z);
// }

// void	cntl_light(t_cntl *cntl, int keycode)
// {
// 	if (keycode == 53 && cntl->mode == 3) // 광원 모드에서 나감. esc
// 		cntl_light_off(cntl);
// 	else if (keycode == 124 && cntl->mode == 3) // 광원 바꾸기. 오른쪽 방향키
// 		cntl_light_select(cntl);
// 	else if (keycode == 2 && cntl->mode == 3)
// 		cntl_light_translate_pos_x(cntl);
// }
// // 	world = vec3(0, 0, -1);
// // 	camera = cntl->scene->cam_onair;
// // 	a = -atan(camera->dir.x / -camera->dir.z);
// // 	b = -atan(camera->dir.y / -camera->dir.z);
// // 	// offset = vminus(world, camera->dir);
// // 	camera->dir = world;
	
// // 	theta = deg_to_rad(5);
// // 	// world를 회전시켜줘야함. 근데 회전하는 함수를 모르겠음...
// // 	if (keycode == 124)
// // 	{
// // 		printf("you press right arrow key\n");
// // 		camera->dir.x = world.x * cos(theta) + world.z * sin(theta);
// // 		camera->dir.z = world.x * -sin(theta) + world.z * cos(theta);
// // 	}
// // 	else if (keycode == 123)
// // 	{
// // 		printf("you press left arrow key\n");
// // 		camera->dir.x = world.x * cos(-theta) + world.z * sin(-theta);
// // 		camera->dir.z = world.x * -sin(-theta) + world.z * cos(-theta);
// // 	}
// // 	world = camera->dir;
// // 	// y축 회전
// // 	camera->dir.x = cos(a) * world.x + sin(a) * world.z;
// // 	camera->dir.z = -sin(a) * world.x + cos(a) * world.z;
// // 	world = camera->dir;
// // 	// x축 회전
// // 	camera->dir.y = cos(b) * world.y + -sin(b) * world.z;
// // 	camera->dir.z = sin(b) * world.y + cos(b) * world.z;
// // 	camera->dir = vunit(camera->dir);
// // 	dprintf(2, "%f, %f, %f\n", camera->dir.x, camera->dir.y, camera->dir.z);
// // 	// camera->dir = vminus(camera->dir, offset);
// // 	// world - offset
// // }

// // void		cntl_cam_rotate(int keycode, t_cntl *cntl)
// // {
// // 	t_point3		offset;
// // 	double			theta;

// // 	theta = deg_to_rad(40);
// // 	// offset = cntl->scene->cam_onair->orig;
// // 	// cntl->scene->cam_onair->orig = vminus(cntl->scene->cam_onair->orig, offset);
// // 	if (keycode == 124)
// // 	{
// // 		printf("you press right arrow key\n");
// // 		cntl->scene->cam_onair->dir.x = cntl->scene->cam_onair->dir.x * cos(theta)
// // 									+ cntl->scene->cam_onair->dir.x * sin(theta);
// // 		cntl->scene->cam_onair->dir.z = cntl->scene->cam_onair->dir.z * -sin(theta)
// // 									+ cntl->scene->cam_onair->dir.z * cos(theta);
// // 	}
// // 	// cntl->scene->cam_onair->orig = vplus(cntl->scene->cam_onair->orig, offset);
// // }
