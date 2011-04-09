/// @todo TODO insert headers...

unsigned char testMode;
#define TEST_MODE_NONE                0
#define TEST_MODE_ITERATIONS          1
#define TEST_MODE_TIME_UNITS_SECONDS  2
#define TEST_MODE_TIME_UNITS_MINUTES  3
#define TEST_MODE_TIME_UNITS_HOURS    4
#define TEST_MODE_REVOLUTIONS         5 // Default of dizzy, sub modes of different patterns:
#define TEST_MODE_REVOLUTIONS_12_1    6
#define TEST_MODE_REVOLUTIONS_24_1    7
#define TEST_MODE_REVOLUTIONS_36_1    8
#define TEST_MODE_REVOLUTIONS_60_2    9
#define TEST_MODE_REVOLUTIONS_4and1  10
#define TEST_MODE_REVOLUTIONS_4and2  11
#define TEST_MODE_REVOLUTIONS_24and1 12
#define TEST_MODE_REVOLUTIONS_24and2 13
#define TEST_MODE_REVOLUTIONS_LT1    14

/// @todo TODO make event array length a var, and populate it with the const at init time, and with the chosen fake array type
/// @todo TODO make the event array itself be a pointer, and switch this pointer in the bench test call with it pre-inited to the address of the const array for real decoders
