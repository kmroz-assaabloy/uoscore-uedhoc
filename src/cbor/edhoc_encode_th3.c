/*
 * Generated using zcbor version 0.3.99
 * https://github.com/NordicSemiconductor/zcbor
 * Generated with a --default-max-qty of 3
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "zcbor_encode.h"
#include "edhoc_encode_th3.h"

#if DEFAULT_MAX_QTY != 3
#error "The type file was generated with a different default_max_qty than this file"
#endif


static bool encode_th3(
		zcbor_state_t *state, const struct th3 *input)
{
	zcbor_print("%s\r\n", __func__);

	bool tmp_result = (((((zcbor_bstr_encode(state, (&(*input)._th3_th_2))))
	&& ((zcbor_bstr_encode(state, (&(*input)._th3_CIPHERTEXT_2)))))));

	if (!tmp_result)
		zcbor_trace();

	return tmp_result;
}



bool cbor_encode_th3(
		uint8_t *payload, size_t payload_len,
		const struct th3 *input,
		size_t *payload_len_out)
{
	zcbor_state_t states[2];

	zcbor_new_state(states, sizeof(states) / sizeof(zcbor_state_t), payload, payload_len, 2);

	bool ret = encode_th3(states, input);

	if (ret && (payload_len_out != NULL)) {
		*payload_len_out = MIN(payload_len,
				(size_t)states[0].payload - (size_t)payload);
	}

	return ret;
}
