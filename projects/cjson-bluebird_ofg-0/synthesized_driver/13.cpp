#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  cJSON_bool is_raw = cJSON_IsRaw(json);

  // Use the result of cJSON_IsRaw to avoid compiler warnings about unused variables
  if (is_raw) {
    // Do something if it's raw, though for fuzzing purposes, we don't need to do anything specific
  }


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_InsertItemInArray
  cJSON_bool ret_cJSON_IsObject_szmth = cJSON_IsObject(json);
  if (ret_cJSON_IsObject_szmth < 0){
  	return 0;
  }
  cJSON* ret_cJSON_CreateNull_zcqtm = cJSON_CreateNull();
  if (ret_cJSON_CreateNull_zcqtm == NULL){
  	return 0;
  }

  cJSON_bool ret_cJSON_InsertItemInArray_kgumg = cJSON_InsertItemInArray(json, ret_cJSON_IsObject_szmth, ret_cJSON_CreateNull_zcqtm);
  if (ret_cJSON_InsertItemInArray_kgumg < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  cJSON_Delete(json);

  return 0;
}
#ifdef __cplusplus
}
#endif