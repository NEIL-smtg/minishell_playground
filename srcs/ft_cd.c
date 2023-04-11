/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:59:57 by suchua            #+#    #+#             */
/*   Updated: 2023/04/12 01:42:36 by suchua           ###   ########.fr       */
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

void	ft_cd(t_shell *info, char **cmd)
{
	int		i;
	char	new_pwd[4096];

	if (info->input_size != 1)
		exit(EXIT_SUCCESS);
	if (chdir(cmd[1]) == -1)
	{
		perror(cmd[1]);
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
}
