#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "../cJSON.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Create a dummy cJSON object to replace an item in
  cJSON *json_object = cJSON_CreateObject();
  cJSON *item_to_replace = cJSON_CreateString("original_value");
  cJSON_AddItemToObject(json_object, "key", item_to_replace);

  // Create a new cJSON item to replace the existing one
  cJSON *new_item = cJSON_CreateString("new_value");

  // Ensure the key is null-terminated
  size_t key_length = size - 1;
  char *key = (char *)malloc(key_length + 1);
  if (key == NULL) {
    cJSON_Delete(json_object);
    cJSON_Delete(new_item);
    return 0;
  }
  memcpy(key, data, key_length);
  key[key_length] = '\0';

  // Call the function under test
  cJSON_ReplaceItemInObject(json_object, key, new_item);

  // Clean up
  free(key);
  cJSON_Delete(json_object);

  return 0;
}

#ifdef __cplusplus
}
#endif