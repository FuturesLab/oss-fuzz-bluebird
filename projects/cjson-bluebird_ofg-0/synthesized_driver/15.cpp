#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
  if (size < sizeof(cJSON_Hooks)) {
    return 0;
  }

  cJSON_Hooks hooks;
  memcpy(&hooks, data, sizeof(cJSON_Hooks));

  // Ensure that the function pointers are not NULL
  if (hooks.malloc_fn == NULL) {
    hooks.malloc_fn = malloc;
  }
  if (hooks.free_fn == NULL) {
    hooks.free_fn = free;
  }

  cJSON_InitHooks(&hooks);

  return 0;
}

#ifdef __cplusplus
}
#endif