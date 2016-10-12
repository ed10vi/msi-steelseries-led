static const unsigned char defaultConf[kSize] = {
	MODE_NORMAL,
	0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0x00, 0x00, 0xFF,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0xFF, 0xFF, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0xFF, 0x77, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00
};

static const unsigned char night[kSize] = {
	MODE_NORMAL,
	0xFF, 0x33, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0xFF, 0x33, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0xFF, 0x10, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00
};

static const unsigned char work[kSize] = {
	MODE_NORMAL,
	0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00,

	0xFF, 0x55, 0x44,
	0x00, 0x00, 0x00,
	0x00, 0x00, 0x00
};

static const unsigned char sea[kSize] = {
	MODE_WAVE,
	0x00, 0x00, 0xFF,
	0x00, 0xFF, 0x77,
	0x03, 0x03, 0x03,

	0x00, 0x00, 0xFF,
	0x00, 0xFF, 0x77,
	0x03, 0x03, 0x03,

	0x00, 0x00, 0xFF,
	0x00, 0xFF, 0x77,
	0x03, 0x03, 0x03,

	0x00, 0x00, 0x00,
	0x00, 0xFF, 0x77,
	0x03, 0x03, 0x03,

	0x00, 0x00, 0x00,
	0x00, 0xFF, 0x77,
	0x03, 0x03, 0x03,

	0x00, 0x00, 0x00,
	0x00, 0xFF, 0x77,
	0x03, 0x03, 0x03,

	0x00, 0x00, 0x00,
	0x00, 0xFF, 0x77,
	0x03, 0x03, 0x03
};

static const unsigned char magma[kSize] = {
	MODE_WAVE,
	0xFF, 0x77, 0x00,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0x77, 0x00,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0x77, 0x00,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0x00, 0x00, 0x00,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0x00, 0x00, 0x00,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0x00, 0x00, 0x00,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0x00, 0x00, 0x00,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03
};

static const unsigned char alien[kSize] = {
	MODE_BREATHING,
	0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03
};

static const unsigned char dragon[kSize] = {
	MODE_BREATHING,
	0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00,
	0x03, 0x03, 0x03
};

static const unsigned char heavenhell[kSize] = {
	MODE_DUAL,
	0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03,

	0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00,
	0x03, 0x03, 0x03
};
