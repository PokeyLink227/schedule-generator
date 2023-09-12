#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

enum DAYOFWEEK {
    NONE,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

color_rgb COLOR_RED = {0xff, 0x00, 0x00};

struct time_block {
    int start, end;
    unsigned char days[7];
};

void draw_rect(bmp_image img, int x, int y, int width, int height, color_rgb color) {
    if (x < 0 || x >= img.width || y < 0 || y >= img.height || width <= 0 || height <= 0) return;
    for (int w = 0; w < width; w++) for (int h = 0; h < height; h++) img.pixels[(y + h) * img.width + x + w] = color;
    return;
}

int main(int argc, char **argv) {
    int canvas_length = 10800;
    color_rgb canvas[10800];
    for (int i = 0; i < canvas_length; i++) canvas[i] = (color_rgb){0, 0, 0};
    bmp_image img = {90, 120, canvas};

    struct time_block classes[6] = {
        {14, 15, {0, 1, 0, 1, 0, 0, 0}},
        {9, 11, {0, 1, 0, 1, 0, 0, 0}},
        {11, 12, {1, 0, 1, 0, 0, 0, 0}},
        {8, 9, {1, 0, 1, 0, 1, 0, 0}},
        {9, 10, {1, 0, 0, 0, 0, 0, 0}},
        {17, 20, {0, 1, 0, 0, 0, 0, 0}}
    };

    for (int i = 0; i < 6; i++) {
        for (int d = 0; d < 7; d++) if (classes[i].days[d]) draw_rect(img, d * 10, classes[i].start * 5, 10, (classes[i].end - classes[i].start) * 5, COLOR_RED);
    }



    save_image(img, "schedule.bmp");
}
