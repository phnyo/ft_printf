/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 16:32:13 by fsugimot          #+#    #+#             */
/*   Updated: 2020/10/07 22:19:11 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_max(long long a, long long b)
{
	return (a > b ? a : b);
}

long long	ft_abs(long long nbr)
{
	return (nbr > 0 ? nbr : -nbr);
}

long long	ft_min(long long a, long long b)
{
	return (a > b ? b : a);
}

int			is_num(char c)
{
	return (c <= '9' && c >= '0');
}
