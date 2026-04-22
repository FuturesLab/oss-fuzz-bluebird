#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
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


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_ReplaceItemInObject
  cJSON* ret_cJSON_CreateNumber_fguxo = cJSON_CreateNumber(cJSON_String);
  if (ret_cJSON_CreateNumber_fguxo == NULL){
  	return 0;
  }
  char* ret_cJSON_Print_troic = cJSON_Print(NULL);
  if (ret_cJSON_Print_troic == NULL){
  	return 0;
  }

  cJSON_bool ret_cJSON_ReplaceItemInObject_rajyz = cJSON_ReplaceItemInObject(ret_cJSON_CreateNumber_fguxo, ret_cJSON_Print_troic, json);
  if (ret_cJSON_ReplaceItemInObject_rajyz < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  cJSON_Delete(json);

  return 0;
}
#ifdef __cplusplus
}
#endif