/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:43:39 by fsugimot          #+#    #+#             */
/*   Updated: 2020/08/27 09:48:45 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		fill_field(const char *args, int *front, t_dataset **data, int rot)
{
	int	num_r;
	int	ret;

	num_r = *front;
	while ((is_flg(args[num_r]) && !rot) || (rot && args[num_r] == '.'))
		num_r++;
	if (args[num_r] == '*')
		return (-1);
	ret = str_to_int(args, num_r, data);
	*front = num_r;
	return (ret);
}

int		fill_flg(const char *str, int front)
{
	int	ret;
	int	ind;

	ret = 0;
	ind = front;
	while (is_flg(str[ind]))
	{
		if (str[ind] == '-' && !(ret & MIN_FLG))
			ret |= (MIN_FLG);
		if (str[ind] == ' ' && !(ret & SPC_FLG))
			ret |= (SPC_FLG);
		if (str[ind] == '+' && !(ret & POS_FLG))
			ret |= (POS_FLG);
		if (str[ind] == '#' && !(ret & SHA_FLG))
			ret |= (SHA_FLG);
		if (str[ind] == '0' && !(ret & ZERO_FLG))
			ret |= (ZERO_FLG);
		ind++;
	}
	if (ret & ZERO_FLG && ret & MIN_FLG)
		ret |= ZERO_FLG;
	if (ret & POS_FLG && ret & SPC_FLG)
		ret |= SPC_FLG;
	return (ret);
}

int		parse_front(t_dataset **data, const char *args, int front, va_list list)
{
	t_dataset	*tmp;
	int			rear;

	rear = front;
	while (!is_terminator(args[rear]))
		rear++;
	tmp = *data;
	tmp->prefix = 0;
	tmp->flg = fill_flg(args, front);
	tmp->width = fill_field(args, &front, data, 0);
	if (tmp->width == -1)
		tmp->width = va_arg(list, int);
	tmp->precision = fill_field(args, &front, data, 1);
	if (tmp->precision == -1)
		tmp->precision = va_arg(list, int);
	return (1);
}
