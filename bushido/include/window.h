#pragma once

struct Game;
struct Manager;

void window_init(const struct Game *game, struct Manager *manager);
void window_loop(struct Manager *manager);
void window_close();