#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Allocate memory for a copy of the input data plus a null terminator
  char *input_copy = (char *)malloc(size + 1);
  if (input_copy == NULL) {
    return 0;
  }

  // Copy the input data into the allocated memory
  memcpy(input_copy, data, size);

  // Ensure the input is null-terminated
  input_copy[size] = '\0';

  // Call the function-under-test
  cJSON_Minify(input_copy);

  // Free the allocated memory

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Minify to cJSON_HasObjectItem
  cJSON* ret_cJSON_CreateBool_vqxak = cJSON_CreateBool(1);
  if (ret_cJSON_CreateBool_vqxak == NULL){
  	return 0;
  }

  cJSON_bool ret_cJSON_HasObjectItem_qawhl = cJSON_HasObjectItem(ret_cJSON_CreateBool_vqxak, input_copy);
  if (ret_cJSON_HasObjectItem_qawhl < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  free(input_copy);

  return 0;
}
#ifdef __cplusplus
}
#endif