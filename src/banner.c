/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpirotti <vpirotti@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:25:37 by vpirotti          #+#    #+#             */
/*   Updated: 2025/08/08 15:25:37 by vpirotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#include <stdio.h>
#define RED_B "\033[38;5;196m"

void	banner_two(void)
{
	ft_putendl_fd(RESET"  -^  '888'  X888  8888>     888E    8888  888R    888E"
		"   %8'    R88  "RED_B"888E  888E 8888"
		".+'     "RED_B" 888R     888R   ", 1);
	ft_putendl_fd(RESET"   dx '88~x. !88~  8888>     888E    8888  888R    888E"
		"    @8Wou 9%   "RED_B"888E  888E 8888L  "
		"      "RED_B"888R     888R   ", 1);
	ft_putendl_fd(RESET" .8888Xf.888x:!    X888X.:   888&   '*88*' 8888'   888&"
		"  .888888P`    "RED_B"888E  888E '8888c. "
		".+  "RED_B".888B .  .888B . ", 1);
	ft_putendl_fd(RESET":''888':~'888'     `888*'    R888'    ''   'Y'     R888"
		"' `   ^'F    "RED_B" m888N= 888>  '88888% "
		"  "RED_B" ^*888%   ^*888%  ", 1);
	ft_putendl_fd(RESET"    '~'    '~        ''       ''                    '' "
		"              "RED_B" `Y''   888     ''YP' "
		"    "RED_B"  '%       '%    ", 1);
	ft_putendl_fd("                                                            "
		"          "RED_B"     J88'                        "
		"       ", 1);
	ft_putendl_fd("                                                            "
		"         "RED_B"      @%                          "
		"       ", 1);
	ft_putendl_fd("                                                            "
		"   "RED_B"          :'                            "
		"       "RESET, 1);
}

void	print_banner(void)
{
	ft_putendl_fd(RESET"    ...     ..      ..        .                     .  "
		"     .x+=:.                                "RED_B"..  "
		"     .. ", 1);
	ft_putendl_fd(RESET"  x*8888x.:*8888: -'888:     @88>                  @88>"
		"    z`    ^%   "RED_B" 'uef^'              "RED_B" x ."
		"d88'  x .d88", 1);
	ft_putendl_fd(RESET" X   48888X `8888H  8888     %8P      u.    u.     %8P "
		"       .   <k :"RED_B"d88E                "RED_B"   588"
		"8R    5888R   ", 1);
	ft_putendl_fd(RESET"X8x.  8888X  8888X  !888>     .     x@88k u@88c.    ."
		"       .@8Ned8' "RED_B"`888E            .u   "
		" "RED_B" '888R    '888R   ", 1);
	ft_putendl_fd(RESET"X8888 X8888  88888   '*8%-  .@88u  ^'8888''8888'  .@88"
		"u   .@^%8888'  "RED_B" 888E .z8k    ud8888."
		"   "RED_B" 888R     888R   ", 1);
	ft_putendl_fd(RESET"'*888!X8888> X8888  xH8>   ''888E`   8888  888R  ''888"
		"E` x88:  `)8b. "RED_B" 888E~?888L :888'88"
		"88.  "RED_B" 888R     888R   ", 1);
	ft_putendl_fd(RESET"  `?8 `8888  X888X X888>     888E    8888  888R    888"
		"E  8888N=*8888  "RED_B"888E  888E d888 '88%' "
		"  "RED_B"888R     888R   ", 1);
	banner_two();
}
