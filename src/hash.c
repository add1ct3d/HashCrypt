// CRC-32 Hashing Algorithm

#include "header.h"

// Hash seed using CRC-32 hashing algorithm
unsigned int toHash(const char* buf) {
	unsigned int len = strlen(buf);
    unsigned int crc = 0;
	static unsigned int table[256];
	static int have_table = 0;
	unsigned int rem;
	unsigned char octet;
	int i, j;
	const char *p, *q;

	if (have_table == 0) {
		for (i = 0; i < 256; i++) {
			rem = i;  // Stores remainder from division
			for (j = 0; j < 8; j++) {
				if (rem & 1) {
					rem >>= 1;
					rem ^= 0xedb88320;
				} else
					rem >>= 1;
			}
			table[i] = rem;
		}
		have_table = 1;
	}

	crc = ~crc;
	q = buf + len;
	for (p = buf; p < q; p++) {
		octet = *p;  // Cast to unsigned octet
		crc = (crc >> 8) ^ table[(crc & 0xff) ^ octet];
	}
	return ~crc;
}
