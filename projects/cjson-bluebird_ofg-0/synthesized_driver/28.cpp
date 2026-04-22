#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for key and value
    size_t key_size = data[0] % size; // Ensure key_size is within bounds
    size_t value_size = size - key_size - 1;

    // Create a null-terminated string for the key
    char *key = (char *)malloc(key_size + 1);
    if (!key) {
        return 0;
    }
    memcpy(key, data + 1, key_size);
    key[key_size] = '\0';

    // Create a cJSON object to replace
    cJSON *replacement_item = cJSON_CreateString("replacement");
    if (!replacement_item) {
        free(key);
        return 0;
    }

    // Create a cJSON object to act as the parent
    cJSON *parent = cJSON_CreateObject();
    if (!parent) {
        cJSON_Delete(replacement_item);
        free(key);
        return 0;
    }

    // Add an initial item to the parent object
    cJSON *initial_item = cJSON_CreateString("initial");
    if (!initial_item) {
        cJSON_Delete(replacement_item);
        cJSON_Delete(parent);
        free(key);
        return 0;
    }
    cJSON_AddItemToObject(parent, key, initial_item);

    // Fuzz the cJSON_ReplaceItemInObjectCaseSensitive function
    cJSON_ReplaceItemInObjectCaseSensitive(parent, key, replacement_item);

    // Clean up
    cJSON_Delete(parent);
    free(key);

    return 0;
}

#ifdef __cplusplus
}
#endif