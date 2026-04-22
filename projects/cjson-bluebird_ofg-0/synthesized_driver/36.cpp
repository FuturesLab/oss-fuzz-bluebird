#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Split the input data into two halves for two cJSON objects
    size_t mid = size / 2;
    const uint8_t *data1 = data;
    size_t size1 = mid;
    const uint8_t *data2 = data + mid;
    size_t size2 = size - mid;

    // Ensure both halves are null-terminated
    char *json_str1 = (char *)malloc(size1 + 1);
    char *json_str2 = (char *)malloc(size2 + 1);
    if (json_str1 == NULL || json_str2 == NULL) {
        free(json_str1);
        free(json_str2);
        return 0;
    }

    memcpy(json_str1, data1, size1);
    json_str1[size1] = '\0';

    memcpy(json_str2, data2, size2);
    json_str2[size2] = '\0';

    // Parse the two JSON strings
    cJSON *json1 = cJSON_Parse(json_str1);
    cJSON *json2 = cJSON_Parse(json_str2);

    free(json_str1);
    free(json_str2);

    if (json1 == NULL || json2 == NULL) {
        cJSON_Delete(json1);
        cJSON_Delete(json2);
        return 0;
    }

    // Use the first byte of the input data to determine the value of the case_sensitive parameter
    cJSON_bool case_sensitive = (data[0] % 2 == 0) ? cJSON_True : cJSON_False;

    // Call the function under test
    cJSON_bool result = cJSON_Compare(json1, json2, case_sensitive);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Compare to cJSON_PrintBuffered
    cJSON* ret_cJSON_CreateNull_ocezi = cJSON_CreateNull();
    if (ret_cJSON_CreateNull_ocezi == NULL){
    	return 0;
    }
    cJSON_bool ret_cJSON_IsInvalid_uremj = cJSON_IsInvalid(json2);
    if (ret_cJSON_IsInvalid_uremj < 0){
    	return 0;
    }

    char* ret_cJSON_PrintBuffered_donmq = cJSON_PrintBuffered(ret_cJSON_CreateNull_ocezi, result, ret_cJSON_IsInvalid_uremj);
    if (ret_cJSON_PrintBuffered_donmq == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cJSON_Delete(json1);
    cJSON_Delete(json2);

    return 0;
}
#ifdef __cplusplus
}
#endif