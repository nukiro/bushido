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
    const char *path;
    Nathan nathan;
    int facing;
    Map map;
} Scene;

typedef struct Game
{
    const char *title;
    const char *path;
    const char *code;
    Scene scene;
    Camera3D camera;
} Game;