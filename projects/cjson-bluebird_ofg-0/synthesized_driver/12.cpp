#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
  cJSON *json;
  char *key;
  size_t key_length;

  if (size < 2) {
    return 0;
  }

  // Ensure the data is null-terminated for safe string operations
  char *input_data = (char *)malloc(size + 1);
  if (input_data == NULL) {
    return 0;
  }
  memcpy(input_data, data, size);
  input_data[size] = '\0';

  // Parse the input data as a JSON object
  json = cJSON_Parse(input_data);
  if (json == NULL) {
    free(input_data);
    return 0;
  }

  // Use a portion of the data as the key
  key_length = size / 2;
  key = (char *)malloc(key_length + 1);
  if (key == NULL) {
    cJSON_Delete(json);
    free(input_data);
    return 0;
  }
  memcpy(key, data, key_length);
  key[key_length] = '\0';

  // Call the function under test
  cJSON_DeleteItemFromObjectCaseSensitive(json, key);

  // Clean up
  cJSON_Delete(json);
  free(key);
  free(input_data);

  return 0;
}

#ifdef __cplusplus
}
#endif