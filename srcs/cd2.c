/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:54:06 by vintran           #+#    #+#             */
/*   Updated: 2021/12/27 18:55:32 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_pwd_env(void)
{
	t_dlist	*tmp;

	tmp = g_vars.env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, "PWD=", 4))
			return (ft_strdup(strchr(tmp->data, '=') + 1));
		tmp = tmp->next;
	}
	tmp = NULL;
	push_back(&tmp, ft_strdup("unset"));
	push_back(&tmp, ft_strdup("OLDPWD"));
	unset(tmp);
	lst_clear(&tmp, &free);
	return (NULL);
}
