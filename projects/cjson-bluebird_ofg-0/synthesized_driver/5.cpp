#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0;
    }

    int array_size = size / sizeof(int);
    int *int_array = (int *)malloc(array_size * sizeof(int));
    if (int_array == NULL) {
        return 0;
    }

    memcpy(int_array, data, array_size * sizeof(int));

    cJSON *json_array = cJSON_CreateIntArray(int_array, array_size);

    if (json_array != NULL) {
        cJSON_Delete(json_array);
    }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddRawToObject

        cJSON* ret_cJSON_AddRawToObject_rsesb = cJSON_AddRawToObject(json_array, NULL, NULL);
        if (ret_cJSON_AddRawToObject_rsesb == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    free(int_array);

    return 0;
}
#ifdef __cplusplus
}
#endif