/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:19:30 by suchua            #+#    #+#             */
/*   Updated: 2023/05/05 19:57:24 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_limiter(char *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i] && ft_isspace(cmd[i]))
		++i;
	j = 0;
	while (cmd[i + j] && !ft_isspace(cmd[i + j]))
		++j;
	return (ft_substr(cmd, i, j));
}

static void	read_input(int h_fd, char *limiter, int pipe_flag)
{
	char	*input;
	char	*prompt;

	if (pipe_flag)
		prompt = ft_strdup("pipe heredoc> ");
	else
		prompt = ft_strdup("heredoc> ");
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		if (!ft_strncmp(input, limiter, ft_strlen(input) - 1))
		{
			free(input);
			break ;
		}
		ft_putendl_fd(input, h_fd);
		free(input);
	}
	free(prompt);
	close(h_fd);
}

void	heredoc(char *limiter, t_shell *info, t_cmdlst *next)
{
	int	pipe_flag;

	pipe_flag = 0;
	if (pipe(info->heredoc_fd) == -1)
		return ;
	if (next && !ft_strncmp(next->cmd, "|", 2))
		pipe_flag = 1;
	read_input(info->heredoc_fd[1], limiter, pipe_flag);
	redirlst_addback(&info->infile, ".heredoc_tmp",
		info->heredoc_fd[0]);
	free(limiter);
}
