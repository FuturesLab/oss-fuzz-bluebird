#include "stdint.h"
#include <stddef.h>
#include "stdlib.h"
#include "string.h"
#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Determine the number of strings to create
    int num_strings = data[0] % 10 + 1; // Limit the number of strings to 10 for simplicity

    // Allocate memory for the array of string pointers
    const char **string_array = (const char **)malloc(num_strings * sizeof(char *));
    if (string_array == NULL) {
        return 0;
    }

    // Initialize each string in the array
    size_t offset = 1;
    for (int i = 0; i < num_strings; i++) {
        if (offset >= size) {
            string_array[i] = strdup(""); // Use an empty string if data is exhausted
        } else {
            size_t str_length = (data[offset] % (size - offset)) + 1;
            char *str = (char *)malloc(str_length + 1);
            if (str == NULL) {
                string_array[i] = strdup("");
            } else {
                memcpy(str, data + offset, str_length);
                str[str_length] = '\0';
                string_array[i] = str;
                offset += str_length;
            }
        }
    }

    // Call the function under test
    cJSON *json_array = cJSON_CreateStringArray(string_array, num_strings);

    // Clean up
    if (json_array != NULL) {
        cJSON_Delete(json_array);
    }
    for (int i = 0; i < num_strings; i++) {
        free((void *)string_array[i]);
    }
    free(string_array);

    return 0;
}