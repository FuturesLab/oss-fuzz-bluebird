#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
  if (size < sizeof(double)) {
    return 0;
  }

  cJSON *json = cJSON_CreateObject();
  if (json == NULL) {
    return 0;
  }

  double number;
  memcpy(&number, data, sizeof(double));

  cJSON_SetNumberHelper(json, number);

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif