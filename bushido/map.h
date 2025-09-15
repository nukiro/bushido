#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "types.h"
#include "logger.h"
#include "returncode.h"
#include "nathan.h"

#define MAP_NAVIGATION_OUT 'X'
#define MAP_NAVIGATION_FREE '.'
#define MAP_NAVIGATION_OBSTACLE '#'
#define MAP_NAVIGATION_HALF_OBSTACLE '-'
#define MAP_NAVIGATION_DOOR '|'

int map_at(Map map, size_t x, size_t z)
{
    // if (x >= map.x || z >= map.z)
    //     return MAP_NAVIGATION_OUT;

    // map.cells = row-major
    return ((map).cells[(x) * (map).z + (z)]);
}

bool map_is_free_at(Map map, size_t x, size_t z)
{

    if (map_at(map, x, z) == MAP_NAVIGATION_FREE)
    {
        return true;
    }

    return false;
}

static void trim_eol(char *s)
{
    if (!s)
        return;
    size_t n = strlen(s);
    while (n && (s[n - 1] == '\n' || s[n - 1] == '\r'))
        s[--n] = '\0';
}

void map_free(Map *m)
{
    if (!m)
        return;
    free(m->cells);
    m->cells = NULL;
    m->x = m->z = 0;
    m->max_x = m->max_z = 0;
}

#define MAP_AT(m, x, z) ((m).cells[(x) * (m).z + (z)])
rc map_loader(Scene *scene, char pad)
{
    rc rc = RC_OK;
    // open file in read mode
    FILE *fp = fopen(scene->path, "r");
    if (!fp)
    {
        rc = RC_FILE_NOT_OPEN;
        log_error("%s => path(%s)", rc_str(rc), scene->path);
        return rc;
    }

    // find rows and cols in the header file
    size_t rows, cols;
    if (fscanf(fp, "%zu %zu", &rows, &cols) != 2)
    {
        // close file opened previously
        fclose(fp);
        rc = RC_MAP_HEADER_NOT_FOUND;
        log_error("%s => path(%s)", rc_str(rc), scene->path);
        return rc;
    }

    // find nathan initial position
    size_t nx, nz;
    if (fscanf(fp, "%zu %zu", &nx, &nz) != 2)
    {
        // close file opened previously
        fclose(fp);
        rc = RC_MAP_HEADER_NOT_FOUND;
        log_error("%s => path(%s)", rc_str(rc), scene->path);
        return rc;
    }
    nathan_init(scene, nx, nz);

    int ch;
    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
    {
    } // consume rest of line

    scene->map.x = rows;
    scene->map.z = cols;
    scene->map.max_x = rows - 1;
    scene->map.max_z = cols - 1;
    scene->map.cells = (char *)malloc(rows * cols);

    // check if map was loaded
    // means that cells are defined
    if (!scene->map.cells)
    {
        // close file opened previously
        fclose(fp);
        rc = RC_MAP_CELLS_NOT_FOUND;
        log_error("%s => path(%s)", rc_str(rc), scene->path);
        return rc;
    }

    char *line = NULL;
    size_t cap = 0;
    ssize_t n;
    for (size_t x = 0; x < rows; ++x)
    {
        n = getline(&line, &cap, fp);
        if (n < 0)
        {
            free(line);
            fclose(fp);
            free(scene->map.cells);
            return -4;
        }
        trim_eol(line);
        // copy up to cols; pad the rest
        size_t L = strlen(line);
        for (size_t z = 0; z < cols; ++z)
            MAP_AT((scene->map), x, z) = (z < L) ? line[z] : pad;
    }
    free(line);
    fclose(fp);

    log_info("map loaded => %s", scene->path);
    return rc;
}

rc map_init(Scene *scene)
{
    return map_loader(scene, ' ');
}
