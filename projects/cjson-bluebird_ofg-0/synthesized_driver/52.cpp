#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_52(const uint8_t *data, size_t size) {
  cJSON *json;
  cJSON *array_item;
  size_t offset = 4;
  int index;

  if (size <= offset)
    return 0;
  if (data[size - 1] != '\0')
    return 0;

  // Parse the input data as JSON
  json = cJSON_ParseWithOpts((const char *)data + offset, NULL, 1);
  if (json == NULL)
    return 0;

  // Ensure the JSON object is an array
  if (!cJSON_IsArray(json)) {
    cJSON_Delete(json);
    return 0;
  }

  // Use the first 4 bytes of data to determine the index
  index = (int)(data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));

  // Get the array item at the specified index
  array_item = cJSON_GetArrayItem(json, index);

  // Clean up
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif