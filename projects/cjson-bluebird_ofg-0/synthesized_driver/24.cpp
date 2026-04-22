#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    cJSON *json_array;
    cJSON *detached_item;
    size_t offset = 4;
    int index;

    if (size <= offset)
        {
        return 0;
    }
    if (data[size - 1] != '\0')
        {
        return 0;
    }

    // Parse the input data as a JSON array
    json_array = cJSON_ParseWithOpts((const char *)data + offset, NULL, 1);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_ParseWithOpts to cJSON_AddNullToObject

    cJSON* ret_cJSON_AddNullToObject_yhcrr = cJSON_AddNullToObject(json_array, (const char *)data);
    if (ret_cJSON_AddNullToObject_yhcrr == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    if (json_array == NULL || !cJSON_IsArray(json_array))
        {
        return 0;
    }

    // Use the first 4 bytes of data to determine the index
    index = (int)(data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));

    // Detach item from array
    detached_item = cJSON_DetachItemFromArray(json_array, index);

    // Free the detached item if it exists
    if (detached_item != NULL) {
        cJSON_Delete(detached_item);
    }

    // Delete the JSON array
    cJSON_Delete(json_array);

    return 0;
}
#ifdef __cplusplus
}
#endif