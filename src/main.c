/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:44:39 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/01 17:14:32 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char *argv[], char **envp)
{
	char		*line_read;
	t_minishell	minishell;

	////////////////////////
	(void)argc;
	(void)argv;
	////////////////////////

	////////// init signal ///////////////////
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);

	////////// init strcut minishell ///////////////////
	minishell.exit_status = 0;
	minishell.env = init_env(envp);
	minishell.exec_path_tab = get_exec_path(&minishell);
	minishell.cmds = NULL;
	////////// init strcut minishell ///////////////////
	
	///test environnement///
	//test_print_env(minishell.env);
	// test_print_env_value(minishell.env, "PATH");
	// test_print_exec_path_tab(minishell.exec_path_tab);
	/////////
	
	while (1)
	{
		line_read = readline("minishell> ");
		// line_read = "test < r_input | test > r_output | test >> r_output_append | test << here_doc_limiter | $exp | cmd arg1 arg2 arg3";
		if (g_receive_message == 1)
		{
			//mettre minishell.exit.status = 130
			g_receive_message = 0;
			
		}
		if (!line_read)
		{
			printf("exit\n");
			break ;
		}

		if (line_read[0] != '\0')
		{
			add_history(line_read);
			parsing_prompt(&minishell, line_read);
			/////test////
			printf("RETURN: %d\n", minishell.exit_status);
			///////
			
		}

			

		free(line_read);
	}
	if (line_read)
		free(line_read);
	free_all(&minishell);
	
}

