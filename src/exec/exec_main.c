/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:16:41 by masenche          #+#    #+#             */
/*   Updated: 2026/03/01 18:18:41 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(t_cmd *cmd, t_minishell *minishell)
{
	pid_t pid;
	int   status;

	// 1. Création du processus enfant
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0) // Processus ENFANT
	{
		// 2. Remplacer l'enfant par le nouveau programme
		// cmd->cmd_path a été trouvé via find_path() dans ton code
		if (execve(cmd->cmd_path, cmd->args, envp) == -1)
		{
			perror("minishell");
			exit(127); // Code standard si la commande échoue
		}
	}
	else // Processus PARENT
	{
		// 3. Attendre que l'enfant se termine
		waitpid(pid, &status, 0);
		
		// 4. Récupérer le code de sortie pour $?
		if (WIFEXITED(status))
			minishell->exit_status = WEXITSTATUS(status);
	}
}