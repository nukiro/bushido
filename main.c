#include <raylib.h>
#include <raymath.h>

#include <stdlib.h>

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    const int speed = 3;
    const float map = 9.0f;

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
            Vector3 newPosition = Vector3Add(position, Vector3Scale(dir, speed * dt));

            // once the direction vector is set
            // check map boundaries
            if (fabs(newPosition.x) < (map / 2.0f) - 0.25f - 0.05f)
            {
                position.x = newPosition.x;
            }
            if (fabs(newPosition.z) < (map / 2.0f) - 0.25f - 0.05f)
            {
                position.z = newPosition.z;
            }
        }

        BeginDrawing();

        ClearBackground((Color){25, 25, 25, 1});

        BeginMode3D(camera);

        DrawCube(position, nathan.x, nathan.y, nathan.z, PURPLE);
        DrawCubeWires(position, nathan.x, nathan.y, nathan.z, WHITE);

        DrawCube((Vector3){-1.0f, 0.5f, 1.0f}, 0.90f, 0.90f, 0.90f, BROWN);
        DrawCubeWires((Vector3){-1.0f, 0.5f, 1.0f}, 0.90f, 0.90f, 0.90f, WHITE);

        DrawCube((Vector3){2.0f, 0.5f, 3.0f}, 0.90f, 0.90f, 0.90f, BROWN);
        DrawCubeWires((Vector3){2.0f, 0.5f, 3.0f}, 0.90f, 0.90f, 0.90f, WHITE);

        DrawCube((Vector3){0.0f, 0.5f, -5.0f}, 9.0f, 1.0f, 0.9f, (Color){230, 41, 55, 50});
        DrawCubeWires((Vector3){0.0f, 0.5f, -5.0f}, 9.0f, 1.0f, 0.9f, (Color){255, 255, 255, 150});
        DrawCube((Vector3){-5.0f, 0.5f, 0.0f}, 0.9f, 1.0f, 9.0f, (Color){230, 41, 55, 50});
        DrawCubeWires((Vector3){-5.0f, 0.5f, 0.0f}, 0.9f, 1.0f, 9.0f, (Color){255, 255, 255, 150});
        DrawCube((Vector3){0.0f, 0.5f, 5.0f}, 9.0f, 1.0f, 0.9f, (Color){230, 41, 55, 255});
        DrawCubeWires((Vector3){0.0f, 0.5f, 5.0f}, 9.0, 1.0f, 0.9f, (Color){255, 255, 255, 150});
        DrawCube((Vector3){5.0f, 0.5f, 0.0f}, 0.9f, 1.0f, 9.0, (Color){230, 41, 55, 255});
        DrawCubeWires((Vector3){5.0f, 0.5f, 0.0f}, 0.9f, 1.0f, 9.0, (Color){255, 255, 255, 150});

        DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){map, map}, DARKGREEN);

        DrawLine3D(position, Vector3Add(position, (Vector3){3.0f, 0.0f, 0.0f}), RED);
        DrawLine3D(position, Vector3Add(position, (Vector3){0.0f, 3.0f, 0.0f}), GREEN);
        DrawLine3D(position, Vector3Add(position, (Vector3){0.0f, 0.0f, 3.0f}), BLUE);

        DrawGrid(52, 0.25f);

        EndMode3D();

        DrawFPS(10, 10);

        DrawText(TextFormat("Position: x=%.2f y=%.2f z=%.2f", position.x, position.y, position.z), 10, 30, 12, LIME);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}