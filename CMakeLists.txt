cmake_minimum_required(VERSION 3.23)
project(Kino C)

set(CMAKE_C_STANDARD 99)

add_executable(Kino main.c catalog.h catalog.c user.c user.h draw_A.c draw_A.h drawing.c drawing.h)
configure_file(films.txt films.txt COPYONLY)
configure_file(Users.txt Users.txt COPYONLY)