/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:33:25 by algasnie          #+#    #+#             */
/*   Updated: 2025/10/23 11:45:14 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*t;

	t = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!t)
		return (NULL);
	ft_strlcpy(t, s, ft_strlen(s) + 1);
	return (t);
}
