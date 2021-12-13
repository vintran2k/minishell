/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:37:32 by vintran           #+#    #+#             */
/*   Updated: 2021/12/13 07:41:23 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_in_str(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strndup(char *src, int n)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] && i < n)
		i++;
	dest = malloc(sizeof(*dest) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	add_str_list(t_list **lst, char *line, int len)
{
	char	*data;

	data = ft_strndup(line, len);
	push_back(lst, data);
}

char	*is_in_env(char *s, int dq)
{
	int		i;
	t_list *env;

	i = 0;
	env = g_vars.env;
	while (env && *s)
	{
		if (dq == 1)
		{
			if (ft_strncmp(s, (char *)env->data, ft_strlen(s)) == 0)
				return ((char *)env->data);
		}
		else
		{
			if (ft_strncmp(s, (char *)env->data, ft_strlen(s) - 1) == 0)
				return ((char *)env->data);
		}
		i++;
		env = env->next;
	}
	printf("passage avant tmp\n");
	t_list *tmp = g_vars.env;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->data);
		tmp = tmp->next;
	}
	printf("passage apres tmp\n");
	return (NULL);
}

int	itoa_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nb;

	len = itoa_len(n);
	nb = n;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb)
	{
		str[len] = nb % 10 + '0';
		len--;
		nb /= 10;
	}
	return (str);
}

int		replace_var(t_list **lst, char *env, int dq)
{
	int		i;
	int		j;
	int		len;
	char	*new;
	t_list	*tmp;
	int		err;

	tmp = *lst;
	i = 1;
	while (env && env[i - 1] != '=')
		i++;
	j = 0;
	while (((char *)tmp->data)[j] != '$')
		j++;
	len = 0;
	if (dq == -1)
		len = 1;
	err = ft_strncmp(&((char *)tmp->data)[j], "$?", 2);
	if (err == 0)
		len += itoa_len(g_vars.error) + j;
	else
		len += ft_strlen(&env[i]) + j;
	new = malloc(len + 1);
	if (!new)
		return (malloc_error());
	new[0] = '\0';
	((char *)tmp->data)[j] = '\0';
	ft_strcat(new, ((char *)tmp->data));
	if (err == 0)
	{
		char	*itoa = ft_itoa(g_vars.error);
		ft_strcat(new, itoa);
		free(itoa);
	}
	else
		ft_strcat(new, &env[i]);
	free(tmp->data);
	if (dq == -1)
		new[len - 1] = '"';
	new[len] = '\0';
	tmp->data = new;
	return (0);
}

void	parse_vars(t_lexer *a)
{
	t_list	*tmp;
	int		i;
	char	*env;

	tmp = a->lst;
	while (tmp)
	{
		i = 0;
		while (((char *)tmp->data)[i])
		{
			quote_maj(a, ((char *)tmp->data)[i]);
			if (((char *)tmp->data)[i] == '$' && a->q == 1)
			{
				env = is_in_env(&((char *)tmp->data)[i + 1], a->dq);
				if (env || ft_strncmp(&((char *)tmp->data)[i], "$?", 2) == 0)
				{
					replace_var(&tmp, env, a->dq);
					break;
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}

t_list	*lexer(char *line, t_lexer *a)
{
	while (line[a->i])
	{
		a->j = 0;
		while (is_in_str(a->sep, line[a->i + a->j]))
			a->j++;
		if (a->j)
			add_str_list(&(a->lst), &line[a->i], a->j);
		a->i += a->j;
		while (line[a->i] == ' ' && a->q == 1 && a->dq == 1)
			a->i++;
		a->j = 0;
		while (line[a->i + a->j] && ((!is_in_str(a->sep, line[a->i + a->j])
					&& line[a->i + a->j] != ' ' && a->q == 1
					&& a->dq == 1) || (a->q != 1 || a->dq != 1)))
		{
			quote_maj(a, line[a->i + a->j]);
			a->j++;
		}
		if (a->j)
			add_str_list(&(a->lst), &line[a->i], a->j);
		a->i += a->j;
	}
	if (!is_quote_closed(a))
		lst_clear(&(a->lst), &free);
	parse_vars(a);
	return (a->lst);
}
