/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flg_proc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:38:07 by fsugimot          #+#    #+#             */
/*   Updated: 2020/08/26 16:59:14 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*conv_left(char *str)
{
	int size;
	int ind;
	int rear;

	ind = 0;
	rear = 0;
	size = ft_strlen(str);
	while (str[rear] == ' ' && str[rear])
		rear++;
	while (ind < size - rear)
	{
		str[ind] = str[ind + rear];
		ind++;
	}
	while (ind < size)
	{
		str[ind] = ' ';
		ind++;
	}
	return (str);
}

char	*fill_zero(char *str)
{
	int ind;

	ind = 0;
	while (str[ind] == ' ')
	{
		str[ind] = '0';
		ind++;
	}
	return (str);
}

char	*add_prefix(char *str, int flg, int len)
{
	int ind;

	ind = 0;
	if (!str)
		return (0);
	while (str[ind] == ' ')
		ind++;
	if (ind < len)
		str = extend_str(str, ft_strlen(str) + (len - ind), ft_strlen(str));
	ind = (ind < len ? 0 : ind - len);
	if (!str)
		return (str);
	if (flg & 1)
		str[ind] = 'o';
	if (flg & 2)
	{
		str[ind] = '0';
		str[ind + 1] = 'X' + (((flg & 4) > 0) << 5);
	}
	if (flg & 8)
		str[ind] = ' ';
	if (flg & 16)
		str[ind] = '+';
	return (str);
}
