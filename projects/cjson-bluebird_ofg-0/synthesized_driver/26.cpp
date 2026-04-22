#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
  cJSON *json;
  cJSON *duplicate;
  size_t offset = 1;
  cJSON_bool recurse;

  if (size <= offset)
    {
    return 0;
  }
  if (data[size - 1] != '\0')
    {
    return 0;
  }
  if (data[0] != '1' && data[0] != '0')
    {
    return 0;
  }

  recurse = data[0] == '1' ? 1 : 0;

  json = cJSON_ParseWithOpts((const char *)data + offset, NULL, 1);
  if (json == NULL)
    {
    return 0;
  }

  duplicate = cJSON_Duplicate(json, recurse);

  cJSON_Delete(json);
  if (duplicate != NULL) {

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddArrayToObject
    char* ret_cJSON_PrintUnformatted_lnzjq = cJSON_PrintUnformatted(duplicate);
    if (ret_cJSON_PrintUnformatted_lnzjq == NULL){
    	return 0;
    }

    cJSON* ret_cJSON_AddArrayToObject_nxylg = cJSON_AddArrayToObject(duplicate, ret_cJSON_PrintUnformatted_lnzjq);
    if (ret_cJSON_AddArrayToObject_nxylg == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cJSON_Delete(duplicate);
  }
  return 0;
}

#ifdef __cplusplus
}
#endif