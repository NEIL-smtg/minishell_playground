/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:12:19 by suchua            #+#    #+#             */
/*   Updated: 2023/04/22 03:57:22 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo_str(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && !ft_isspace(cmd[i]))
		++i;
	while (cmd[i] && ft_isspace(cmd[i]))
		++i;
	if (!ft_strncmp(&cmd[i], "-n", 2))
		while (cmd[i] && !ft_isspace(cmd[i]))
			++i;
	ft_putstr_fd(&cmd[i], 1);
}

void	ft_echo(char **split, char *cmd, t_shell *info)
{
	int		flag;

	flag = 0;
	if (!ft_strncmp(split[1], "-n", 3))
		flag = 1;
	print_echo_str(cmd);
	if (flag)
		ft_putstr_fd("%", 1);
	ft_putchar_fd('\n', 1);
	info->ms_status = 0;
}
