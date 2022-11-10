PARAMS = sphincs-shake-128f
THASH = simple

CC=/usr/bin/gcc
CFLAGS=-Wall -Wextra -Wpedantic -O3 -std=c99 -Wconversion -Wmissing-prototypes -DPARAMS=$(PARAMS) $(EXTRA_CFLAGS)

SOURCES =          address.c randombytes.c merkle.c wots.c wotsx1.c utils.c utilsx1.c fors.c sign.c
HEADERS = params.h address.h randombytes.h merkle.h wots.h wotsx1.h utils.h utilsx1.h fors.h api.h  hash.h thash.h


SOURCES += fips202.c hash_shake.c thash_shake_$(THASH).c
HEADERS += fips202.h

test: test/keygen_sign test/verify

test/message_keys.inc: test/keygen_sign
	./test/keygen_sign > $@


test/keygen_sign: test/keygen_sign.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) test/keygen_sign.c $(LDLIBS)

test/verify: test/message_keys.inc test/verify.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) test/verify.c $(LDLIBS)


.PHONY: clean

clean:
	-rm test/keygen_sign
	-rm test/verify
