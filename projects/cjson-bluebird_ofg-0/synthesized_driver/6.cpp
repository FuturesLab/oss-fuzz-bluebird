#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_PrintPreallocated
    cJSON_bool ret_cJSON_IsString_yupff = cJSON_IsString(json_array);
    if (ret_cJSON_IsString_yupff < 0){
    	return 0;
    }
    cJSON_bool ret_cJSON_IsObject_iznio = cJSON_IsObject(json_array);
    if (ret_cJSON_IsObject_iznio < 0){
    	return 0;
    }

    cJSON_bool ret_cJSON_PrintPreallocated_mnqhg = cJSON_PrintPreallocated(json_array, NULL, ret_cJSON_IsString_yupff, ret_cJSON_IsObject_iznio);
    if (ret_cJSON_PrintPreallocated_mnqhg < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cJSON_Delete(json_array);

    return 0;
}
#ifdef __cplusplus
}
#endif