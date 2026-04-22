#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Allocate memory for a cJSON object
  cJSON *json = cJSON_CreateObject();
  if (json == NULL) {
    return 0;
  }

  // Ensure the data is null-terminated
  char *value_string = (char *)malloc(size + 1);
  if (value_string == NULL) {
    cJSON_Delete(json);
    return 0;
  }
  memcpy(value_string, data, size);
  value_string[size] = '\0';

  // Call the function-under-test
  char *result = cJSON_SetValuestring(json, value_string);

  // Clean up
  free(value_string);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif