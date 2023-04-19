/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:03:14 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 23:18:43 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_exec(t_shell *info, t_cmdlst *node)
{
	char	**s_cmd;
	int		flag;

	if (node->next && !ft_strncmp(node->next->cmd, "|", 2))
		return (0);
	flag = 1;
	s_cmd = ft_split(node->cmd, 32);
	if (!ft_strncmp("cd", s_cmd[0], 3))
		ft_cd(s_cmd, info);
	else if (!ft_strncmp("export", s_cmd[0], 7))
		ft_export(s_cmd, info);
	else if (!ft_strncmp("unset", s_cmd[0], 6))
		ft_unset(s_cmd, info);
	else if (!ft_strncmp("exit", s_cmd[0], 5))
		exit(EXIT_SUCCESS);
	else
		flag = 0;
	ft_free2d(s_cmd);
	return (flag);
}

int	is_builtin(char **s_cmd, t_shell *info)
{
	if (!ft_strncmp("echo", s_cmd[0], 5))
		ft_echo(s_cmd, info);
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
