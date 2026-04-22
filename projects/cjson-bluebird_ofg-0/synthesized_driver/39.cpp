#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  const char *error_ptr = NULL;
  cJSON_bool require_null_termination = cJSON_True;

  // Ensure the input is null-terminated
  char *input_data = (char *)malloc(size + 1);
  if (input_data == NULL) {
    return 0;
  }
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  // Parse the input JSON data
  cJSON *json = cJSON_ParseWithLengthOpts(input_data, size, &error_ptr, require_null_termination);

  // Clean up
  if (json != NULL) {
    cJSON_Delete(json);
  }

  free(input_data);

  return 0;
}

#ifdef __cplusplus
}
#endif