#pragma once

#include <raylib.h>

typedef struct Hero
{
    Vector3 position;
    Vector3 box;
} Hero;

void hero_init(Hero *hero);