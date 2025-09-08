#include <raylib.h>
#include <raymath.h>

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    const int speed = 1;

    InitWindow(screenWidth, screenHeight, "bushido");

    Vector3 nathan = {0.5f, 2.0f, 0.5f};
    Vector3 position = {0.0f, 1.0f, 0.0f};

    // Define the camera to look into our 3d world
    Camera3D camera = {0};
    camera.position = (Vector3){-10.0f, 10.0f, -10.0f};
    camera.target = position;
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 25.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    SetTargetFPS(120);

    // Main game loop
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // 1) Build a direction vector from input
        Vector3 dir = {0.0f, 0.0f, 0.0f};
        if (IsKeyDown(KEY_W))
        {
            dir.x += 1.0f;
            dir.z += 1.0f;
        }
        if (IsKeyDown(KEY_S))
        {
            dir.x -= 1.0f;
            dir.z -= 1.0f;
        }
        if (IsKeyDown(KEY_A))
        {
            dir.x += 1.0f;
            dir.z -= 1.0f;
        }
        if (IsKeyDown(KEY_D))
        {
            dir.x -= 1.0f;
            dir.z += 1.0f;
        }

        // 2) Normalize (so diagonals aren't faster) and move once
        if (dir.x != 0.0f || dir.z != 0.0f)
        {
            dir = Vector3Normalize(dir);
            position = Vector3Add(position, Vector3Scale(dir, speed * dt));
        }

        BeginDrawing();

        ClearBackground((Color){25, 25, 25, 1});

        BeginMode3D(camera);

        DrawCube(position, nathan.x, nathan.y, nathan.z, PURPLE);
        DrawCubeWires(position, nathan.x, nathan.y, nathan.z, WHITE);

        DrawLine3D(position, Vector3Add(position, (Vector3){3.0f, 0.0f, 0.0f}), RED);
        DrawLine3D(position, Vector3Add(position, (Vector3){0.0f, 3.0f, 0.0f}), GREEN);
        DrawLine3D(position, Vector3Add(position, (Vector3){0.0f, 0.0f, 3.0f}), BLUE);

        DrawGrid(20, 1.0f);

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}