#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
  if (size < 2) return 0; // Ensure there is enough data for at least two strings

  // Split the input data into two parts for key and raw value
  size_t key_length = data[0] % (size - 1) + 1; // Ensure key_length is at least 1
  size_t raw_length = size - key_length - 1;

  char *key = (char *)malloc(key_length + 1);
  char *raw_value = (char *)malloc(raw_length + 1);

  if (key == NULL || raw_value == NULL) {
    free(key);
    free(raw_value);
    return 0;
  }

  memcpy(key, data + 1, key_length);
  key[key_length] = '\0';

  memcpy(raw_value, data + 1 + key_length, raw_length);
  raw_value[raw_length] = '\0';

  cJSON *object = cJSON_CreateObject();
  if (object == NULL) {
    free(key);
    free(raw_value);
    return 0;
  }

  cJSON *result = cJSON_AddRawToObject(object, key, raw_value);

  // Clean up
  cJSON_Delete(object);
  free(key);
  free(raw_value);

  return 0;
}

#ifdef __cplusplus
}
#endif