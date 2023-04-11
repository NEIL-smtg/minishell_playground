/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:55:41 by suchua            #+#    #+#             */
/*   Updated: 2023/04/11 23:15:37 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**grep_cmd(char **cmd)
{
	int		i;
	char	**new;

	i = -1;
	while (cmd[++i])
		if (is_redir(cmd[i]))
			break ;
	if (cmd[i] == 0)
		return (NULL);
	if (i == 0)
		new = ft_2d_strdup(&cmd[i + 2]);
	else
		new = ft_2d_strndup(cmd, i);
	return (new);
}

static void	child_exec(char **cmd, t_shell *info, int npipe)
{
	char	**redir_cmd;

	redir_cmd = grep_cmd(cmd);
	if (redir_cmd)
	{
		ft_free2d(cmd);
		cmd = redir_cmd;
	}
	if (npipe == 0)
		set_no_pipe_dup(info);
	if (is_builtin_cmd(cmd, info))
		exit(EXIT_SUCCESS);
	execve(get_cmd_path(cmd[0]), cmd, info->ms_env);
	exit(EXIT_FAILURE);
}

void	parent_process(t_shell *info, int n_pipe, int i)
{
	if (n_pipe > 0 && info->outfile != -1)
	{
		close(info->fd[i][0]);
		info->fd[i][0] = open(info->outfile_name, O_RDONLY);
		free(info->outfile_name);
	}
	close(info->infile);
	close(info->outfile);
	info->infile = -1;
	info->outfile = -1;
	if (n_pipe > 0 && i < n_pipe)
		close(info->fd[i][1]);
}

void	iterate_pipe(t_shell *info, int n_pipe, char **s_cmd)
{
	int		i;
	pid_t	id;

	i = -1;
	while (s_cmd[++i])
	{
		set_infile_outfile(info, s_cmd[i]);
		id = fork();
		if (id == 0 && n_pipe > 0)
		{
			set_dup(info, s_cmd[i + 1], i);
			close_all_pipe(info, n_pipe, 0);
		}
		if (id == 0)
			child_exec(ft_split(s_cmd[i], 32), info, n_pipe);
		else
			parent_process(info, n_pipe, i);
	}
}

void	ft_handle_cmd(t_shell *info)
{
	char	**s_cmd;

	// s_cmd = ft_split(info->input_line, '|');
	// s_cmd = ft_smart_split(info->input_line, info);
	info->input_size = get_2d_arr_size(s_cmd);
	if (check_wild_card(&s_cmd) == -1 || exec_now(info, s_cmd))
	{
		ft_free2d(s_cmd);
		return ;
	}
	init_pipe_fd(info);
	iterate_pipe(info, info->input_size - 1, s_cmd);
	close_all_pipe(info, info->input_size - 1, FREE_PIPE);
	wait_child(s_cmd, info);
	ft_free2d(s_cmd);
}
