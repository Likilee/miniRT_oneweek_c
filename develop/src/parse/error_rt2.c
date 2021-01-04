/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_rt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:40:10 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 01:08:26 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_data_set_double(char **data, int n, char *line)
{
	int		i;

	parse_error_data_count(data, n, line);
	i = -1;
	while (++i < n)
		data_is_double(data[i], line);
}

void	data_is_zero_to_one(char *str, char *line)
{
	data_is_double(str, line);
	if (atod(str) >= -1 && atod(str) <= 1)
		return ;
	ft_printf("Error\n** SCENE FILE ERROR **\n");
	ft_printf("** Wrong type of data : IS NOT FEET IN [0, 1]\n");
	ft_printf("** this line: \"%s\" **\n", line);
	ft_printf("** this data: \"%s\" **\n", str);
	exit(EXIT_SUCCESS);
}

void	parse_data_set_zero_to_one(char **data, int n, char *line)
{
	int			i;

	parse_error_data_count(data, n, line);
	i = -1;
	while (++i < n)
		data_is_zero_to_one(data[i], line);
}

void	data_is_in_rgb_range(char *str, char *line)
{
	data_is_integer(str, line);
	if (ft_atoi(str) >= 0 && ft_atoi(str) <= 255)
		return ;
	ft_printf("Error\n** SCENE FILE ERROR **\n");
	ft_printf("** Wrong type of data : IS NOT FEET IN RGB RANGE[0, 255] **\n");
	ft_printf("** this line: \"%s\" **\n", line);
	ft_printf("** this data: \"%s\" **\n", str);
	exit(EXIT_SUCCESS);
}

void	data_is_in_degree_range(char *str, char *line)
{
	data_is_double(str, line);
	if (atod(str) >= 0 && atod(str) <= 180)
		return ;
	ft_printf("Error\n** SCENE FILE ERROR **\n");
	ft_printf("** Wrong type of data : NOT FEET IN DEGREE RANGE[0, 180] **\n");
	ft_printf("** this line: \"%s\" **\n", line);
	ft_printf("** this data: \"%s\" **\n", str);
	exit(EXIT_SUCCESS);
}
