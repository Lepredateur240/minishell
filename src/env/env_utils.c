/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:11:35 by algasnie          #+#    #+#             */
/*   Updated: 2026/02/25 15:08:31 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_minishell *minishell, char *key)
{
	t_env	*current;
	t_list	*tmp;
	char	*value;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(minishell->exit_status));
	tmp = minishell->env;
	while (tmp)
	{
		current = (t_env *)tmp->content;
		if (ft_strcmp(current->key, key) == 0)
		{
			value = ft_strdup(current->value);
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
