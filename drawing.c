// Подключение файла с объявлением структур и соответствующих функций
#include "list.h"
// Подключение системных библиотек
#include <math.h>
#include <stdio.h>
#include <string.h>

/**
 * =================
 * === Константы ===
 * =================
 */

// Символы рамки окна
const char *HORIZONTAL_LINE_SYMBOL = "\u2550";
const char *VERTICAL_LINE_SYMBOL = "\u2551";
const char *LEFT_TOP_ANGLE_LINE_SYMBOL = "\u2554";
const char *RIGHT_TOP_ANGLE_LINE_SYMBOL = "\u2557";
const char *LEFT_BOTTOM_ANGLE_LINE_SYMBOL = "\u255A";
const char *RIGHT_BOTTOM_ANGLE_LINE_SYMBOL = "\u255D";

// Размер рабочей части консоли
const unsigned short VIEWPORT_WIDTH = 130;
const unsigned short VIEWPORT_HEIGHT = 40;

// Размеры блока со звездочками
const unsigned short STARS_BLOCK_WIDTH = 14;
const unsigned short STARS_BLOCK_HEIGHT = 9;

/**
 * ===========================
 * === Описание функций ===
 * ===========================
 *
 * Описание работы функций показывает то, как функции работают изнутри
 */

// Подсчет длины строки, состощей из символов русского алфавита
unsigned short ru_strlen(char *str) {
    // Т.к. размер символа русского алфавита - 2 байта вместо 1, то найти размер
    // строки и поделить на 2 (без учета таких символов как пробел, запятая и тд.,
    // которые занимают 1 байт)
    return ceil(strlen(str) / 2);
}

// Установка позиции курсора
void set_cursor_position(short x, short y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

// Отрисовка горизонтальной линии
void draw_horizontal_line(short x, short y, unsigned short length) {
    // Установить курсор
    set_cursor_position(x, y);

    // Посимвольно вывести в строку символы горизончальной части рамки
    for (unsigned short i = 0; i < length; i++) {
        printf("%s", HORIZONTAL_LINE_SYMBOL);
    }
}

// Отрисовка вертикальной линии
void draw_vertical_line(short x, short y, unsigned short length) {
    // Для каждого символа линии
    for (unsigned short i = 0, new_y = y; i < length; i++) {
        // Установить новое положение курсора
        set_cursor_position(x, new_y);
        // Увеличить координату y
        new_y++;

        // Вывести символ вертикальной части рамки
        printf("%s", VERTICAL_LINE_SYMBOL);
    }
}

// Отрисовка прямоугольника
void draw_square(short x, short y, unsigned short width,
                 unsigned short height) {
    // Отрисовка сторон

    // Верхняя
    draw_horizontal_line(x, y, width);
    // Правая
    draw_vertical_line(x + width - 1, y, height);
    // Нижняя
    draw_horizontal_line(x, y + height - 1, width);
    // Левая
    draw_vertical_line(x, y, height);

    // Отрисовка углов

    // Левый верхний
    set_cursor_position(x, y);
    printf("%s", LEFT_TOP_ANGLE_LINE_SYMBOL);

    // Правый верхний
    set_cursor_position(x + width - 1, y);
    printf("%s", RIGHT_TOP_ANGLE_LINE_SYMBOL);

    // Правый нижний
    set_cursor_position(x + width - 1, y + height - 1);
    printf("%s", RIGHT_BOTTOM_ANGLE_LINE_SYMBOL);

    // Левый нижний
    set_cursor_position(x, y + height - 1);
    printf("%s", LEFT_BOTTOM_ANGLE_LINE_SYMBOL);
}

// Очистка рабочей части консоли
void clear_viewport() {
    // Установить курсор в начало рабочей области
    set_cursor_position(0, 0);

    // Для каждого символа по оси y
    for (unsigned short y = 0; y < VIEWPORT_HEIGHT; y++) {
        // Для каждого символа по оси x
        for (unsigned short x = 0; x < VIEWPORT_WIDTH; x++) {
            // Вывести пробел
            printf("%c", ' ');
        }
        // Перенести строку
        printf("%c", '\n');
    }
}

// Вычисление координат окна для того, чтобы оно находилось по центру рабочей
// части консоли
short calculate_window_x(unsigned short width) {
    return (VIEWPORT_WIDTH - width) / 2;
}

short calculate_window_y(unsigned short height) {
    return (VIEWPORT_HEIGHT - height) / 2;
}

// Отрисовка окна
void draw_window(short x, short y, unsigned short width, unsigned short height,
                 char **content, unsigned short size_of_content) {
    // Отрисовка прямоугольника
    draw_square(x, y, width, height);

    // Для каждой строки контента
    for (unsigned short i = 0; i < size_of_content; i++) {
        // Поставить координаты так, чтобы текст был по центру окна
        set_cursor_position(x + width / 2 - ru_strlen(content[i]) / 2 - 1,
                            y + (i + 1) * 2);
        // Вывести текст
        printf("%s", content[i]);
    }

    // Убрать курсор за прямоугольник
    set_cursor_position(0, y + height);
}

// Отрисовка одного блока звездочек в заданной позиции
void draw_stars_block(short x, short y) {
    // Отрисовка рамок
    draw_square(x, y, STARS_BLOCK_WIDTH, STARS_BLOCK_HEIGHT);

    // Массив строк со звездочками
    const char *stars[] = {
            "\u2605\u2605\u2605\u2605\u2605\u2605\u2605",
            "\u2605\u2605\u2605\u2605\u2605",
            "\u2605\u2605\u2605",
            "\u2605",
            "",
            "\u2605\u2605\u2605",
    };

    // Для каждой строки
    for (unsigned short i = 0; i < 6; i++) {
        // Поставить координаты так, чтобы строка была по центру блока
        set_cursor_position(x + (STARS_BLOCK_WIDTH - strlen(stars[i]) / 3) / 2,
                            y + (i + 1));
        // Вывести звездочки
        printf("%s", stars[i]);
    }
}

// Отрисовка звездочек вокруг окна заданных размеров и в заданной позиции
void draw_stars_around_window(short window_x, short window_y,
                              unsigned short window_width,
                              unsigned short window_height) {
    // Координата y, расчитанная так, чтобы блоки были вертикально по центру окна
    const short y = window_y + (window_height - STARS_BLOCK_HEIGHT) / 2;

    // Отрисовать левый блок
    draw_stars_block(window_x - STARS_BLOCK_WIDTH + 1, y);
    // Отрисовать правй блок
    draw_stars_block(window_x + window_width - 1, y);
}