#pragma once

struct Configuration;
struct Game;

void config_init(struct Configuration *config);

int game_init(struct Game *game);
void game_close();
