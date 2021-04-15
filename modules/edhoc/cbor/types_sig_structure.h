/*
 * Generated with cddl_gen.py (https://github.com/oyvindronningstad/cddl_gen)
 * Generated with a default_maxq of 3
 */

#ifndef TYPES_SIG_STRUCTURE_H__
#define TYPES_SIG_STRUCTURE_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "cbor_encode.h"

#define DEFAULT_MAXQ 3

struct sig_structure {
 	cbor_string_type_t _sig_structure_context;
	cbor_string_type_t _sig_structure_external_aad;
	cbor_string_type_t _sig_structure_payload;
};


#endif /* TYPES_SIG_STRUCTURE_H__ */
