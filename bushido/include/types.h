// contains all structures
#pragma once

#include <raylib.h>
#include <raymath.h>

#define NAVIGATION_ID_LENGTH 6 // 5 characters plus null terminator
#define DEBUGGER_NAME_MAX_LENGTH 51

typedef struct Configuration
{
    /**
     * Debugger name.
     * Required (non-empty) only when compiled with debug support (DEBUG defined).
     * Optional otherwise.
     */
    char debugger[DEBUGGER_NAME_MAX_LENGTH];
    int fps;
    const char *assets;
    int window_width;
    int window_height;
    const char *navigation_scene_init;
    int fov_view;
    float fov_zoom;
    bool vsync;
} Configuration;

typedef struct Game
{
    const char *tag;     // repository version use to build the game
    const char *release; // game build version
    const char *title;
} Game;

typedef struct Navigation
{
    char current[NAVIGATION_ID_LENGTH];
    char previous[NAVIGATION_ID_LENGTH];
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
