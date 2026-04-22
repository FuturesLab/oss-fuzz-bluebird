#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size); /* required by C89 */

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
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


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Duplicate to cJSON_InsertItemInArray


  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Duplicate to cJSON_AddItemReferenceToObject
  void* ret_cJSON_malloc_gqoku = cJSON_malloc(cJSON_Object);
  if (ret_cJSON_malloc_gqoku == NULL){
  	return 0;
  }

  cJSON_bool ret_cJSON_AddItemReferenceToObject_clflc = cJSON_AddItemReferenceToObject(duplicate, (const char *)ret_cJSON_malloc_gqoku, NULL);
  if (ret_cJSON_AddItemReferenceToObject_clflc < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  cJSON_bool ret_cJSON_InsertItemInArray_mtesb = cJSON_InsertItemInArray(duplicate, CJSON_CIRCULAR_LIMIT, duplicate);
  if (ret_cJSON_InsertItemInArray_mtesb < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  cJSON_Delete(json);
  if (duplicate != NULL) {

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddArrayToObject
    char* ret_cJSON_PrintUnformatted_lnzjq = cJSON_PrintUnformatted(duplicate);
    if (ret_cJSON_PrintUnformatted_lnzjq == NULL){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cJSON_AddArrayToObject with cJSON_AddObjectToObject
    cJSON* ret_cJSON_AddArrayToObject_nxylg = cJSON_AddObjectToObject(duplicate, ret_cJSON_PrintUnformatted_lnzjq);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_cJSON_AddArrayToObject_nxylg == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cJSON_Delete(duplicate);
  }return 0;
}

#ifdef __cplusplus
}
#endif