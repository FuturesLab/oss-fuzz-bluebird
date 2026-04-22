#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
  if (size == 0 || data[size - 1] != '\0') {
    return 0;
  }

  cJSON *json = cJSON_Parse((const char *)data);
  if (json == NULL) {
    return 0;
  }

  double number_value = cJSON_GetNumberValue(json);

  // Optionally, print the number value for debugging purposes
  printf("Number value: %f\n", number_value);

  cJSON_Delete(json);

  return 0;
}

#ifdef __cplusplus
}
#endif