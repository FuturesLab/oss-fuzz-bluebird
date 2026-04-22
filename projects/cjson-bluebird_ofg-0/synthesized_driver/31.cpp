#include "stdint.h"
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../cJSON.h"

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = cJSON_Version();

    // Print the version to ensure the function is called
    printf("cJSON version: %s\n", version);

    return 0;
}

#ifdef __cplusplus
}
#endif