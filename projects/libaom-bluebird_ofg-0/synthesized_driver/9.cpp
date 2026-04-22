#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <aom/aom_codec.h>
#include <aom/aom_decoder.h>

extern "C" {
    aom_codec_err_t aom_codec_peek_stream_info(aom_codec_iface_t *, const uint8_t *, size_t, aom_codec_stream_info_t *);
    aom_codec_iface_t *aom_codec_av1_dx(); // Declare the AV1 decoder interface function
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    aom_codec_iface_t *codec_iface = aom_codec_av1_dx(); // Using AV1 decoder interface
    aom_codec_stream_info_t stream_info;
    
    // Initialize stream_info to avoid NULL dereference
    memset(&stream_info, 0, sizeof(stream_info));

    // Call the function under test with valid parameters
    aom_codec_err_t result = aom_codec_peek_stream_info(codec_iface, data, size, &stream_info);

    // Optionally handle the result or inspect stream_info if needed
    if (result == AOM_CODEC_OK) {
        // Successfully peeked stream info, you can add additional checks or processing here
    }

    return 0;
}