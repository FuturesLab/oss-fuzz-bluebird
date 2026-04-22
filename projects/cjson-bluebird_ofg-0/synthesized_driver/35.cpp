#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
  cJSON *json;

  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  json = cJSON_Parse((const char *)data);

  if (json == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      // Handle the error pointer if needed, for now just continue
    }
  } else {
    cJSON_Delete(json);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif