#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    if (size < sizeof(float)) {
        return 0;
    }

    int num_floats = size / sizeof(float);
    float *float_array = (float *)malloc(num_floats * sizeof(float));
    if (float_array == NULL) {
        return 0;
    }

    memcpy(float_array, data, num_floats * sizeof(float));

    cJSON *json_array = cJSON_CreateFloatArray(float_array, num_floats);

    if (json_array != NULL) {
        cJSON_Delete(json_array);
    }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddItemToObject
        void* ret_cJSON_malloc_nqaxi = cJSON_malloc(cJSON_True);
        if (ret_cJSON_malloc_nqaxi == NULL){
        	return 0;
        }

        cJSON_bool ret_cJSON_AddItemToObject_gnhkq = cJSON_AddItemToObject(json_array, (const char *)ret_cJSON_malloc_nqaxi, json_array);
        if (ret_cJSON_AddItemToObject_gnhkq < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    free(float_array);

    return 0;
}
#ifdef __cplusplus
}
#endif