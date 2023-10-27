#include "payload.h"

#include <stdint.h>

extern const char _binary_target_efm32pg23_bin_start[];
extern const uint32_t _binary_target_efm32pg23_bin_size;


const void * payload = _binary_target_efm32pg23_bin_start;
const uint32_t * payload_size = &_binary_target_efm32pg23_bin_size;