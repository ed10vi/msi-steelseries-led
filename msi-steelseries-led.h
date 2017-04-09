/* Lights modes */
#define MODE_OFF	0x00
#define MODE_NORMAL	0x01
#define MODE_GAMING	0x02 //The same as normal
#define MODE_BREATHING	0x03
#define MODE_AUDIO	0x04
#define MODE_WAVE	0x05
#define MODE_DUAL	0x06 //The same as breathing

#define CODE_STATIC	0x40
#define CODE_DYNAMIC	0x44

/* Flags */
#define FLAG_PRESET		0b0000000000000001
#define FLAG_MODE		0b0000000000000010
#define FLAG_LEFT		0b0000000000000100
#define FLAG_CENTER		0b0000000000001000
#define FLAG_RIGHT		0b0000000000010000
#define FLAG_LOGO		0b0000000000100000
#define FLAG_FRONT_LEFT		0b0000000001000000
#define FLAG_FRONT_RIGHT	0b0000000010000000
#define FLAG_TOUCHPAD		0b0000000100000000
#define FLAG_NO_SAVE		0b0000001000000000

#define SEPARATOR	":"

/* enum for array param values positions */
enum values {
	kMode,

	colourLeft1R,
	colourLeft1G,
	colourLeft1B,
	colourLeft2R,
	colourLeft2G,
	colourLeft2B,
	speedLeftR,
	speedLeftG,
	speedLeftB,

	colourCenter1R,
	colourCenter1G,
	colourCenter1B,
	colourCenter2R,
	colourCenter2G,
	colourCenter2B,
	speedCenterR,
	speedCenterG,
	speedCenterB,

	colourRight1R,
	colourRight1G,
	colourRight1B,
	colourRight2R,
	colourRight2G,
	colourRight2B,
	speedRightR,
	speedRightG,
	speedRightB,
#ifndef E2
	colourLogo1R,
	colourLogo1G,
	colourLogo1B,
	colourLogo2R,
	colourLogo2G,
	colourLogo2B,
	speedLogoR,
	speedLogoG,
	speedLogoB,

	colourFrontLeft1R,
	colourFrontLeft1G,
	colourFrontLeft1B,
	colourFrontLeft2R,
	colourFrontLeft2G,
	colourFrontLeft2B,
	speedFrontLeftR,
	speedFrontLeftG,
	speedFrontLeftB,

	colourFrontRight1R,
	colourFrontRight1G,
	colourFrontRight1B,
	colourFrontRight2R,
	colourFrontRight2G,
	colourFrontRight2B,
	speedFrontRightR,
	speedFrontRightG,
	speedFrontRightB,

	colourTouchpad1R,
	colourTouchpad1G,
	colourTouchpad1B,
	colourTouchpad2R,
	colourTouchpad2G,
	colourTouchpad2B,
	speedTouchpadR,
	speedTouchpadG,
	speedTouchpadB,
#endif
	kSize
};
