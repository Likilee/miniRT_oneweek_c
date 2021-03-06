/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 06:51:00 by kihoonlee         #+#    #+#             */
/*   Updated: 2021/01/03 14:12:12 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Split string to words
** Special case#1. ("hello","\0") > return "hello"
*/

static size_t	ft_word_size(char const *s, char c)
{
	size_t size;

	size = 0;
	while (*s && *s++ != c)
		size++;
	return (size);
}

static size_t	ft_word_amount(char const *s, char c)
{
	size_t amount;

	amount = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		amount++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (amount);
}

char			*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*result;

	if (!(result = (char *)malloc(sizeof(char) * (n + 1))))
		return (0);
	i = 0;
	while (i < n)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

void		ft_free_arr(char **s)
{
	int	i;

	if (s == NULL)
		return ;
	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	size_t	count;
	size_t	wordlen;
	size_t	i;

	count = ft_word_amount(s, c);
	if (!(result = (char **)malloc(sizeof(char *) * (count + 1))))
		return (0);
	i = 0;
	while (i < count)
	{
		while (*s && *s == c)
			s++;
		wordlen = ft_word_size(s, c);
		if (!(result[i] = ft_strndup(s, wordlen)))
		{
			ft_free_arr(result);
			return (0);
		}
		s += wordlen;
		i++;
	}
	result[count] = 0;
	return (result);
}
