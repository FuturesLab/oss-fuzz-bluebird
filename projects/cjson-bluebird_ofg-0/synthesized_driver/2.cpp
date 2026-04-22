#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a JSON array
    cJSON *json_array = cJSON_CreateArray();
    if (json_array == NULL) {
        return 0;
    }

    // Add a few items to the array to ensure it has elements

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cJSON_AddItemToArray with cJSON_AddItemReferenceToArray
    cJSON_AddItemReferenceToArray(json_array, cJSON_CreateString("item1"));
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    cJSON_AddItemToArray(json_array, cJSON_CreateString("item2"));
    cJSON_AddItemToArray(json_array, cJSON_CreateString("item3"));

    // Use the first byte of data as the index
    int index = data[0] % cJSON_GetArraySize(json_array);

    // Parse the remaining data as a new cJSON item
    cJSON *new_item = cJSON_ParseWithLength((const char *)(data + 1), size - 1);
    if (new_item == NULL) {
        cJSON_Delete(json_array);
        return 0;
    }

    // Call the function-under-test
    cJSON_bool result = cJSON_ReplaceItemInArray(json_array, index, new_item);

    // Clean up
    cJSON_Delete(json_array);

    return 0;
}
#ifdef __cplusplus
}
#endif