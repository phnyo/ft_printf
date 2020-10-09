/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flg_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:49:49 by fsugimot          #+#    #+#             */
/*   Updated: 2020/10/09 12:13:40 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_terminator(const char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' ||\
		c == 'x' || c == 'X' || c == 'o' || c == '%')
		return (1);
	return (0);
}

int	is_flg(char c)
{
	return (c == '-' || c == ' ' || c == '+' || c == '0' || c == '#');
}

int	str_to_int(const char *str, int *front, t_dataset **data)
{
	int			ret;
	int			cur;
	t_dataset	*tmp;

	ret = -2;
	cur = *front;
	tmp = *data;
	if (is_num(str[cur]))
		ret = 0;
	while (is_num(str[cur]))
	{
		ret *= 10;
		ret += str[cur] - '0';
		cur++;
	}
	*front = cur;
	return (ret);
}
