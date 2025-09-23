#pragma once

struct Configuration;
struct Game;
struct Manager;

void window_init(const struct Game *game, struct Manager *manager, const struct Configuration *config);
void window_loop(struct Manager *manager);
void window_close();