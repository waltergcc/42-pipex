/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:34:31 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/03/19 00:12:32 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long int	l;

	l = n;
	if (l < 0)
	{
		ft_putchar('-');
		l *= -1;
	}
	if (l > 9)
		ft_putnbr(l / 10);
	ft_putchar(l % 10 + '0');
}
