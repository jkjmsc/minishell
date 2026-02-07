/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radandri <radandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 20:21:21 by radandri          #+#    #+#             */
/*   Updated: 2026/01/11 03:01:48 by radandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../lib/libft/libft.h"
# include "../minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}					t_env;

t_env				*env_init(char **envp);

/*
**   Return the value for a given key in the env list.
**   Returns NULL if the key is not found.
**
** Example:
**   const char *home = env_get(env, "HOME");
**   if (home == NULL) { handle missing HOME }
*/
char				*env_get(t_env *env, const char *key);

/*
**   Create or update an environment variable in the list.
**   Returns 0 on success, -1 on allocation failure.
**
** Example:
**   if (env_set(&env, "PATH", "/usr/bin") != 0)
**       { handle allocation error }
*/
int					env_set(t_env **env, const char *key, const char *value);

/*
**   Ensure SHLVL follows shell rules and update it.
**   Rules:
**   - Missing -> set to "1".
**   - Non-numeric -> set to "1".
**   - Negative -> set to "0".
**   - >= 1000 -> warn and set to "1".
**   - Else -> increment by 1.
**
** Example:
**   // SHLVL=2 becomes 3 after update
**   if (env_update_shlvl(&env) != 0) { handle update error }
*/
int					env_update_shlvl(t_env **env);
int					is_number(const char *s);
t_env				*env_remove(t_env *env, const char *key);
char				**env_to_array(t_env *env);
void				env_free(t_env *env);
#endif