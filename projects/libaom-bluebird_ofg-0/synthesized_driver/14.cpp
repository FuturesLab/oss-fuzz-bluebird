#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>

extern "C" {
    // Include necessary AOM headers for codec context and error types
    #include <aom/aom_codec.h>
    #include <aom/aom_decoder.h>
    #include <aom/aomdx.h> // Include this header for aom_codec_av1_dx
}

// Fuzzing harness for the AOM codec decode function
extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Initialize codec context
    aom_codec_ctx_t codec_ctx;
    aom_codec_err_t result;

    // Initialize the codec context
    result = aom_codec_dec_init(&codec_ctx, aom_codec_av1_dx(), NULL, 0);
    if (result != AOM_CODEC_OK) {
        return 0;  // Initialization failed
    }

    // Ensure the input size is reasonable
    if (size == 0 || size > 65536) {
        aom_codec_destroy(&codec_ctx);
        return 0;  // Invalid input size
    }

    // Call the function-under-test
    result = aom_codec_decode(&codec_ctx, data, size, NULL);
    
    // Cleanup

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_destroy to aom_codec_error


        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function aom_codec_error with aom_codec_error_detail
        const char* ret_aom_codec_error_bonta = aom_codec_error_detail(&codec_ctx);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_aom_codec_error_bonta == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec_ctx);
    
    return 0;  // Return 0 to indicate the end of the fuzzing test
}