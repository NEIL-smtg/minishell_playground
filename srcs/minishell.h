/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:22:17 by suchua            #+#    #+#             */
/*   Updated: 2023/04/13 02:17:59 by suchua           ###   ########.fr       */
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

# define R1 1
# define R2 2
# define L1 3
# define L2 4
# define FREE_PIPE 1
# define PRINT 1

# define DOUBLE_PIPE 1
# define DOUBLE_N    2
# define PIPE        3
# define NORMAL      4

typedef	struct s_term_setting
{
	struct termios	original_setting;
}	t_term;

//to store the files in wildcard
typedef struct s_files
{
	char			*file;
	struct s_files	*next;
}	t_files;

//to check if number of files before and after wildcard is the same
//if its the same, meaning no file is found is that directory, hence perror
typedef struct s_file_num
{
	int	before;
	int	after;
}	t_files_num;

//retation = relation of prev cmd and nxt cmd
//open_brac = indicates bracket starts
//close_brac = indicates bracket closed
//no brac = cmd isnt within bracket
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

//main data struct
typedef struct s_shell
{
	char		*ms_prompt;
	char		**ms_env;
	char		*input_line;
	int			ms_status;
	int			**fd;
	int			infile;
	int			outfile;
	int			input_size;
	char		*outfile_name;
	t_term		term;
	t_cmdlst	*cmdlst;
}	t_shell;

//check dangling
int		ft_dangling(char *str, int print);
int		dangling_dquote(char *str);
int		dangling_squote(char *str);
int		dangling_bracket(char *str);
int		dangling_pipe(char *str);

//signal
void	init_signal(void);

//built-in cmd
void	ft_pwd(t_shell *info);
void	ft_export(t_shell *info, char **cmd);
void	ft_env(t_shell *info);
void	ft_echo(t_shell *info, char **cmd);
void	ft_unset(t_shell *info, char **cmd);
void	ft_cd(t_shell *info, char **cmd);

//redirection
void	set_infile_outfile(t_shell *info, char *cmd);
int		is_redir(char *cmd);

//execve
void	ft_handle_cmd(t_shell *info);
int		exec_now(t_shell *info, char **cmd);
void	set_dup(t_shell *info, char *nxt_cmd, int index);
void	set_no_pipe_dup(t_shell *info);

//execve utils
void	close_all_pipe(t_shell *info, int n_pipe, int type);
void	init_pipe_fd(t_shell *info);
char	*get_cmd_path(char *cmd);
void	wait_child(char **s_cmd, t_shell *info);
int		is_builtin_cmd(char **cmd, t_shell *info);

//wildcard
int		check_wild_card(char ***cmd);
char	*write_files_to_str(char *cmd, t_files **files);
int		wild_card_exists(char *cmd);
void	get_the_files(t_files **lst, char *type);
int		is_file_type(char *file, char *type);
char	*wildcard_error(char *str, t_files **files);

//utils
void	msg_cmd_not_found(char **cmd);
void	free_everything(t_shell *info);
void	swap_str(char **s1, char **s2);
void	ft_free_files_lst(t_files **lst);
int		get_files_num(t_files *files);
t_files	*get_last_files(t_files *files);

//cmdlst
void	interpret_cmd(char *cmd, t_cmdlst **lst);
void	ft_cmdexec(t_shell *info);

//cmdlst utils
void	ft_free_cmdlst(t_cmdlst **lst);
void	print_lst(t_cmdlst *lst);
void	ft_cmdlst_addback(t_cmdlst	**lst, char *s);
int		to_split(char *s);
char	**interesting_split(char *cmd, int depth);
int		cmdlst_is_double(char *s, char *bonus);


//smart split for pipe
char	**ft_smart_split(char *str, t_shell *info);
char	**remove_space_quote(char **str, t_shell *info);
char	*filter_dollar(char *str, t_shell *info);

#endif