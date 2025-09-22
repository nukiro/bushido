#pragma once

#include "volume.h"

typedef struct Hero
{
    Volume volume;
} Hero;

void hero_init(Hero *hero);