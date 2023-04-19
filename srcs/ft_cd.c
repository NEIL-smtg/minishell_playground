/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:25:40 by suchua            #+#    #+#             */
/*   Updated: 2023/04/19 22:34:51 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_oldpwd(char *new, t_shell *info)
{
	int	i;

	i = 0;
	while (ft_strncmp("OLDPWD=", info->ms_env[i], 7))
		++i;
	free(info->ms_env[i]);
	info->ms_env[i] = ft_strdup("OLDPWD=");
	info->ms_env[i] = gnl_strjoin(info->ms_env[i], new);
}

void	ft_cd(char **s_cmd, t_shell *info)
{
	char	new_pwd[4096];
	int		i;

	if (get_2d_arr_size(s_cmd) != 2)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(s_cmd[1], 2);
		info->ms_status = 1;
		return ;
	}
	if (chdir(s_cmd[1]) == -1)
	{
		info->ms_status = 1;
		perror(s_cmd[1]);
		return ;
	}
	getcwd(new_pwd, sizeof(new_pwd));
	i = 0;
	while (ft_strncmp("PWD=", info->ms_env[i], 4))
		++i;
	set_oldpwd(info->ms_env[i] + 4, info);
	free(info->ms_env[i]);
	info->ms_env[i] = ft_strdup("PWD=");
	info->ms_env[i] = gnl_strjoin(info->ms_env[i], new_pwd);
	info->ms_status = 0;
}
