/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smart_split_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:57:03 by mmuhamad          #+#    #+#             */
/*   Updated: 2023/03/24 12:33:47 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_dollar(char *str)
{
	int	i;
	int	have_dollar;

	i = -1;
	have_dollar = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			return (1);
	}
	return (0);
}

char	*remove_dollar(char *str, t_shell *info)
{
	int		i;
	int		j;
	char	*new;
	char	**tmp;

	i = -1;
	j = 0;
	tmp = ft_split(str, 32);
	while (tmp[++i])
	{
		if (tmp[i][0] == '$')
		{
			while (info->ms_env[j] && ft_strncmp(tmp[i] + 1, info->ms_env[j], ft_strlen(tmp[i] + 1)))
				j++;
			free(tmp[i]);
			tmp[i] = ft_strdup(ft_strchr(info->ms_env[j], '=') + 1);
		}	
	}
	new = ft_2d_strjoin(i, tmp, " ");
	ft_free2d(tmp);
	free(str);
	return (new);
}

char	*filter_dollar(char *str, t_shell *info)
{
	int	i;

	i = 0;
	if (!ft_strncmp("echo", &str[i], 4))
		return (str);
	if (have_dollar(str))
		return (remove_dollar(str, info));
	return (str);
}

// int	get_quote_number(char *str)
// {
// 	int	i;
// 	int flag;

// 	i = -1;
// 	flag = 0;
// 	while (str[++i])
// 	{
// 		if (str[i] == 34)
// 			flag++;
// 		if (str[i] == 39)
// 			flag++;
// 	}
// 	return (flag);
// }