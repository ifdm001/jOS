
#ifndef BITSET_H
#define BITSET_H


#include <stdint.h>



static void inline
bitset (u64 *word, u64 pos) 
{
	asm volatile (
		"bts %[bit], %[reg]\n"
		: [reg] "+m"(*word)
		: [bit] "ir" (pos)
		: "cc" ); /* cc = condition code */

}



static void inline
bitclear (u64 *word, u64 pos)
{
	asm volatile (
		"btr %[bit], %[reg]\n"
		: [reg] "+m"(*word)
		: [bit] "ir" (pos)
		: "cc" );
}



static void inline
bittoggle (u64 *word, u64 pos)
{
	asm volatile (
		"btc %[bit], %[reg]\n"
		: [reg] "+m"(*word)
		: [bit] "ir" (pos)
		: "cc" );
}



static u8 inline
bittest (u64 word, u8 pos)
{
	while (pos) {
		word >>= 1;
		--pos;
	}

	return word & 1;

/* TODO: doesn't work (yet) :)
        asm (	"bt %[bit], %[reg]\n"
		"jc 1f\n"
		"xor %%ax, %%ax\n"
		"inc %%ax\n"
		"1:\n"
		: [reg] "+m"(word)
		: [bit] "ir" (pos));
*/
}



/* Returns the position of the leftmost set bit.
 * -1 for 0, 0 for (unsigned)-1 */
static s8 inline
bitscan_left (u64 word)
{
	if (word == 0)
		return -1;

	return MACHINEBITS - __builtin_clzl (word) - 1;
}


/* Same thing starting from the LSB */
static s8 inline
bitscan_right (u64 word)
{
	if (word == 0)
		return -1;

	return __builtin_ctzl (word);
}




#endif /* BITSET_H */


