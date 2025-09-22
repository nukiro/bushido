#pragma once

struct Manager;

int manager_init(struct Manager *m);
void manager_close(struct Manager *m);