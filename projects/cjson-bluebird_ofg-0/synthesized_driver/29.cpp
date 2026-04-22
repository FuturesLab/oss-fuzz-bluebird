#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
  cJSON *json;
  cJSON *result;
  char *key;
  cJSON_bool value;

  // Ensure there is enough data for a key and a boolean value
  if (size < 2) return 0;

  // Create a new JSON object
  json = cJSON_CreateObject();
  if (json == NULL) return 0;

  // Use the first byte as a boolean value
  value = (data[0] % 2 == 0) ? cJSON_False : cJSON_True;

  // Use the rest of the data as a key
  key = (char *)malloc(size);
  if (key == NULL) {
    cJSON_Delete(json);
    return 0;
  }
  memcpy(key, data + 1, size - 1);
  key[size - 1] = '\0'; // Ensure null-termination

  // Call the function-under-test
  result = cJSON_AddBoolToObject(json, key, value);

  // Clean up
  free(key);
  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif