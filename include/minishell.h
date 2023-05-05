/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:22:17 by suchua            #+#    #+#             */
/*   Updated: 2023/05/05 21:33:51 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/include/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <errno.h>
# include <signal.h>
# include <string.h>

# define R1 	5
# define R2 	6
# define L1 	7
# define L2		8
# define PRINT	1

//	to store info of files to redirect
typedef struct s_redirlst
{
	int					fd;
	char				*filename;
	struct s_redirlst	*next;
}	t_redirlst;

//	wildcard linked list, store file that found in directory
typedef struct s_files
{
	char				*file;
	struct s_files		*next;
}	t_files;

//	retation	=	relation of prev cmd and nxt cmd
//	open_brac	=	indicates bracket starts
//	close_brac	=	indicates bracket closed
//	no brac		=	cmd isnt within bracket
typedef struct s_cmdlst
{
	char				*cmd;
	int					open_brac;
	int					closed_brac;
	int					within_brac;
	int					relation;
	struct s_cmdlst		*prev;
	struct s_cmdlst		*next;
}	t_cmdlst;

//	shell information
typedef struct s_shell
{
	char				*ms_prompt;
	char				**ms_env;
	char				*input_line;
	int					ms_status;
	int					fd[2];
	int					heredoc_fd[2];
	int					prevfd;
	t_cmdlst			*cmdlst;
	t_redirlst			*infile;
	t_redirlst			*outfile;
}	t_shell;

//	check dangling
int		ft_dangling(char *str, int print);
int		dangling_dquote(char *str);
int		dangling_squote(char *str);
int		dangling_bracket(char *str, int dq, int sq, int echo);
int		dangling_pipe(char *str);
int		dangling_redir(char *str);

//	signal handling
void	init_signal(void);

//	parse input (manage wildcard, env variables)
void	ft_parse_input(t_shell *info);
void	ft_parse_wildcard(t_shell *info);

//	redirection
int		redir_within_quotes(char *cmd);
int		set_redir(t_shell *info, t_cmdlst **node);
void	ft_redir_exec(t_shell *info, t_cmdlst *node);
void	redirect_output(int piping, t_shell *info, char *cmd);
void	shell_output(int piping, t_shell *info, char *cmd);

//	build redirection lst
void	redirlst_addback(t_redirlst **rlst, char *filename, int fd);

//	heredoc
char	*get_limiter(char *cmd);
void	heredoc(char *limiter, t_shell *info, t_cmdlst *next);

//	wildcard
int		is_curr_dir(char *cmd, int i);
char	*get_target(char *cmd, int i);
int		target_found(char *file, char *target);
void	files_addback(t_files **files, char *file, int cmd_type);

//	free stuff
void	free_everything(t_shell *info);
void	ft_free_files_lst(t_files **lst);
void	ft_free_infile_outfile(t_shell *info);

//	cmdlst
void	interpret_cmd(char *cmd, t_cmdlst **lst);
void	ft_cmdexec(t_shell *info);

//	cmdlst utils
void	ft_free_cmdlst(t_cmdlst **lst);
void	print_lst(t_cmdlst *lst);
void	ft_cmdlst_addback(t_cmdlst	**lst, char *s);
int		to_split(char *s);
char	**interesting_split(char *cmd, int depth);
int		cmdlst_is_double(char *s, char *bonus);
int		instr_split(char *s);

//	utils
char	*get_cmd_path(char *cmd);
void	swap_str(char **s1, char **s2);

//	builtins
int		is_builtin(char **s_cmd, t_shell *info, char *ori_cmd);
int		parent_exec(t_shell *info, t_cmdlst *node);
void	ft_echo(char **split, char *cmd, t_shell *info);
void	ft_env(char **s_cmd, t_shell *info);
void	ft_export(char **s_cmd, t_shell *info);
void	ft_pwd(char **s_cmd, t_shell *info);
void	ft_unset(char **s_cmd, t_shell *info);
void	ft_cd(char **s_cmd, t_shell *info);

// prompt error when cmd not found
void	cmd_not_found(t_cmdlst *node);

#endif