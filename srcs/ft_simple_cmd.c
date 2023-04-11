/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:36:55 by suchua            #+#    #+#             */
/*   Updated: 2023/03/16 21:08:38 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_shell *info)
{
	char	pwd[4096];

	getcwd(pwd, sizeof(pwd));
	ft_putendl_fd(pwd, 1);
	info->ms_status = 0;
}

void	ft_env(t_shell *info)
{
	int	i;

	i = -1;
	while (info->ms_env[++i])
		ft_putendl_fd(info->ms_env[i], 1);
	info->ms_status = 0;
}

char	**remove_var_from_env(int j, char **env)
{
	int		row;
	char	**new;
	int		i;
	int		flag;

	row = 0;
	flag = 0;
	while (env[row])
		++row;
	new = malloc(sizeof(char *) * (row - 1));
	i = -1;
	while (env[++i])
	{
		if (i == j)
		{
			flag = 1;
			continue ;
		}
		new[i - flag] = ft_strdup(env[i]);
	}
	new[i - flag] = 0;
	return (new);
}

void	ft_unset(t_shell *info, char **cmd)
{
	int		i;
	char	**new_env;

	if (info->input_size != 1)
		exit(EXIT_SUCCESS);
	i = 0;
	while (info->ms_env[i]
		&& ft_strncmp(cmd[1], info->ms_env[i], ft_strlen(cmd[1])))
		++i;
	if (!info->ms_env[i])
		return ;
	new_env = remove_var_from_env(i, info->ms_env);
	ft_free2d(info->ms_env);
	info->ms_env = new_env;
	info->ms_status = 0;
}
