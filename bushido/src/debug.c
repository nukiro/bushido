#include "debug.h"

#include <yaml.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>

#include "common.h"
#include "types.h"
#include "config.h"
#include "utils.h"

#define DEBUG_YAML_KEY_BUFFER_SIZE 256

/**
 * Initializes debug configuration from "debug.yaml".
 *
 * Loads debug settings into the provided Configuration struct.
 *
 * Requirements:
 *   - When compiled with debug support (DEBUG defined), the YAML configuration file
 *     must contain a non-empty "debugger" field. If missing or empty, returns STATUS_ERR_FILE_DEBUG.
 *   - When not in debug mode, "debugger" is optional.
 *
 * @param c Pointer to Configuration struct to populate.
 * @return STATUS_OK on success, STATUS_ERR_FILE_DEBUG on error.
 */
int debug_init(Configuration *c)
{
    DBG("debug mode on");

    FILE *file = fopen("debug.yaml", "r");
    // if we are in debug mode, but no debug configuration is set
    // just return OK as the default configuration is applied
    if (!file)
    {
        DBG("no debug configuration file, default configuration applied");
        return STATUS_OK;
    }

    yaml_parser_t parser;
    yaml_token_t token;

    // Initialize parser
    if (!yaml_parser_initialize(&parser))
    {
        log_error("failed to initialize YAML parser");
        fclose(file);
        return STATUS_ERR_FILE_DEBUG;
    }

    yaml_parser_set_input_file(&parser, file);

    char current_key[DEBUG_YAML_KEY_BUFFER_SIZE] = {0};
    int expecting_value = 0;

    // Parse tokens
    do
    {

        // If scan failures, token is undefined and the loop continues.
        // This error checks it, handling and cleanup when yaml_parser_scan returns 0.
        if (!yaml_parser_scan(&parser, &token))
        {
            log_error(
                "failed to scan YAML token: error=%d problem=%s at %lu:%lu",
                parser.error,
                parser.problem ? parser.problem : "unknown",
                (unsigned long)parser.problem_mark.line,
                (unsigned long)parser.problem_mark.column);
            yaml_parser_delete(&parser);
            fclose(file);
            return STATUS_ERR_FILE_DEBUG;
        }

        switch (token.type)
        {
        case YAML_KEY_TOKEN:
            expecting_value = 0;
            break;

        case YAML_VALUE_TOKEN:
            expecting_value = 1;
            break;

        case YAML_SCALAR_TOKEN:
            if (!expecting_value)
            {
                // Note: strncpy does not NUL-terminate if the source string is too long
                strncpy(current_key, (char *)token.data.scalar.value, sizeof(current_key) - 1);
                current_key[sizeof(current_key) - 1] = '\0'; // Ensure NUL-termination
            }
            else
            {
                // This is a value
                char *value = (char *)token.data.scalar.value;

                if (strcmp(current_key, "debugger") == 0)
                {
                    // 50 characters max
                    snprintf(c->debugger, sizeof(c->debugger), "%s", value);
                }
                else if (strcmp(current_key, "width") == 0)
                {
                    char *end_w = NULL;
                    unsigned long w = strtoul(value, &end_w, 10);
                    if (end_w == value || *end_w != '\0' || w == 0)
                    {
                        log_error("invalid 'width' value: %s", value);
                        yaml_parser_delete(&parser);
                        fclose(file);
                        return STATUS_ERR_FILE_DEBUG;
                    }
                    c->window_width = (int)w;
                }
                else if (strcmp(current_key, "height") == 0)
                {
                    char *end_h = NULL;
                    unsigned long h = strtoul(value, &end_h, 10);
                    if (end_h == value || *end_h != '\0' || h == 0)
                    {
                        log_error("invalid 'height' value: %s", value);
                        yaml_parser_delete(&parser);
                        fclose(file);
                        return STATUS_ERR_FILE_DEBUG;
                    }
                    c->window_height = (int)h;
                }
                else if (strcmp(current_key, "vsync") == 0)
                {
                    c->vsync = (strcasecmp(value, "true") == 0 ||
                                strcasecmp(value, "yes") == 0 ||
                                strcmp(value, "1") == 0);
                }
                else
                {
                    DBG("unknown key in debug configuration: %s", current_key);
                }
                expecting_value = 0;
            }
            break;

        default:
            break;
        }

        if (token.type != YAML_STREAM_END_TOKEN)
        {
            yaml_token_delete(&token);
        }
    } while (token.type != YAML_STREAM_END_TOKEN);

    yaml_token_delete(&token);
    yaml_parser_delete(&parser);

    fclose(file);

#ifdef DEBUG
    if (is_array_empty(c->debugger, sizeof(c->debugger)))
    {
        DBG("debugger field is empty in configuration");
        log_error("debugger property is empty in debug config file");
        return STATUS_ERR_FILE_DEBUG;
    }
    DBG("debugger %s", c->debugger);
#endif

    return STATUS_OK;
}