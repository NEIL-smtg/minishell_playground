/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:45:38 by suchua            #+#    #+#             */
/*   Updated: 2023/05/15 18:45:56 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_shell *info, char **env)
{
	char			*user;
	char			*ms;
	struct termios	term;

	user = getenv("USER");
	ms = "@minishell->";
	info->ms_prompt = ft_strjoin(user, ms);
	info->ms_env = ft_2d_strdup(env);
	info->ms_status = 0;
	info->cmdlst = NULL;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	info->open_error = 0;
	info->wildcard_error = 0;
}

void	get_input(t_shell *info)
{
	while (1)
	{
		init_signal();
		info->input_line = readline(info->ms_prompt);
		if (!info->input_line)
			break ;
		if (!(*info->input_line) || !ft_dangling(info->input_line, PRINT)
			|| !dangling_pipe(info->input_line))
		{
			free(info->input_line);
			continue ;
		}
		add_history(info->input_line);
		interpret_cmd(info->input_line, &info->cmdlst);
		ft_parse_wildcard(info);
		if (info->wildcard_error == -1)
			continue ;
		ft_cmdexec(info);
		ft_free_cmdlst(&info->cmdlst);
		free(info->input_line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	info;

	init(&info, env);
	get_input(&info);
	(void) ac;
	(void) av;
	exit(EXIT_SUCCESS);
}
