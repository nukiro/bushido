#pragma once

struct Configuration;
struct Manager;

int manager_init(struct Manager *manager, const struct Configuration *config);
void manager_close(struct Manager *manager);