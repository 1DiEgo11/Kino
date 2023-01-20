#ifndef CATS_DRAWING_H
#define CATS_DRAWING_H
/**
 * ==========================
 * === Объявление функций ===
 * ==========================
 *
 * Объявление показывает лишь то как функции будут выглядеть при их вызове;
 * Тело функции здесь не нужно
 */

// Подсчет длины строки, состощей из символов русского алфавита
unsigned short ru_strlen(char *str);

// Установка позиции курсора
void set_cursor_position(short x, short y);

// Отрисовка горизонтальной линии
void draw_horizontal_line(short x, short y, unsigned short length);

// Отрисовка вертикальной линии
void draw_vertical_line(short x, short y, unsigned short length);

// Отрисовка прямоугольника
void draw_square(short x, short y, unsigned short width, unsigned short height);

// Очистка рабочей части консоли
void clear_viewport();

// Вычисление координат окна для того, чтобы оно находилось по центру рабочей
// части консоли
short calculate_window_x(unsigned short width);

short calculate_window_y(unsigned short height);

// Отрисовка окна
void draw_window(short x, short y, unsigned short width, unsigned short height,
                 char **content, unsigned short count_to_show);

// Отрисовка одного блока звездочек в заданной позиции
void draw_stars_block(short x, short y);

// Отрисовка звездочек вокруг окна заданных размеров и в заданной позиции
void draw_stars_around_window(short window_x, short window_y,
                              unsigned short window_width,
                              unsigned short window_height);
#endif //CATS_DRAWING_H
