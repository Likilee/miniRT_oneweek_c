/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_rt3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:40:10 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/04 01:08:23 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_data_set_rgb(char **data, int n, char *line)
{
	int			i;

	parse_error_data_count(data, n, line);
	i = -1;
	while (++i < n)
		data_is_in_rgb_range(data[i], line);
}

void	error_malloc(void)
{
	perror("Error\n** Malloc Failed in somewhere **");
	exit(0);
}
