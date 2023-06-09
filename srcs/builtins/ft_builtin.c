/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:03:14 by suchua            #+#    #+#             */
/*   Updated: 2023/05/15 16:07:12 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parent_exec_decider(char **s_cmd)
{
	int	flag;

	flag = 0;
	if (!ft_strncmp("cd", s_cmd[0], 3))
		flag = 1;
	else if (!ft_strncmp("export", s_cmd[0], 7))
		flag = 1;
	else if (!ft_strncmp("unset", s_cmd[0], 6))
		flag = 1;
	else if (!ft_strncmp("exit", s_cmd[0], 5))
		flag = 1;
	ft_free2d(s_cmd);
	return (flag);
}

int	parent_exec(t_shell *info, t_cmdlst *node)
{
	char	**s_cmd;
	int		flag;

	if (node->next && !ft_strncmp(node->next->cmd, "|", 2))
		return (0);
	flag = parent_exec_decider(ft_split(node->cmd, 32));
	if (flag)
		ft_parse_input(info, &node);
	s_cmd = ft_split(node->cmd, 32);
	if (!ft_strncmp("cd", s_cmd[0], 3))
		ft_cd(s_cmd, info);
	else if (!ft_strncmp("export", s_cmd[0], 7))
		ft_export(s_cmd, info);
	else if (!ft_strncmp("unset", s_cmd[0], 6))
		ft_unset(s_cmd, info);
	else if (!ft_strncmp("exit", s_cmd[0], 5))
		exit(EXIT_SUCCESS);
	ft_free2d(s_cmd);
	return (flag);
}

int	is_builtin(char **s_cmd, t_shell *info, char *ori_cmd)
{
	if (!ft_strncmp("echo", s_cmd[0], 5))
		ft_echo(s_cmd, ori_cmd, info);
	else if (!ft_strncmp("pwd", s_cmd[0], 4))
		ft_pwd(s_cmd, info);
	else if (!ft_strncmp("cd", s_cmd[0], 3))
		ft_cd(s_cmd, info);
	else if (!ft_strncmp("export", s_cmd[0], 7))
		ft_export(s_cmd, info);
	else if (!ft_strncmp("unset", s_cmd[0], 6))
		ft_unset(s_cmd, info);
	else if (!ft_strncmp("env", s_cmd[0], 4))
		ft_env(s_cmd, info);
	else if (!ft_strncmp("exit", s_cmd[0], 5))
		exit(EXIT_SUCCESS);
	else
		return (0);
	if (!info->ms_status)
		exit(EXIT_SUCCESS);
	exit(127);
	return (1);
}
