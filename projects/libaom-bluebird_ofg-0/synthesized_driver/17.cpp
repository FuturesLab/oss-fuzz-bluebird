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
extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_destroy to aom_codec_control
        size_t ret_aom_uleb_size_in_bytes_ywtfk = aom_uleb_size_in_bytes(AOM_PLANE_Y);
        if (ret_aom_uleb_size_in_bytes_ywtfk < 0){
        	return 0;
        }

        aom_codec_err_t ret_aom_codec_control_poiox = aom_codec_control(&codec_ctx, (int )ret_aom_uleb_size_in_bytes_ywtfk);

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_control to aom_codec_get_stream_info


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from aom_codec_control to aom_codec_set_option

        aom_codec_err_t ret_aom_codec_set_option_xbjhu = aom_codec_set_option(&codec_ctx, (const char *)"w", NULL);

        // End mutation: Producer.APPEND_MUTATOR

        aom_codec_err_t ret_aom_codec_get_stream_info_pmboj = aom_codec_get_stream_info(&codec_ctx, NULL);

        // End mutation: Producer.APPEND_MUTATOR

    aom_codec_destroy(&codec_ctx);
    
    return 0;  // Return 0 to indicate the end of the fuzzing test
}