#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a root JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        return 0;
    }

    // Create a new JSON item to add
    cJSON *item = cJSON_CreateString("example_value");
    if (item == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Use the first byte of the input data as the length of the key
    size_t key_length = data[0] % (size - 1) + 1; // Ensure key_length is at least 1 and less than size
    char *key = (char *)malloc(key_length + 1);
    if (key == NULL) {
        cJSON_Delete(root);
        cJSON_Delete(item);
        return 0;
    }

    // Copy the key from the input data
    memcpy(key, data + 1, key_length);
    key[key_length] = '\0'; // Null-terminate the key

    // Call the function-under-test
    cJSON_bool result = cJSON_AddItemToObjectCS(root, key, item);

    // Clean up
    free(key);
    cJSON_Delete(root);

    return 0;
}

#ifdef __cplusplus
}
#endif