#include "stdint.h"
#include "stdlib.h"
#include <stddef.h>
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read at least one double and an integer
    if (size < sizeof(double) + sizeof(int)) {
        return 0;
    }

    // Calculate the number of doubles we can read from the data
    int num_doubles = (size - sizeof(int)) / sizeof(double);

    // Extract the integer value from the data
    int count = *((int *)(data + num_doubles * sizeof(double)));

    // Ensure count is not negative and does not exceed num_doubles
    if (count < 0 || count > num_doubles) {
        return 0;
    }

    // Create an array of doubles from the data
    const double *double_array = (const double *)data;

    // Call the function under test
    cJSON *json_array = cJSON_CreateDoubleArray(double_array, count);

    // Clean up
    if (json_array != NULL) {

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_CreateDoubleArray to cJSON_AddNumberToObject
    cJSON_bool ret_cJSON_IsObject_wxzhp = cJSON_IsObject(json_array);
    if (ret_cJSON_IsObject_wxzhp < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of cJSON_AddNumberToObject
    cJSON* ret_cJSON_AddNumberToObject_irriw = cJSON_AddNumberToObject(json_array, NULL, (const double)ret_cJSON_IsObject_wxzhp);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_cJSON_AddNumberToObject_irriw == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddStringToObject

        cJSON* ret_cJSON_AddStringToObject_kiipj = cJSON_AddStringToObject(json_array, NULL, (const char *)"w");
        if (ret_cJSON_AddStringToObject_kiipj == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        cJSON_Delete(json_array);
    }   return 0;
}

#ifdef __cplusplus
}
#endif