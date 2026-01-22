/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:06:35 by radandri          #+#    #+#             */
/*   Updated: 2026/01/19 03:25:00 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../environment/env.h"
# include "../parser/ast.h"

/*
** search relative path in env PATH variable
** return full path if found, else return nullptr
** Example:
** For command "ls" and PATH="/usr/bin:/bin:/usr/local/bin"
** find_path("ls") -> "/bin/ls"
*/
char		*find_path(char *cmd, t_env *env);

/*
** return exit status of the command executed
*/
int			execute_ast(t_ast *root, t_env **env);

void		restore_stdio(int saved_in, int saved_out);

int			execute_command(t_ast *node, t_env **env);

void		reset_child_signals(void);

char		*get_cmd_path(char *cmd, t_env *env);

void		apply_prefix_env(t_env **env, char **prefix_env);

void		exec_child(char **cmd_args, char *path, t_env **env);

int			execute_forked_command(t_ast *node, t_env **env);

int			is_builtin(char *cmd);

int			execute_builtin(t_ast *node, t_env **env);

int			write_heredoc_content(int fd, char *delimiter);

typedef struct s_pipe_params
{
	t_ast	*node;
	t_env	**env;
	int		pipe_fd;
	int		target_fd;
}			t_pipe_params;

void		spawn_pipe_child(pid_t *pid, t_pipe_params *p);
int			wait_pipe_children(pid_t left_pid, pid_t right_pid);

#endif
