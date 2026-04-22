#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
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


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddItemToArray
        cJSON* ret_cJSON_CreateString_mxedc = cJSON_CreateString(NULL);
        if (ret_cJSON_CreateString_mxedc == NULL){
        	return 0;
        }

        cJSON_bool ret_cJSON_AddItemToArray_rxgvt = cJSON_AddItemToArray(json_array, ret_cJSON_CreateString_mxedc);
        if (ret_cJSON_AddItemToArray_rxgvt < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    free(float_array);

    return 0;
}
#ifdef __cplusplus
}
#endif