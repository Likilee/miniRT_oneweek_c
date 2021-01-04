/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 17:07:13 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 17:08:04 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

void	*mlx_init();
void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
int		mlx_clear_window(void *mlx_ptr, void *win_ptr);
int		mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
void	*mlx_new_image(void *mlx_ptr, int width, int height);
char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
							int *size_line, int *endian);
int		mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr,
								int x, int y);
int		mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);
int		mlx_loop (void *mlx_ptr);
void	*mlx_png_file_to_image(void *mlx_ptr, char *file,
								int *width, int *height);
int		mlx_hook(void *win_ptr, int x_event, int x_mask,
				int (*funct)(), void *param);
int		mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

#endif
