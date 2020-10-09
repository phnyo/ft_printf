/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:43:39 by fsugimot          #+#    #+#             */
/*   Updated: 2020/10/10 02:35:46 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		fill_field(const char *args, int *front, t_dataset *data, int rot)
{
	int			num_r;
	int			ret;

	num_r = *front;
	if (args[num_r] == '.' && !(data->flg & ZERO_FLG))
		data->flg |= ZERO_FLG;
	if (args[num_r] == '.')
		data->flg |= ZERO_PREC;
	while ((is_flg(args[num_r]) && !rot) || (rot && args[num_r] == '.' && \
		args[num_r + 1] != '.'))
		num_r++;
	if (args[num_r] == '*')
	{
		*front = num_r + 1;
		return (-1);
	}
	ret = str_to_int(args, &num_r, rot);
	*front = num_r;
	if (ret != -2 && ret != 0)
		data->flg &= ~ZERO_PREC;
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
		ret &= ~ZERO_FLG;
	if (ret & POS_FLG && ret & SPC_FLG)
		ret &= ~SPC_FLG;
	return (ret);
}

int		parse_front(t_dataset *data, const char *args, int front, va_list list)
{
	int			*cur;

	cur = &front;
	init_data(data, args, front);
	data->width = fill_field(args, cur, data, 0);
	if (data->width == -1)
	{
		data->width = va_arg(list, int);
		fill_neg_flgs(data, data->width, 0);
		data->width = ft_abs(data->width);
	}
	data->precision = fill_field(args, cur, data, 1);
	if (data->precision == -1)
	{
		data->precision = va_arg(list, int);
		fill_neg_flgs(data, data->precision, 1);
	}
	if (data->precision == -2 && !is_terminator(args[*cur]) && \
		(args[*cur] != '.' || (args[*cur] == '.' && args[*cur + 1] == '.')))
	{
		free(data);
		return (-1);
	}
	return (1);
}

void	fill_neg_flgs(t_dataset *data, int val, int is_prec)
{
	if (!is_prec && val < 0)
		data->flg |= MIN_FLG + MIN_FIELD;
	if (is_prec)
	{
		if (val > 0 && data->flg & MIN_FIELD)
			data->flg &= ~MIN_FIELD;
		if (val < 0)
			data->flg |= MIN_FLG + MIN_FIELD;
		if (val != 0)
			data->flg &= ~ZERO_PREC;
	}
	return ;
}

void	init_data(t_dataset *data, const char *args, int front)
{
	data->flg = fill_flg(args, front);
	data->prefix = 0;
	data->datatype = 0;
	data->width = 0;
	data->precision = 0;
}
