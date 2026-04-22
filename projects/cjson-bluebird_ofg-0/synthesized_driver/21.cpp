#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Ensure the data is null-terminated to be used as a string
  char *key = (char *)malloc(size + 1);
  if (key == NULL) {
    return 0;
  }
  memcpy(key, data, size);
  key[size] = '\0';

  // Create a dummy JSON object
  cJSON *json = cJSON_CreateObject();
  if (json == NULL) {
    free(key);
    return 0;
  }

  // Add some items to the JSON object
  cJSON_AddStringToObject(json, "exampleKey1", "exampleValue1");
  cJSON_AddStringToObject(json, "exampleKey2", "exampleValue2");

  // Call the function under test
  cJSON_DeleteItemFromObject(json, key);

  // Clean up
  cJSON_Delete(json);
  free(key);

  return 0;
}

#ifdef __cplusplus
}
#endif