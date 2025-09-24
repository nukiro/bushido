// contains all structures
#pragma once

#include <raylib.h>
#include <raymath.h>

typedef struct Configuration
{
    char debugger[51];
    int fps;
    const char *assets;
    int window_width;
    int window_height;
    const char *navigation_scene_init;
    int fov_view;
    float fov_zoom;
} Configuration;

typedef struct Game
{
    const char *tag;     // repository version use to build the game
    const char *release; // game build version
    const char *title;
} Game;

typedef struct Navigation
{
    char current[6];
    char previous[6];
} Navigation;

typedef struct Window
{
    const char *title;
    int width;
    int height;
} Window;

typedef enum
{
    Default,
    Aerial,
    Ground,
} View;

typedef struct FieldOfVision
{
    View view;
    Camera camera; // raylib Camera3D
} FieldOfVision;

typedef struct Volume
{
    Vector3 position;
    Vector3 box;
} Volume;

typedef struct Hero
{
    Volume volume;
} Hero;

typedef struct Scene
{
    char id[6];
} Scene;

typedef struct Manager
{
    Window window;
    Navigation navigation;
    Scene *scene;
    FieldOfVision fov;
    Hero hero;

} Manager;
