/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flg_proc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:41:09 by fsugimot          #+#    #+#             */
/*   Updated: 2020/08/27 13:32:08 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		process_w_p(t_dataset *data, char **str)
{
	int	tmp;

	tmp = ft_max(data->precision, ft_max(data->width, ft_strlen(*str)));
	if ((data->width > ft_strlen(*str) || data->precision > ft_strlen(*str)) \
		&& data->datatype)
		*str = extend_str(*str, tmp, data->precision);
	if (data->precision == tmp && data->datatype & 2)
		data->flg |= 16;
	if (!str[0])
		return (-1);
	if ((data->precision < ft_strlen(*str) || data->flg & 32) && \
		(!data->datatype || (str[0][0] == '0' && !str[0][1])))
	{
		tmp = (data->flg & 32 ? 0 : ft_strlen(*str));
		*str = cut_str(*str, data->precision);
		*str = extend_str(*str, tmp, ft_strlen(*str));
	}
	if (!str[0])
		return (-1);
	return (0);
}

int		process_flg(t_dataset *data, char **str)
{
	if (data->flg & MIN_FLG)
		*str = conv_left(*str);
	if (data->flg & SPC_FLG && data->datatype & SIGNED)
		*str = add_prefix(*str, 8, 1);
	if (data->flg & POS_FLG && data->datatype & SIGNED)
		*str = add_prefix(*str, 16, 1);
	if (data->flg & SHA_FLG && data->prefix > 0)
		*str = add_prefix(*str, data->prefix, 1 + ((data->prefix & 2) != 0));
	if (data->flg & ZERO_FLG && data->datatype & NUM)
		*str = fill_zero(*str);
	if (!(*str))
		return (-1);
	return (0);
}

int		process_fmt(t_dataset *data, char *str)
{
	int	tmp;

	tmp = process_w_p(data, &str);
	if (tmp == -1)
	{
		free(data);
		return (-1);
	}
	tmp = process_flg(data, &str);
	if (tmp == -1)
	{
		free(data);
		return (-1);
	}
	tmp = ft_strlen(str);
	super_write(str);
	free(str);
	free(data);
	return (tmp);
}
