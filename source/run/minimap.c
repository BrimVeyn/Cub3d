/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:18:21 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/08 16:53:39 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3d.h"

void draw_circle_matrix(t_data *data) {
	t_minimap *m;

	m = data->minimap;
    int x = m->draw_size / 2 - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (m->draw_size / 2 << 1);

    while (x >= y) {
        if (m->center_x + x < m->draw_size && m->center_y + y < m->draw_size)
            m->circle_matrix[m->center_x + x][m->center_y + y] = 1; // Octant 1

        if (m->center_x + y < m->draw_size && m->center_y + x < m->draw_size)
            m->circle_matrix[m->center_x + y][m->center_y + x] = 1; // Octant 2

        if (m->center_x - y >= 0 && m->center_y + x < m->draw_size)
            m->circle_matrix[m->center_x - y][m->center_y + x] = 1; // Octant 3

        if (m->center_x - x >= 0 && m->center_y + y < m->draw_size)
            m->circle_matrix[m->center_x - x][m->center_y + y] = 1; // Octant 4

        if (m->center_x - x >= 0 && m->center_y - y >= 0)
            m->circle_matrix[m->center_x - x][m->center_y - y] = 1; // Octant 5

        if (m->center_x - y >= 0 && m->center_y - x >= 0)
            m->circle_matrix[m->center_x - y][m->center_y - x] = 1; // Octant 6

        if (m->center_x + y < m->draw_size && m->center_y - x >= 0)
            m->circle_matrix[m->center_x + y][m->center_y - x] = 1; // Octant 7

        if (m->center_x + x < m->draw_size && m->center_y - y >= 0)
            m->circle_matrix[m->center_x + x][m->center_y - y] = 1; // Octant 8

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (m->draw_size / 2 << 1);
        }
    }
}
// int main() {
//     int width = 10; // Width of the matrix
//     int height = 10; // Height of the matrix
//     int **matrix = (int **)malloc(width * sizeof(int *));
//     for (int i = 0; i < width; i++)
//         matrix[i] = (int *)calloc(height, sizeof(int));
//
//     int centerX = width / 2; // X-coordinate of the center of the circle
//     int centerY = height / 2; // Y-coordinate of the center of the circle
//     int radius = 4; // Radius of the circle
//
//     drawCircle(matrix, centerX, centerY, radius, width, height);
//
//     // Printing the matrix
//     for (int i = 0; i < height; i++) {
//         for (int j = 0; j < width; j++)
//             printf("%d ", matrix[j][i]);
//         printf("\n");
//     }
//
//     // Freeing the memory
//     for (int i = 0; i < width; i++)
//         free(matrix[i]);
//     free(matrix);
//
//     return 0;
// }
