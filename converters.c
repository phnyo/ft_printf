/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:33:23 by fsugimot          #+#    #+#             */
/*   Updated: 2020/10/09 12:30:15 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	output_ptr(t_dataset *data, unsigned long long int ptr)
{
	int		dig;
	int		ret;
	char	*str;

	dig = count_digit(ptr, (1 << 4));
	str = malloc(dig + 1);
	str[dig] = 0;
	if (!ptr)
		str[0] = '0';
	while (ptr > 0)
	{
		if (ptr % 16 > 9)
			str[dig--] = 'a' + ptr % 16 - 10;
		else
			str[dig--] = '0' + ptr % 16;
		ptr /= 16;
	}
	data->datatype |= NUM;
	data->flg |= PTR_FLG;
	ret = process_fmt(data, str);
	return (ret);
}

int	output_char(t_dataset *data, char c)
{
	int		ret;
	char	*str;

	str = malloc(2);
	if (!str)
		return (-1);
	str[1] = 0;
	str[0] = c;
	data->datatype |= NUM;
	ret = process_fmt(data, str);
	return (ret);
}

int	output_num(t_dataset *data, int nbr)
{
	int		ret;
	char	*str;

	data->datatype |= SIGNED + NUM;
	if (data->flg & ZERO_PREC && !nbr)
	{
		str = ft_strdup("");
		data->flg &= ~ZERO_FLG;
	}
	else
		str = num_to_str(nbr);
	if (!str)
		return (-1);
	ret = process_fmt(data, str);
	return (ret);
}

int	output_unum(t_dataset *data, unsigned int nbr, int is_hex, int is_oct)
{
	int		ret;
	char	*str;

	if (!data->precision && !nbr)
		str = ft_strdup("");
	else
		str = u_num_to_str(nbr, is_hex, is_oct);
	if (!str)
		return (-1);
	data->prefix |= ((is_hex & 2) << 1);
	data->prefix |= ((is_hex & 1) << 1);
	data->prefix |= is_oct;
	data->datatype |= NUM;
	ret = process_fmt(data, str);
	return (ret);
}

int	output_str(t_dataset *data, const char *content)
{
	int		ret;
	char	*str;

	if (data->flg & ZERO_FLG)
		data->flg &= ~ZERO_FLG;
	if (!content)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(content);
	data->datatype = 0;
	if (!str)
		return (-1);
	ret = process_fmt(data, str);
	return (ret);
}
