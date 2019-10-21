/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats_pf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 20:27:26 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/30 20:27:27 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_prefix_flt(int sign, t_arg *arg, char *ret)
{
	char	prefix;
	char	*add;
	int		pos;
	int		len;

	prefix = sign == 1 ? '-' : 0;
	sign == 0 && arg->flags & SPACE ? (prefix = ' ') : 0;
	sign == 0 && arg->flags & PLUS ? (prefix = '+') : 0;
	if (!(add = (char *)easymalloc(2)))
		return (0);
	add[0] = prefix;
	pos = 0;
	while (!ft_isdigit(ret[pos]) && !ft_isdigit(ret[pos + 1]))
		pos++;
	if ((ret[pos] == '0' || ret[pos] == arg->fill)
			&& ft_isdigit(ret[pos + 1]) && prefix)
		ret[pos] = *add;
	else if (prefix)
	{
		ret = ft_strjoin(add, ret);
		len = ft_strlen(ret);
		ret[len - 1] == ' ' ? (ret[len - 1] = 0) : 0;
	}
	ft_free((void **)&add);
	return (ret);
}

int		ft_pad_flt(t_flt *flt, t_buf *buf, t_arg *arg)
{
	unsigned long long int		len_l;
	char						*ret;

	arg->min > 2147483647 ? (arg->min = 6) : 0;
	!arg->prec || arg->max > 2147483647 ? (arg->max = 6) : 0;
	arg->max || arg->flags & HASH ? arg->max++ : 0;
	len_l = ft_strlen(flt->val_l);
	arg->min < len_l + arg->max ? (arg->min = len_l + arg->max) : 0;
	if (!(ret = (char *)easymalloc(arg->min + 2)))
		return (0);
	arg->fill = arg->flags & ZERO && !(arg->flags & MINUS) ? '0' : ' ';
	ft_memset(ret, arg->fill, arg->min);
	ft_round(flt, arg, ft_strlen(flt->val_r) - 1, ret);
	if (!(ret = ft_prefix_flt(flt->sign, arg, ret)))
		return (0);
	return (add_to_buf(ret, buf));
}

int		ft_pad_spec(t_flt *flt, t_arg *arg, t_buf *buf)
{
	char	*prefix;
	char	*ret;
	int		len;
	int		start;

	if (!(ret = (char *)easymalloc(arg->min + 4)))
		return (0);
	flt->val_l = flt->flt == flt->flt * 2 ? ("inf") : ("nan");
	prefix = flt->val_l[0] == 'i' && arg->flags & SPACE ? " " : 0;
	flt->val_l[0] == 'i' && arg->flags & PLUS ? (prefix = "+") : 0;
	flt->val_l[0] == 'i' && flt->flt < 0 ? (prefix = "-") : 0;
	if (!(flt->val_l = ft_strjoin(prefix, flt->val_l)))
		return (0);
	start = arg->flags & MINUS ? 0 : arg->min - ft_strlen(flt->val_l);
	start < 0 ? (start = 0) : 0;
	ft_memset(ret, ' ', arg->min);
	len = -1;
	while (flt->val_l[++len])
	{
		ret[start + len] = flt->val_l[len];
	}
	return (add_to_buf(ret, buf));
}

int		ft_parse_flt(t_flt *flt)
{
	char				*c;
	int					oct;
	unsigned char		all[16];

	c = (char *)&(flt->flt);
	oct = 16;
	while (--oct > 5)
		all[oct] = *(c + (15 - oct));
	flt->sign = all[6] >> 7;
	flt->exp = (all[6] << 9);
	flt->exp >>= 1;
	flt->exp |= all[7];
	flt->exp &= (short)32767;
	if (flt->exp)
		flt->exp -= 16383;
	oct = 7;
	while (++oct < 16)
	{
		oct < 9 ? 0 : (flt->mant <<= 8);
		flt->mant |= all[oct];
	}
	if (!ft_calc_flt(flt))
		return (0);
	return (1);
}

int		f_float(t_arg *arg, t_buf *buf, va_list arg_list)
{
	t_flt		flt;

	ft_memset(&flt, 0, sizeof(t_flt));
	if (!arg->field)
		flt.flt = (long double)va_arg(arg_list, double);
	else if (arg->field == LFIELD)
		flt.flt = (long double)va_arg(arg_list, double);
	else if (arg->field == LMAJFIELD)
		flt.flt = va_arg(arg_list, long double);
	if (flt.flt != flt.flt || (flt.flt && flt.flt == flt.flt * 2))
	{
		if (!(ft_pad_spec(&flt, arg, buf)))
			return (0);
	}
	else
	{
		if (!(ft_parse_flt(&flt)))
			return (ft_display(buf, 0));
		return (ft_pad_flt(&flt, buf, arg));
	}
	ft_free((void **)&flt.val_l);
	ft_free((void **)&flt.val_r);
	ft_free((void **)&flt.add);
	return (1);
}
