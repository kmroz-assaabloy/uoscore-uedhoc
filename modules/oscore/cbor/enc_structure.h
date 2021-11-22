/*
 * Generated using cddl_gen version 0.2.99
 * https://github.com/NordicSemiconductor/cddl-gen
 * Generated with a default_max_qty of 3
 */

#ifndef ENC_STRUCTURE_H__
#define ENC_STRUCTURE_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "cbor_encode.h"
#include "types_enc_structure.h"

#if DEFAULT_MAX_QTY != 3
#error "The type file was generated with a different default_max_qty than this file"
#endif


bool cbor_encode_enc_structure(
		uint8_t *payload, uint32_t payload_len,
		const struct enc_structure *input,
		uint32_t *payload_len_out);


#endif /* ENC_STRUCTURE_H__ */
