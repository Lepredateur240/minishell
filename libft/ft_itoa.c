/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:54:20 by algasnie          #+#    #+#             */
/*   Updated: 2025/10/23 12:33:00 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_int(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_putnbr(char *s, int n, size_t len)
{
	size_t	i;

	s[len] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	else if (n == 0)
		s[0] = '0';
	i = len - 1;
	while (n > 0)
	{
		s[i--] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	len;

	if (n == -2147483648)
	{
		s = ft_strdup("-2147483648");
		return (s);
	}
	len = ft_len_int(n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	ft_putnbr(s, n, len);
	return (s);
}
