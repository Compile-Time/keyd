/*
 * keyd - A key remapping daemon.
 *
 * © 2019 Raheman Vaiya (see also: LICENSE).
 */
#ifndef __H_LAYER_
#define __H_LAYER_
	
#include "keys.h"
#include "descriptor.h"

#define MAX_LAYER_NAME_LEN	32
#define MAX_COMPOSITE_LAYERS	8
#define MAX_TIMEOUTS		32

#define MAX_MACRO_SIZE	128
#define MAX_MACROS	64

#define LT_NORMAL	0
#define LT_LAYOUT	1
#define LT_COMPOSITE	2

#define LF_ACTIVE	0x1
#define LF_TOGGLE	0x2
#define LF_ONESHOT	0x4
#define LF_ONESHOT_HELD	0x8

/*
 * A layer is a map from keycodes to descriptors. It may optionally
 * contain one or more modifiers which are applied to the base layout in
 * the event that no matching descriptor is found in the keymap. For
 * consistency, modifiers are internally mapped to eponymously named
 * layers consisting of the corresponding modifier and an empty keymap.
 */

struct layer {
	char name[MAX_LAYER_NAME_LEN];

	size_t nr_layers;
	int layers[MAX_COMPOSITE_LAYERS];

	int type;
	uint8_t mods;

	struct descriptor keymap[256];

	/* state */
	uint8_t flags;
	long activation_time;
};

struct timeout {
	uint16_t timeout;
	struct descriptor d1;
	struct descriptor d2;
};

struct macro_entry {
	enum {
		MACRO_KEYSEQUENCE,
		MACRO_HOLD,
		MACRO_RELEASE,
		MACRO_TIMEOUT
	} type;

	uint8_t code;
	uint8_t mods;
	uint16_t timeout;
};

/*
 * A series of key sequences optionally punctuated by
 * timeouts
 */
struct macro {
	struct macro_entry entries[MAX_MACRO_SIZE];
	size_t sz;
};

struct layer_table {
	struct layer layers[MAX_LAYERS];
	size_t nr;

	struct timeout timeouts[MAX_TIMEOUTS];
	struct macro macros[MAX_MACROS];

	size_t nr_macros;
	size_t nr_timeouts;
};

#endif
