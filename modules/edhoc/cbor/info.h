/*
 * Generated with cddl_gen.py (https://github.com/oyvindronningstad/cddl_gen)
 * Generated with a default_maxq of 3
 */

#ifndef INFO_H__
#define INFO_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "cbor_encode.h"
#include "types_info.h"

#if DEFAULT_MAXQ != 3
#error "The type file was generated with a different default_maxq than this file"
#endif


bool cbor_encode_info(
		uint8_t *payload, size_t payload_len,
		const struct info *input,
		size_t *payload_len_out);


#endif /* INFO_H__ */
