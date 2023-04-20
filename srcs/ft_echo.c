/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:12:19 by suchua            #+#    #+#             */
/*   Updated: 2023/04/20 19:36:30 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_echo_strs(char *cmd)
{
	int		i;
	char	**s_cmd;
	char	*tmp;

	i = 0;
	while (cmd[i] && !ft_isspace(cmd[i]))
		++i;
	while (cmd[i] && ft_isspace(cmd[i]))
		++i;
	if (!ft_strncmp(&cmd[i], "-n", 2))
		while (cmd[i] && !ft_isspace(cmd[i]))
			++i;
	tmp = ft_strdup("\"");
	tmp = gnl_strioin(tmp, &cmd[i]);
	tmp = gnl_strioin(tmp, "\"");
	s_cmd = interesting_split(tmp, 0, 0, 0);
	free(tmp);
	return (s_cmd);
}

void	ft_echo(char **split, char *cmd, t_shell *info)
{
	int		flag;
	int		i;
	char	**s_cmd;

	flag = 0;
	if (!ft_strncmp(split[1], "-n", 3))
		flag = 1;
	s_cmd = get_echo_strs(cmd);
	i = -1;
	while (s_cmd[++i])
	{
		ft_putstr_fd(s_cmd[i], 1);
		ft_putchar_fd(32, 1);
	}
	if (flag)
		ft_putstr_fd("%", 1);
	ft_putchar_fd('\n', 1);
	info->ms_status = 0;
	ft_free2d(s_cmd);
}
