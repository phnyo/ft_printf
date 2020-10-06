/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:45:13 by fsugimot          #+#    #+#             */
/*   Updated: 2020/08/27 09:42:15 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		count_digit(unsigned long long int num, int div)
{
	int	dig;

	dig = 0;
	while (num > 0)
	{
		num /= div;
		++dig; 
	}
	return (dig);
}

char	*num_to_str(int num)
{
	int		dig; 
	char	*ret;

	dig = count_digit(num, 10);
	dig += (num <= 0);
	ret = malloc(dig + 1);
	if (!ret)
		return (ret);
	ret[dig--] = 0;
	if (num < 0)
		ret[0] = '-';
	if (!num)
		ret[0] = '0';
	while (ft_abs(num) > 0)
	{
		ret[dig--] = '0' + ft_abs(num % 10);
		num /= 10; 
	}
	return (ret);
}

char	*u_num_to_str(unsigned int num, int is_hex, int is_oct)
{
	int		div;
	int		dig;
	int		is_cap;
	char	*ret;

	div = is_hex & 1 ? (1 << 4) : 10;
	div = is_oct ? 8 : div;
	is_cap = (is_hex & 2 << 5); 
	dig = count_digit(num, div);
	ret = malloc(dig + 1);
	if (!ret)
		return (ret);
	ret[dig--] = 0;
	if (!num)
		ret[0] = '0';
	while (num > 0)
	{
		if (num % div > 9)
			ret[dig--] = ('A' ^ is_cap) + num % div - 10;
		else
			ret[dig--] = '0' + num % div;
		num /= div; 
	}
	return (ret);
}
