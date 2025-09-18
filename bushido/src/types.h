#pragma once

#include <raylib.h>
#include <stdlib.h>

typedef struct Nathan
{
    Vector3 position;
    Vector3 body;
} Nathan;

typedef struct Map
{
    size_t x, z;
    size_t max_x, max_z;
    char *cells; // size = rows * cols, row-major
} Map;

typedef struct Scene
{
    char code[6];
    char from[6];
    const char *path;
    Nathan nathan;
    int facing;
    Map map;
    size_t n_doors;
    char (*doors)[6]; // pointer to arrays of 6 chars
    bool is_ready;
    bool is_done;
    size_t to;
} Scene;

typedef struct Game
{
    const char *title;
    const char *path;
    char code[6];
    char from[6];
    Scene scene;
    Camera3D camera;
} Game;