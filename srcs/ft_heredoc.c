/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 00:19:30 by suchua            #+#    #+#             */
/*   Updated: 2023/04/18 02:02:08 by suchua           ###   ########.fr       */
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

static void read_input(int h_fd, char *limiter, int pipe_flag)
{
	char	*input;

	while (1)
	{
		if (pipe_flag)
			ft_putstr_fd("pipe ", 1);
		ft_putstr_fd("heredoc> ", 1);
		input = get_next_line(0);
		if (*input != '\n' && !ft_strncmp(input, limiter, ft_strlen(input) - 1))
		{
			free(input);
			break ;
		}
		if (input)
		{
			ft_putstr_fd(input, h_fd);
			free(input);
		}
	}
	close(h_fd);
}

void	heredoc(char *limiter, t_shell *info, t_cmdlst *next)
{
	int	h_fd;
	int	pipe_flag;

	pipe_flag = 0;
	h_fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (next && !ft_strncmp(next->cmd, "|", 2))
		pipe_flag = 1;
	read_input(h_fd, limiter, pipe_flag);
	redirlst_addback(&info->infile, ".heredoc_tmp", open(".heredoc_tmp", O_RDONLY));
	free(limiter);
}
