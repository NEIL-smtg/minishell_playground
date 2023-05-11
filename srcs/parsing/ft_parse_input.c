/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:29:44 by suchua            #+#    #+#             */
/*   Updated: 2023/05/11 20:21:32 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	char	*new;
	int		i;
	int		j;
}	t_vars;

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
static void	overwrite_with_env_value(t_shell *info, char *cmd,
									t_vars *vars)
{
	char	*res;
	int		k;
	char	*needle;
	char	*tmp;

	k = vars->i + 1;
	while (cmd[k] && ft_isalpha(cmd[k]))
		++k;
	if (k == vars->i + 1 && cmd[k] == '?')
		k++;
	needle = ft_substr(cmd, vars->i + 1, k - vars->i - 1);
	res = search_result(info, needle);
	if (!res)
		res = ft_calloc(ft_strlen(cmd) - k + 1, sizeof(char));
	tmp = ft_strjoin(vars->new, res);
	tmp = gnl_strjoin(tmp, &cmd[k]);
	vars->j += ft_strlen(res);
	vars->i += ft_strlen(needle);
	memset(&tmp[vars->j], 0, ft_strlen(&tmp[vars->j]));
	free(res);
	free(vars->new);
	free(needle);
	vars->new = tmp;
}

static void	generate_new_input(t_shell *info, t_cmdlst **node, int quote)
{
	t_vars	vars;

	vars.new = ft_calloc(ft_strlen((*node)->cmd), sizeof(char));
	vars.i = -1;
	vars.j = 0;
	while ((*node)->cmd[++(vars.i)])
	{
		if (quote == -1 && ((*node)->cmd[vars.i] == 34
				|| (*node)->cmd[vars.i] == 39))
			quote = (*node)->cmd[vars.i];
		else if (quote == (*node)->cmd[vars.i])
			quote = -1;
		else if ((quote == -1 || quote == 34) && (*node)->cmd[vars.i] == '$')
			overwrite_with_env_value(info, (*node)->cmd, &vars);
		else
			vars.new[(vars.j)++] = (*node)->cmd[vars.i];
	}
	free((*node)->cmd);
	(*node)->cmd = vars.new;
}

void	no_quote_parsing(t_shell *info, t_cmdlst **node)
{
	t_vars	vars;

	if (!ft_strchr((*node)->cmd, '$'))
		return ;
	vars.i = -1;
	vars.j = 0;
	vars.new = ft_calloc(ft_strlen((*node)->cmd), sizeof(char));
	while ((*node)->cmd[++(vars.i)])
	{
		if ((*node)->cmd[vars.i] == '$')
			overwrite_with_env_value(info, (*node)->cmd, &vars);
		else
			vars.new[vars.j++] = (*node)->cmd[vars.i];
	}
	free((*node)->cmd);
	(*node)->cmd = vars.new;
}

void	ft_parse_input(t_shell *info, t_cmdlst **node)
{
	if (ft_strchr((*node)->cmd, 34) || ft_strchr((*node)->cmd, 39))
		generate_new_input(info, node, -1);
	else
		no_quote_parsing(info, node);
}
