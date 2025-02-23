/*
   Copyright (c) 2022 Eriptic Technologies. See the COPYRIGHT
   file at the top-level directory of this distribution.

   Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
   http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
   <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
   option. This file may not be copied, modified, or distributed
   except according to those terms.
*/

#include <zephyr/zephyr.h>
#include <zephyr/ztest.h>

#include "oscore/option.h"
#include "common/byte_array.h"

void t400_is_class_e(void)
{
	enum o_num not_e_opt_nums[] = { URI_HOST, URI_PORT, OSCORE, PROXY_URI,
					PROXY_SCHEME };

	uint32_t len = sizeof(not_e_opt_nums) / sizeof(not_e_opt_nums[0]);
	for (uint32_t i = 0; i < len; i++) {
		zassert_equal(is_class_e(not_e_opt_nums[i]), false, "");
	}
}

void t401_cache_echo_val(void)
{
	struct byte_array empty = BYTE_ARRAY_INIT(NULL, 0);
	enum err r;

	struct o_coap_option options[] = {
		{ .delta = 2, .len = 0, .value = NULL, .option_number = 2 },
		{ .delta = 2, .len = 0, .value = NULL, .option_number = 4 },
		{ .delta = 3, .len = 0, .value = NULL, .option_number = 7 },
		{ .delta = 5, .len = 0, .value = NULL, .option_number = ECHO }
	};

	/*successful caching*/
	r = cache_echo_val(&empty, (struct o_coap_option *)&options, 4);
	zassert_equal(r, ok, "Error in cache_echo_val. r: %d", r);

	/*unsuccessful caching */
	r = cache_echo_val(&empty, (struct o_coap_option *)&options, 3);
	zassert_equal(r, no_echo_option, "Error in cache_echo_val. r: %d", r);
}

void t402_echo_val_is_fresh(void)
{
	enum err r;

	uint8_t cache_val_buf[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
				    0x06, 0x07, 0x08, 0x09, 0x10, 0x11 };

	struct byte_array cache_val =
		BYTE_ARRAY_INIT(cache_val_buf, sizeof(cache_val_buf));

	uint8_t decrypted_payload_buf[] = { 0x01 }; /*code only*/
	struct byte_array decrypted_payload = BYTE_ARRAY_INIT(
		decrypted_payload_buf, sizeof(decrypted_payload_buf));

	/*test no ECHO option*/
	r = echo_val_is_fresh(&cache_val, &decrypted_payload);
	zassert_equal(r, no_echo_option, "Error in echo_val_is_fresh. r: %d",
		      r);

	/*test ECHO option mismatch*/
	uint8_t decrypted_payload_buf_mismatch[] = {
		0x81, 0xDC, 0xEF, 0x00, 0x01, 0x02, 0x03, 0x04,
		0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x12
	}; /*wrong last byte of the ECHO option*/
	struct byte_array decrypted_payload_mismatch =
		BYTE_ARRAY_INIT(decrypted_payload_buf_mismatch,
				sizeof(decrypted_payload_buf_mismatch));

	r = echo_val_is_fresh(&cache_val, &decrypted_payload_mismatch);
	zassert_equal(r, echo_val_mismatch, "Error in echo_val_is_fresh. r: %d",
		      r);
}