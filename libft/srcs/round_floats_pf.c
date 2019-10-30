/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_pf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hehlinge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:34:42 by hehlinge          #+#    #+#             */
/*   Updated: 2019/10/01 16:08:36 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_do_rounding(t_flt *flt, t_arg *arg, int len_l, int len_r)
{
	if (flt->val_r[len_r] > '4' && len_r >= (long long int)arg->max)
	{
		while (flt->val_r[len_r - 1] == '9')
			len_r--;
		flt->val_r[len_r - 1]++;
	}
	while (flt->val_r[++len_r])
		if (flt->val_r[len_r - 1] == '9' && flt->val_r[len_r] > '4')
			flt->val_r[len_r - 1] = '0';
	if (!(flt->val_r[0] > '0' || (arg->max < 2 && arg->flags & HASH
				&& flt->val_r[1] > '4')))
	{
		flt->val_r[0] = '.';
		return (0);
	}
	while (flt->val_l[--len_l] == '9' && len_l > -1)
		flt->val_l[len_l] = '0';
	flt->val_r[0] = '.';
	if (len_l > -1)
		flt->val_l[len_l]++;
	else
		flt->val_l[len_l] = '0';
	return (flt->val_l[len_l] == '0' ? 1 : 0);
}

void	ft_banker(char *val_r, int max, char *val_l, int len_r)
{
	int		len_l;

	len_r ? 0 : (len_r++);
	while (len_r > max && val_r[len_r] == '0')
		len_r--;
	if (!(val_r[len_r] == '5'))
		return ;
	val_r[len_r] = '0';
	if (max > 1)
	{
		val_r[max]--;
		val_r[max] += val_r[max] % 2;
	}
	else
	{
		len_l = ft_strlen(val_l);
		val_r[0] = '1' - (val_l[len_l - 1] + 1) % 2;
	}
}

void	ft_round(t_flt *flt, t_arg *arg, long long int len_r, char *ret)
{
	long long int		pos;
	long long int		start;
	long long int		len_l;
	int					keep;

	ft_banker(flt->val_r, arg->max, flt->val_l, len_r - 1);
	len_l = ft_strlen(flt->val_l);
	pos = len_l + arg->max;
	start = arg->flags & MINUS ? 0 : arg->min - len_l - arg->max;
	while (pos - len_l > len_r + 1)
		ret[start + --pos] = '0';
	if ((long long int)arg->max < len_r)
		len_r = arg->max ? arg->max : 1;
	keep = ft_do_rounding(flt, arg, len_l, len_r);
	keep && start && ret[start] == arg->fill ? (start--) : 0;
	while (pos > len_l && pos--)
		ret[start + keep + pos] = flt->val_r[pos - len_l];
	while (pos-- > 0)
		ret[start + keep + pos] = flt->val_l[pos];
	keep ? (ret[start] = keep + 48) : 0;
}
