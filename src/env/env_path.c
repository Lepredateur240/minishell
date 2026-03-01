/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:53:28 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/25 10:41:14 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_exec_path(t_minishell *minishell)
{
	char	*path;
	char	**path_tab;

	path = get_env_value(minishell, "PATH");
	if (!path)
		return (NULL);
	path_tab = ft_split(path, ':');
	if (!path_tab)
		return (NULL);
	free(path);
	return (path_tab);
}
