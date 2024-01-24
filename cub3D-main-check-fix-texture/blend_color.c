/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgras-ca <fgras-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:33:36 by fgras-ca          #+#    #+#             */
/*   Updated: 2024/01/09 13:43:05 by fgras-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int blendColor(int color1, int color2, float alpha) {
    int r = ((color1 >> 16 & 0xFF) * (1 - alpha)) + ((color2 >> 16 & 0xFF) * alpha);
    int g = ((color1 >> 8 & 0xFF) * (1 - alpha)) + ((color2 >> 8 & 0xFF) * alpha);
    int b = ((color1 & 0xFF) * (1 - alpha)) + ((color2 & 0xFF) * alpha);

    return (r << 16) | (g << 8) | b;
}

void drawTransparentSquare(t_structure_main *w, int x, int y, int color, float alpha) {
    int backgroundColor = 0x000000; // Couleur d'arrière-plan, à ajuster selon vos besoins
    int blendedColor = blendColor(color, backgroundColor, alpha);

    draw_square(w, x, y, blendedColor); // Utilisez votre fonction existante pour dessiner le carré
}
