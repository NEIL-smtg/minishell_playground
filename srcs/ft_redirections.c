/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:54:41 by suchua            #+#    #+#             */
/*   Updated: 2023/03/21 16:58:51 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *cmd)
{
	if (!ft_strncmp(">", cmd, 2))
		return (R1);
	if (!ft_strncmp(">>", cmd, 3))
		return (R2);
	if (!ft_strncmp("<", cmd, 2))
		return (L1);
	if (!ft_strncmp("<<", cmd, 3))
		return (L2);
	return (0);
}

void	read_input(int fd, char *LIMITER)
{
	char	*input;

	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		input = get_next_line(0);
		if (*input != '\n' && !ft_strncmp(input, LIMITER, ft_strlen(input) - 1))
		{
			free(input);
			break ;
		}
		if (input)
		{
			ft_putstr_fd(input, fd);
			free(input);
		}
	}
	close(fd);
}

void	open_file(t_shell *info, char *file, int type)
{
	if (type == 0)
		return ;
	if (!file && type != L2)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	if (type == R1)
		info->outfile = open(file, O_RDWR | O_TRUNC | O_CREAT, 0000644);
	if (type == R2)
		info->outfile = open(file, O_RDWR | O_APPEND | O_CREAT, 0000644);
	if (type == L1)
		info->infile = open(file, O_RDONLY);
	if (type == L2)
	{
		info->infile = open(".heredoc_tmp",
				O_CREAT | O_WRONLY | O_TRUNC, 0000644);
		read_input(info->infile, file);
		info->infile = open(".heredoc_tmp", O_RDONLY);
	}
}

void	set_infile_outfile(t_shell *info, char *cmd)
{
	char	**tmp;
	int		i;
	int		ret;

	tmp = ft_split(cmd, 32);
	i = -1;
	while (tmp[++i])
	{
		ret = is_redir(tmp[i]);
		if (ret == R1)
		{
			open_file(info, tmp[i + 1], R1);
			info->outfile_name = ft_strdup(tmp[i + 1]);
		}
		else if (ret == R2)
		{
			open_file(info, tmp[i + 1], R2);
			info->outfile_name = ft_strdup(tmp[i + 1]);
		}
		else if (ret == L1)
			open_file(info, tmp[i + 1], L1);
		else if (ret == L2)
			open_file(info, tmp[i + 1], L2);
	}
	ft_free2d(tmp);
}
