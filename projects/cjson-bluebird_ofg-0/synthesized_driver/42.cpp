#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_42(const uint8_t *data, size_t size) {
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
  cJSON* ret_cJSON_CreateNumber_xlxyp = cJSON_CreateNumber(cJSON_StringIsConst);
  if (ret_cJSON_CreateNumber_xlxyp == NULL){
  	return 0;
  }

  cJSON_bool ret_cJSON_ReplaceItemInObject_cfeuy = cJSON_ReplaceItemInObject(json, NULL, ret_cJSON_CreateNumber_xlxyp);
  if (ret_cJSON_ReplaceItemInObject_cfeuy < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  cJSON_Delete(json);

  return 0;
}
#ifdef __cplusplus
}
#endif