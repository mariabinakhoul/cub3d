/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raldanda <raldanda>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:39:44 by raldanda          #+#    #+#             */
/*   Updated: 2025/07/01 11:40:03 by raldanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

/* ────────────────────────────
**  Regular foreground colours
** ──────────────────────────── */
# define CLR_RESET       "\033[0m"
# define CLR_BLACK       "\033[0;30m"
# define CLR_RED         "\033[0;31m"
# define CLR_GREEN       "\033[0;32m"
# define CLR_YELLOW      "\033[0;33m"
# define CLR_BLUE        "\033[0;34m"
# define CLR_MAGENTA     "\033[0;35m"
# define CLR_CYAN        "\033[0;36m"
# define CLR_WHITE       "\033[0;37m"

/* ────────────────────────────
**  Bold foreground colours
** ──────────────────────────── */
# define BCLR_BLACK      "\033[1;30m"
# define BCLR_RED        "\033[1;31m"
# define BCLR_GREEN      "\033[1;32m"
# define BCLR_YELLOW     "\033[1;33m"
# define BCLR_BLUE       "\033[1;34m"
# define BCLR_MAGENTA    "\033[1;35m"
# define BCLR_CYAN       "\033[1;36m"
# define BCLR_WHITE      "\033[1;37m"

/* ────────────────────────────
**  Underlined foreground colours
** ──────────────────────────── */
# define UCLR_BLACK      "\033[4;30m"
# define UCLR_RED        "\033[4;31m"
# define UCLR_GREEN      "\033[4;32m"
# define UCLR_YELLOW     "\033[4;33m"
# define UCLR_BLUE       "\033[4;34m"
# define UCLR_MAGENTA    "\033[4;35m"
# define UCLR_CYAN       "\033[4;36m"
# define UCLR_WHITE      "\033[4;37m"

/* ────────────────────────────
**  Background colours
** ──────────────────────────── */
# define BG_BLACK        "\033[40m"
# define BG_RED          "\033[41m"
# define BG_GREEN        "\033[42m"
# define BG_YELLOW       "\033[43m"
# define BG_BLUE         "\033[44m"
# define BG_MAGENTA      "\033[45m"
# define BG_CYAN         "\033[46m"
# define BG_WHITE        "\033[47m"

# define INFO            CLR_CYAN
# define WARN            CLR_YELLOW
# define ERROR           CLR_RED

#endif