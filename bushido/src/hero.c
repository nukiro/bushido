#include "hero.h"

#include "types.h"

void hero_init(Hero *h)
{
    h->volume = (Volume){
        (Vector3){0.0f, 0.0f, 0.0f},
        (Vector3){0.5f, 2.0f, 0.5f}};
}