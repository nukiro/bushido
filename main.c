#include <raylib.h>
#include <raymath.h>

#include <stdlib.h>
#include <stdio.h>

// bool collision(Vector3 position, int x, int y)
// {
//     return true;
// }

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    const int speed = 3;
    // const float map = 9.0f;

    // bool collision = false;

    int matrix[11][11] = {
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1},
        {-1, 0, 0, 1, 0, 0, 0, 0, 0, 1, -1},
        {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 0, 1, 1, 0, -1},
        {-1, 1, 0, 0, 0, 0, 0, 1, 1, 0, -1},
        {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
        {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
        {-1, 1, 0, 0, 0, 0, 0, 0, 1, 0, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    };

    InitWindow(screenWidth, screenHeight, "bushido");

    // Vector3 nathana = {0.45f, 1.9f, 0.45f};
    Vector3 nathan = {1.0f, 0.0f, 1.0f};

    // Define the camera to look into our 3d world
    Camera3D camera = {0};
    camera.position = Vector3Add(nathan, (Vector3){-10.0f, 10.0f, -10.0f});
    camera.target = Vector3Add(nathan, (Vector3){0.0f, 1.0f, 0.0f});
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 10.0f;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    SetTargetFPS(60);

    // int mx = (int)nathan.x + (9 / 2);
    // int mz = (int)nathan.x + (9 / 2);

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
            Vector3 newPosition = Vector3Add(nathan, Vector3Scale(dir, speed * dt));

            if (newPosition.x > 0)
            {
                nathan.x = newPosition.x;
            }
            if (newPosition.z > 0)
            {
                nathan.z = newPosition.z;
            }

            camera.position = Vector3Add(nathan, (Vector3){-10.0f, 10.0f, -10.0f});
            camera.target = Vector3Add(nathan, (Vector3){0.0f, 1.0f, 0.0f});

            // mx = (int)newPosition.x + (9 / 2);
            // mz = (int)newPosition.z + (9 / 2);

            // if (newPosition.z <= -3.0f && (newPosition.x >= -1 && newPosition.x <= 0))
            // {
            //     collision = true;
            // }
            // else
            // {
            //     collision = false;
            // }

            // once the direction vector is set
            // check map boundaries
            // if (fabs(newPosition.x) < (map / 2.0f) - 0.25f - 0.05f)
            // {
            //     nathan.x = newPosition.x;
            // }
            // if (fabs(newPosition.z) < (map / 2.0f) - 0.25f - 0.05f)
            // {
            //     nathan.z = newPosition.z;
            // }

            // camera.position = Vector3Add(nathan, (Vector3){-10.0f, 10.0f, -10.0f});
        }

        BeginDrawing();

        ClearBackground((Color){25, 25, 25, 1});

        BeginMode3D(camera);

        // DrawCube(nathan, nathana.x, nathana.y, nathana.z, PURPLE);
        // DrawCubeWires(nathan, nathana.x, nathana.y, nathana.z, WHITE);

        // Obstacles
        // for (int i = 0; i < 9; i++)
        // {
        //     for (int j = 0; j < 9; j++)
        //     {
        //         if (matrix[i][j] != 0)
        //         {
        //             DrawCube((Vector3){i - (9 / 2), 0.5f, j - (9 / 2)}, 0.9f, 0.9f, 0.9f, BROWN);
        //             DrawCubeWires((Vector3){i - (9 / 2), 0.5f, j - (9 / 2)}, 1.0f, 1.0f, 1.0f, WHITE);
        //         }
        //     }
        // }

        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 11; j++)
            {
                int box = matrix[i][j];
                if (box != 0)
                {
                    if (box == -1)
                    {
                        DrawCube((Vector3){i, 0.5f, j}, 0.9f, 0.9f, 0.9f, (Color){150, 150, 150, 50});
                        // DrawCubeWires((Vector3){i, 0.5f, j}, 1.0f, 1.0f, 1.0f, WHITE);
                    }
                    else
                    {
                        DrawCube((Vector3){i, 0.5f, j}, 0.9f, 0.9f, 0.9f, RED);
                        DrawCubeWires((Vector3){i, 0.5f, j}, 1.0f, 1.0f, 1.0f, WHITE);
                    }
                }
            }
        }
        DrawCapsuleWires(nathan, Vector3Add(nathan, (Vector3){0.0f, 2.0f, 0.0f}), 0.5f, 8, 8, PURPLE);
        // DrawCubeWires(Vector3Add(nathan, (Vector3){-1.0f, 0.5f, 1.0f}), 1.0f, 1.0f, 1.0f, (Color){255, 255, 255, 50});
        // DrawCubeWires(Vector3Add(nathan, (Vector3){-1.0f, 0.5f, 0.0f}), 1.0f, 1.0f, 1.0f, (Color){255, 255, 255, 50});
        // DrawCubeWires(Vector3Add(nathan, (Vector3){-1.0f, 0.5f, -1.0f}), 1.0f, 1.0f, 1.0f, (Color){255, 255, 255, 50});
        // BoundingBox box = {(Vector3){-1.0f, 0.0f, 1.0f}, (Vector3){-1.0f, 1.0f, 1.0f}};
        // DrawBoundingBox(box, RED);

        // DrawCube((Vector3){2.0f, 0.5f, 3.0f}, 0.90f, 0.90f, 0.90f, BROWN);
        // DrawCubeWires((Vector3){2.0f, 0.5f, 3.0f}, 0.90f, 0.90f, 0.90f, WHITE);

        // Boundaries
        // DrawCube((Vector3){0.0f, 0.5f, -5.0f}, 9.0f, 1.0f, 0.9f, (Color){230, 41, 55, 50});
        // DrawCubeWires((Vector3){0.0f, 0.5f, -5.0f}, 9.0f, 1.0f, 0.9f, (Color){255, 255, 255, 150});
        // DrawCube((Vector3){-5.0f, 0.5f, 0.0f}, 0.9f, 1.0f, 9.0f, (Color){230, 41, 55, 50});
        // DrawCubeWires((Vector3){-5.0f, 0.5f, 0.0f}, 0.9f, 1.0f, 9.0f, (Color){255, 255, 255, 150});
        // DrawCube((Vector3){0.0f, 0.5f, 5.0f}, 9.0f, 1.0f, 0.9f, (Color){230, 41, 55, 255});
        // DrawCubeWires((Vector3){0.0f, 0.5f, 5.0f}, 9.0, 1.0f, 0.9f, (Color){255, 255, 255, 150});
        // DrawCube((Vector3){5.0f, 0.5f, 0.0f}, 0.9f, 1.0f, 9.0, (Color){230, 41, 55, 255});
        // DrawCubeWires((Vector3){5.0f, 0.5f, 0.0f}, 0.9f, 1.0f, 9.0, (Color){255, 255, 255, 150});

        // DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){map, map}, DARKGREEN);

        DrawLine3D(Vector3Add(nathan, (Vector3){0.0f, 1.0f, 0.0f}), Vector3Add(Vector3Add(nathan, (Vector3){0.0f, 1.0f, 0.0f}), (Vector3){2.0f, 0.0f, 0.0f}), RED);
        // DrawLine3D(Vector3Add(nathan, (Vector3){0.0f, 1.0f, 0.0f}), Vector3Add(Vector3Add(nathan, (Vector3){0.0f, 1.0f, 0.0f}), (Vector3){0.0f, 2.0f, 0.0f}), GREEN);
        DrawLine3D(Vector3Add(nathan, (Vector3){0.0f, 1.0f, 0.0f}), Vector3Add(Vector3Add(nathan, (Vector3){0.0f, 1.0f, 0.0f}), (Vector3){0.0f, 0.0f, 2.0f}), BLUE);

        DrawLine3D((Vector3){-0.5f, 0.0f, -0.5f}, (Vector3){1.0f, 0.0f, -0.5f}, WHITE);
        DrawLine3D((Vector3){-0.5f, 0.0f, -0.5f}, (Vector3){-0.5f, 0.0f, 1.0f}, WHITE);

        // DrawGrid(52, 0.25f);
        // DrawGrid(9, 1.0f);

        EndMode3D();

        // DrawFPS(10, 10);

        DrawText(TextFormat("Position: x=%.2f y=%.2f z=%.2f", nathan.x, nathan.y, nathan.z), 10, 10, 12, LIME);
        DrawText(TextFormat("Position Matrix: x=%d z=%d", (int)nathan.x, (int)nathan.z), 10, 30, 12, LIME);
        // DrawText(TextFormat("Matrix position: x=%d z=%d", mx, mz), 10, 50, 12, LIME);
        // DrawText(TextFormat("[%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d]", matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3], matrix[0][4], matrix[0][5], matrix[0][6], matrix[0][7], matrix[0][8], matrix[0][9]), 10, 70, 12, LIME);
        // DrawText(TextFormat("Matrix Collision %d", matrix[mx][mz] != 0), 10, 70, 12, LIME);
        // DrawText(TextFormat("Collision %d", collision), 10, 90, 12, LIME);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}