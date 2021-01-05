/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:40:10 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 01:08:18 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_error_identifier(char *line)
{
	ft_printf("Error\n** SCENE FILE ERROR **\n");
	ft_printf("** Scene file(*.rt) has wrong identifier line **\n");
	ft_printf("** this line: \"%s\" **", line);
	exit(EXIT_SUCCESS);
}

void	parse_error_data_count(char **data, int n, char *line)
{
	int		i;

	i = 0;
	while (data[i] != NULL)
		i++;
	if (i != n)
	{
		ft_printf("Error\n** SCENE FILE ERROR **\n");
		ft_printf("** Wrong number of data\n");
		ft_printf("** this line: \"%s\" **", line);
		exit(EXIT_SUCCESS);
	}
}

void	parse_error_img_filepath(void *img, char *line)
{
	if (img == NULL)
	{
		ft_printf("Error\n** SCENE FILE ERROR **\n");
		ft_printf("** Wrong img path \n");
		ft_printf("** this line: \"%s\" **", line);
		exit(EXIT_SUCCESS);
	}
}

void	data_is_double(char *str, char *line)
{
	char *start_point;

	start_point = str;
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == '.')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == 0)
		return ;
	ft_printf("Error\n** SCENE FILE ERROR **\n");
	ft_printf("** Wrong type of data : IS NOT DOUBLE\n");
	ft_printf("** this line: \"%s\" **\n", line);
	ft_printf("** this data: \"%s\" **\n", start_point);
	exit(EXIT_SUCCESS);
}

void	data_is_integer(char *str, char *line)
{
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str))
		++str;
	if (*str == 0)
		return ;
	ft_printf("Error\n** SCENE FILE ERROR **\n");
	ft_printf("** Wrong type of data : IS NOT INTEGER\n");
	ft_printf("** this line: \"%s\" **\n", line);
	ft_printf("** this data: \"%s\" **\n", str);
	exit(EXIT_SUCCESS);
}
