/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:31:10 by fsugimot          #+#    #+#             */
/*   Updated: 2020/10/09 23:42:44 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strlen(const char *c)
{
	int	index;

	index = 0;
	if (!c)
		return (0);
	while (c[index])
		++index;
	return (index);
}

char	*ft_strdup(const char *c)
{
	char	*ret;
	int		alloc_size;

	alloc_size = ft_strlen(c);
	ret = malloc(alloc_size + 1);
	if (!ret)
		return (ret);
	ret[alloc_size--] = 0;
	while (alloc_size > -1)
	{
		ret[alloc_size] = c[alloc_size];
		alloc_size--;
	}
	return (ret);
}

void	super_write(char *s, int flg)
{
	int	ind;

	if (flg)
	{
		ind = ft_strlen(s);
		while (s[ind])
		{
			if (s[ind] != -1)
				write(1, &s[ind], 1);
			else
				write(1, 0, 1);
			++ind;
		}
	}
	write(1, s, ft_strlen(s));
}

char	*cut_str(char *str, int size)
{
	int		ind;
	char	*ret;

	if (!str)
		return (0);
	if (size <= 0)
		return (str);
	ret = malloc(size + 1);
	if (!ret)
		return (0);
	ind = 0;
	while (ind < size)
	{
		ret[ind] = str[ind];
		ind++;
	}
	ret[ind] = 0;
	free(str);
	return (ret);
}

char	*extend_str(char *str, int size, int cpy_limit)
{
	int		ind;
	int		tmp;
	char	*ret;

	if (!str || size < 0)
		return (str);
	ret = malloc(size + 1);
	if (!ret)
		return (0);
	ret[size] = 0;
	ind = 0;
	if (cpy_limit < 0 || cpy_limit < ft_strlen(str))
		tmp = size - ft_strlen(str);
	else
		tmp = size - ft_min(cpy_limit, ft_strlen(str));
	while (ind < tmp)
		ret[ind++] = ' ';
	while (ind < size)
	{
		ret[ind] = str[ind - tmp];
		++ind;
	}
	free(str);
	return (ret);
}
