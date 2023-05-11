/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhamad <mmuhamad@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:29:44 by suchua            #+#    #+#             */
/*   Updated: 2023/05/11 14:30:29 by mmuhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_result(t_shell *info, char *needle)
{
	int		i;
	int		len;

	if (!ft_strncmp("?", needle, 1))
		return (ft_itoa(info->ms_status / 256));
	i = -1;
	while (info->ms_env[++i])
	{
		len = 0;
		while (info->ms_env[i][len] != '=')
			++len;
		if (len > (int) ft_strlen(needle))
			continue ;
		if (!ft_strncmp(info->ms_env[i], needle, ft_strlen(needle)))
			return (ft_strdup(info->ms_env[i] + ft_strlen(needle) + 1));
	}
	return (NULL);
}

//	i = input index, j = new index
static void	overwrite_with_env_value(char **new, t_shell *info, t_cmdlst **node, int *i, int *j)
{
	char	*res;
	int		k;
	char	*needle;
	char	*tmp;

	k = *i + 1;
	while ((*node)->cmd[k] && ft_isalpha((*node)->cmd[k]))
		++k;
	needle = ft_substr((*node)->cmd, *i + 1, k - *i - 1);
	res = search_result(info, needle);
	if (!res)
		res = ft_substr((*node)->cmd, *i, k);
	tmp = ft_strjoin(*new, res);
	tmp = gnl_strjoin(tmp, &(*node)->cmd[k]);
	*j += ft_strlen(res);
	*i += ft_strlen(needle);
	ft_memset(&tmp[*j], 0, ft_strlen(&tmp[*j]));
	free(res);
	free(*new);
	free(needle);
	*new = tmp;
}

static void	generate_new_input(t_shell *info, t_cmdlst **node)
{
	int		i;
	int		j;
	char	*new;
	int		quote;

	new = ft_calloc(ft_strlen((*node)->cmd), sizeof(char));
	i = -1;
	j = 0;
	quote = -1;
	while ((*node)->cmd[++i])
	{
		if (quote == -1 && ((*node)->cmd[i] == 34
				|| (*node)->cmd[i] == 39))
			quote = (*node)->cmd[i];
		else if (quote == (*node)->cmd[i])
			quote = -1;
		else if ((quote == -1 || quote == 34) && (*node)->cmd[i] == '$')
			overwrite_with_env_value(&new, info, node, &i, &j);
		else
			new[j++] = (*node)->cmd[i];
	}
	free((*node)->cmd);
	(*node)->cmd = new;
}

void	no_quote_parsing(t_shell *info, t_cmdlst **node)
{
	int		i;
	int		j;
	char	*new;

	if (!ft_strchr((*node)->cmd, '$'))
		return ;
	i = -1;
	j = 0;
	new = ft_calloc(ft_strlen((*node)->cmd), sizeof(char));
	while ((*node)->cmd[++i])
	{
		if ((*node)->cmd[i] == '$')
			overwrite_with_env_value(&new, info, node, &i, &j);
		else
			new[j++] = (*node)->cmd[i];
	}
	free((*node)->cmd);
	(*node)->cmd = new;
}

void	ft_parse_input(t_shell *info, t_cmdlst **node)
{
	if (ft_strchr((*node)->cmd, 34) || ft_strchr((*node)->cmd, 39))
	{
		generate_new_input(info, node);
		return ;
	}
	else
		no_quote_parsing(info, node);
}
