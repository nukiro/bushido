#include <raylib.h>

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "bushido");

    Vector3 nathan = {0.5f, 2.0f, 0.5f};
    Vector3 position = {0.0f, 1.0f, 0.0f};

    // Define the camera to look into our 3d world
    Camera3D camera = {0};
    camera.position = (Vector3){20.0f, 20.0f, -20.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground((Color){25, 25, 25, 1});

        BeginMode3D(camera);

        DrawCube(position, nathan.x, nathan.y, nathan.z, RED);
        DrawCubeWires(position, nathan.x, nathan.y, nathan.z, MAROON);

        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}