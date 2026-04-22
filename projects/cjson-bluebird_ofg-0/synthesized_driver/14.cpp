#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0; // Ensure there's enough data for the parameters
  }

  // Parse the input data as a JSON object
  cJSON *json = cJSON_ParseWithLength((const char *)data, size);
  if (json == NULL) {
    return 0; // Return if parsing fails
  }

  // Allocate a buffer for the output
  int buffer_size = 256; // Example buffer size
  char *buffer = (char *)malloc(buffer_size);
  if (buffer == NULL) {
    cJSON_Delete(json);
    return 0; // Return if memory allocation fails
  }

  // Extract parameters from the input data
  cJSON_bool formatted = (data[0] % 2 == 0) ? true : false; // Use first byte to determine formatting

  // Call the function-under-test
  cJSON_bool result = cJSON_PrintPreallocated(json, buffer, buffer_size, formatted);

  // Clean up
  free(buffer);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif