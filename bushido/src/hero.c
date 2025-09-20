#include "hero.h"

void hero_init(Hero *h)
{
    h->position = (Vector3){0.0f, 0.0f, 0.0f};
    h->box = (Vector3){0.5f, 2.0f, 0.5f};
}