# Copyright (c) 2021 Fraunhofer AISEC. See the COPYRIGHT
# file at the top-level directory of this distribution.

# Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
# http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
# <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
# option. This file may not be copied, modified, or distributed
# except according to those terms.

LIB_NAME = libuoscore-uedhoc.a

include makefile_config.mk

$(info    CC is $(CC))
# $(info    LIB_NAME is $(LIB_NAME))
# $(info    PREFIX is $(PREFIX))
# $(info    SOURCE_DIR is $(SOURCE_DIR))
# $(info    BINARY_DIR is $(BINARY_DIR))
# $(info    CC is $(CC))
# $(info    CFLAGS is $(CFLAGS))
# $(info    OPT is $(OPT))
# $(info    CRYPTO_ENGINE is $(CRYPTO_ENGINE))
################################################################################
# Build directory
PREFIX ?= build
DIR = $(PREFIX)
$(shell mkdir -p $(DIR))
################################################################################
# C Source files

C_SOURCES += $(wildcard src/edhoc/*.c)
C_SOURCES += $(wildcard src/oscore/*.c)
C_SOURCES += $(wildcard src/common/*.c)
C_SOURCES += $(wildcard src/cbor/*.c)


#$(info    \n C_SOURCES is $(C_SOURCES))
vpath %.c $(sort $(dir $(C_SOURCES)))

################################################################################
# libraries 


################################################################################
# C includes
C_INCLUDES += -Iinc

# Crypto engine
ifeq ($(findstring COMPACT25519,$(CRYPTO_ENGINE)),COMPACT25519) 
C_INCLUDES += -Iexternals/compact25519/src/c25519/ 
C_INCLUDES += -Iexternals/compact25519/src/ 
endif

ifeq ($(findstring TINYCRYPT,$(CRYPTO_ENGINE)),TINYCRYPT)
C_INCLUDES += -Iexternals/tinycrypt/lib/include
endif
 
ifeq ($(findstring MBEDTLS,$(CRYPTO_ENGINE)),MBEDTLS)
C_INCLUDES += -Iexternals/mbedtls/library 
C_INCLUDES += -Iexternals/mbedtls/include 
C_INCLUDES += -Iexternals/mbedtls/include/mbedtls 
C_INCLUDES += -Iexternals/mbedtls/include/psa 
endif

# CBOR engine
ifeq ($(findstring ZCBOR,$(CBOR_ENGINE)),ZCBOR)
C_INCLUDES += -Iexternals/zcbor/include
endif

################################################################################
# CFLAGS
################################################################################
FILTERED_CFLAGS = -Os
EXTENDED_CFLAGS = $(filter-out $(FILTERED_CFLAGS), $(CFLAGS))

#add options form configuration file 
EXTENDED_CFLAGS += $(ARCH)
EXTENDED_CFLAGS += $(OPT)
EXTENDED_CFLAGS += $(DEBUG_PRINT)
EXTENDED_CFLAGS += $(CBOR_ENGINE)
EXTENDED_CFLAGS += $(CRYPTO_ENGINE)
EXTENDED_CFLAGS += $(DUNIT_TEST)

#add include paths
EXTENDED_CFLAGS += $(C_INCLUDES)

#generate debug symbols
EXTENDED_CFLAGS += -g -gdwarf-2

# Generate dependency information
EXTENDED_CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"



#GCC warning flags
ifeq ($(findstring cc,$(CC)),cc)
EXTENDED_CFLAGS += -Waddress
EXTENDED_CFLAGS += -Waggregate-return
EXTENDED_CFLAGS += -Wformat-nonliteral
EXTENDED_CFLAGS += -Wformat-security
EXTENDED_CFLAGS += -Wformat
EXTENDED_CFLAGS += -Winit-self
EXTENDED_CFLAGS += -Wmissing-include-dirs
EXTENDED_CFLAGS += -Wno-multichar
EXTENDED_CFLAGS += -Wno-parentheses
EXTENDED_CFLAGS += -Wno-type-limits
EXTENDED_CFLAGS += -Wno-unused-parameter
EXTENDED_CFLAGS += -Wunreachable-code
EXTENDED_CFLAGS += -Wwrite-strings
EXTENDED_CFLAGS += -Wpointer-arith
EXTENDED_CFLAGS += -Wall
EXTENDED_CFLAGS += -Wextra
EXTENDED_CFLAGS += -Wcast-qual
EXTENDED_CFLAGS += -Wstack-usage=9000
EXTENDED_CFLAGS += -Wconversion
EXTENDED_CFLAGS += -Wpedantic
#EXTENDED_CFLAGS += -Werror

#Clang warning flahs
else ifeq ($(findstring clang,$(CC)),clang)
EXTENDED_CFLAGS += -Wcast-qual
EXTENDED_CFLAGS += -Wconversion
EXTENDED_CFLAGS += -Wexit-time-destructors
EXTENDED_CFLAGS += -Wglobal-constructors
EXTENDED_CFLAGS += -Wmissing-noreturn
EXTENDED_CFLAGS += -Wmissing-prototypes
EXTENDED_CFLAGS += -Wno-missing-braces
EXTENDED_CFLAGS += -Wold-style-cast
EXTENDED_CFLAGS += -Wshadow
EXTENDED_CFLAGS += -Wweak-vtables
EXTENDED_CFLAGS += -Wall
EXTENDED_CFLAGS += -Wextra
EXTENDED_CFLAGS += -Wpedantic
EXTENDED_CFLAGS += -Wstack-exhausted
EXTENDED_CFLAGS += -Wconversion
#EXTENDED_CFLAGS += -Werror
endif

# use AddressSanitizer to find memory bugs
# comment this out for better speed
#EXTENDED_CFLAGS += -fsanitize=address -fno-omit-frame-pointer
#CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer
#LDFLAGS += -fsanitize=address -static-libasan

$(info    EXTENDED_CFLAGS are $(EXTENDED_CFLAGS))
################################################################################
# build the library
################################################################################
OBJ = $(addprefix $(DIR)/,$(notdir $(C_SOURCES:.c=.o)))
#$(info    \n OBJ is $(OBJ))


$(DIR)/$(LIB_NAME): $(OBJ) 
	@echo "[Link (Static)]"
	@$(AR) -rcs $@ $^

$(DIR)/%.o: %.c Makefile makefile_config.mk
	@echo [Compile] $<
	@$(CC) -c $(EXTENDED_CFLAGS) $< -o $@

clean:
	rm -fR $(DIR)