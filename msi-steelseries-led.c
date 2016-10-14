/*
 * This software has been developed with USBpcap intercepting the data from SteelSeries Engine 3 in a MSI GT72VR 6RD
 *
 * Eduardo Diez Viñuela
 * 2016-03-30
 */

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <hidapi/hidapi.h>
#include <time.h>

#include "msi-steelseries-led.h"
#include "presets.h"

void send_data(hid_device *handle, unsigned char code, unsigned char index, unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char data[8];

	data[0] = 0x01;
	data[1] = 0x02;
	data[2] = code;
	data[3] = index;
	data[4] = r;
	data[5] = g;
	data[6] = b;
	data[7] = 0x00;

	if (hid_send_feature_report(handle, data, 9) < 0)
		printf("Unable to send a feature report.\n");
}

void send_mode(hid_device *handle, unsigned char mode)
{
	unsigned char commit[8];

	commit[0] = 0x01;
	commit[1] = 0x02;
	commit[2] = 0x41;
	commit[3] = mode;
	commit[4] = 0x00;
	commit[5] = 0x00;
	commit[6] = 0x00;
	commit[7] = 0x00;

	if (hid_send_feature_report(handle, commit, 9) < 0)
		printf("Unable to send a feature report.\n");
}

void mode_normal(hid_device *handle, unsigned char message[kSize])
{
	send_mode(handle, 0x09);

	for (unsigned char i = 1; i < kSize; i += 9)
		send_data(handle, CODE_STATIC, (i / 9) + 1, message[i], message[i + 1], message[i + 2]);

	send_mode(handle, MODE_NORMAL);
}
/*
 * Exactly the same as normal, but only sets left area
 * Still works if sets all the areas
 */
void mode_gaming(hid_device *handle, unsigned char message[kSize])
{
	send_mode(handle, 0x09);
	send_data(handle, CODE_STATIC, 1, message[colourLeft1R], message[colourLeft1G], message[colourLeft1B]); // left
	send_mode(handle, MODE_GAMING);
}

void mode_animated(hid_device *handle, unsigned char message[kSize])
{
	send_mode(handle, 0x09);

	for (unsigned char i = 1; i < kSize; i += 3)
		send_data(handle, CODE_DYNAMIC, (i / 3) + 1, message[i], message[i + 1], message[i + 2]);

	send_mode(handle, message[kMode]);
}

void mode_audio(hid_device *handle)
{
	send_mode(handle, 0x09);
	send_mode(handle, MODE_AUDIO);
}

void save(unsigned char message[kSize], char *path, char *filename)
{
	FILE *file;
	char *filepath = malloc(strlen(path) + strlen(filename) + 1);

	strcpy(filepath, path);
	strcat(filepath, filename);

	if (access(filepath, W_OK) == 0 || access(path, W_OK) == 0) {
		file = fopen(filepath, "wb"); // Open the file in binary mode
		fwrite(message, kSize, 1, file); // Write in the entire file
		fclose(file); // Close the file
	}
}

int load(unsigned char *message, char *path, char *filename)
{
	FILE *file;
	char *filepath = malloc(strlen(path) + strlen(filename) + 1);
	size_t sz;

	strcpy(filepath, path);
	strcat(filepath, filename);

	if (access(filepath, R_OK) == 0) {
		file = fopen(filepath, "rb"); // Open the file in binary mode
		sz = fread(message, kSize, 1, file); // Read in the entire file
		fclose(file); // Close the file
		printf("%lu\n", sz);
		return sz == 1 ? 0 : 1;
	} else {
		return 1;
	}
}

unsigned char parse_mode(char *arg)
{
	unsigned char rd;
	if (strcmp(arg, "off") == 0)
		return MODE_OFF;
	else if (strcmp(arg, "normal") == 0)
		return MODE_NORMAL;
	else if (strcmp(arg, "gaming") == 0)
		return MODE_GAMING;
	else if (strcmp(arg, "breathing") == 0)
		return MODE_BREATHING;
	else if (strcmp(arg, "wave") == 0)
		return MODE_WAVE;
	else if (strcmp(arg, "dual") == 0)
		return MODE_DUAL;
	else if (strcmp(arg, "audio") == 0)
		return MODE_AUDIO;
	else if (strcmp(arg, "random") == 0) {
		srand(time(NULL) + rand());
		rd = rand() % 6;
		if (rd > 3)
			rd += 1;
		return rd;
	} else
		return 0xFF;
}

void parse_colour(char *arg, unsigned char colour[3])
{
	char buff[2];
	unsigned int aux;

	// basic colours
	if (strcmp(arg, "black") == 0) {
		colour[0] = 0x00;
		colour[1] = 0x00;
		colour[2] = 0x00;
	} else if (strcmp(arg, "white") == 0) {
		colour[0] = 0xFF;
		colour[1] = 0xFF;
		colour[2] = 0xFF;
	} else if (strcmp(arg, "red") == 0) {
		colour[0] = 0xFF;
		colour[1] = 0x00;
		colour[2] = 0x00;
	} else if (strcmp(arg, "green") == 0) {
		colour[0] = 0x00;
		colour[1] = 0xFF;
		colour[2] = 0x00;
	} else if (strcmp(arg, "blue") == 0) {
		colour[0] = 0x00;
		colour[1] = 0x00;
		colour[2] = 0xFF;
	} else if (strcmp(arg, "cyan") == 0) {
		colour[0] = 0x00;
		colour[1] = 0xFF;
		colour[2] = 0xFF;
	} else if (strcmp(arg, "magenta") == 0) {
		colour[0] = 0xFF;
		colour[1] = 0x00;
		colour[2] = 0xFF;
	} else if (strcmp(arg, "yellow") == 0) {
		colour[0] = 0xFF;
		colour[1] = 0xFF;
		colour[2] = 0x00;
	} else if (strcmp(arg, "orange") == 0) {
		colour[0] = 0xFF;
		colour[1] = 0x33;
		colour[2] = 0x00;
	} else if (strcmp(arg, "teal") == 0) {
		colour[0] = 0x00;
		colour[1] = 0xFF;
		colour[2] = 0x77;
	} else if (strcmp(arg, "random") == 0) {
		srand(time(NULL) + rand());
		colour[0] = rand() % 256;
		colour[1] = rand() % 256;
		colour[2] = rand() % 256;
	} else if (strlen(arg) == 6) { // HEX
		for (int i = 0; i < 3; i++) {
			buff[0] = arg[i * 2];
			buff[1] = arg[i * 2 + 1];
			sscanf(buff, "%02x", &aux);
			colour[i] = aux;
		}
	}
}

void parse_area(char *arg, unsigned char area[9])
{
	char *running;
	char *token;
	unsigned char colour[3];

	for (unsigned char i = 0; i < 6; i++)
		area[i] = 0x00;
	for (unsigned char i = 6; i < 9; i++)
		area[i] = 0x03;

	running = strdup(arg);
	token = strsep(&running, SEPARATOR);
	if (token != NULL) {
		if (strlen(token) > 2) {
			parse_colour(token, colour);
			area[0] = colour[0];
			area[1] = colour[1];
			area[2] = colour[2];
		}
		token = strsep(&running, SEPARATOR);
		if (token != NULL) {
			if (strlen(token) > 2) {
				parse_colour(token, colour);
				area[3] = colour[0];
				area[4] = colour[1];
				area[5] = colour[2];
			}
			token = strsep(&running, SEPARATOR);
			if (token != NULL && strlen(token) == 6) {
				parse_colour(token, colour);
				area[6] = colour[0];
				area[7] = colour[1];
				area[8] = colour[2];
			}
		}
	}
}

int main(int argc, char *argv[])
{
	unsigned char message[kSize];
	unsigned char area[9];
	unsigned short flags = 0;
	unsigned char preset = 0xFF;

	char *path = NULL, *filename = ".msi-steelseries-led.conf.bin";

	char *usage = "MSI SteelSeries Led\n"
	"Usage:\n"
	"%s [options]\n\n"
	"Options:\n"
	" -p preset\t\tSet one of this presets:\n\t\t\tdefault, night, work, sea, magma, alien, dragon and heavenhell.\n"
	" -m mode\t\tSet mode: normal, gaming, breathing, wave, dual.\n"
	" -l left\t\tSet colour for left area\n\t\t\t(se bellow for available colours).\n"
	" -c center\t\tSet colour for center area.\n"
	" -r right\t\tSet colour for right area.\n"
	" -g logo\t\tSet colour for the SteelSeries logo.\n"
	" -i front-left\t\tSet colour for front left area.\n"
	" -d front-right\t\tSet colour for front right area.\n"
	" -t touchpad\t\tSet colour for the touchpad.\n"
	" -h help\t\tThis help.\n\n"
	"Available colours:\n\tblack, white, red, green, blue, cyan, magenta, yellow, orange and teal.\n\tOr any colour by its hexadecimal code.\n\tBlack if not defined.\n\n"
	"Set a color: primary["SEPARATOR"secondary]["SEPARATOR"hex speed]\n\n"
	"Modes:\n"
	" normal\t\tStatic. Only take effect primary colour.\n"
	" gaming\t\tStatic. Turns on left area with the primary colour.\n"
	" breathing\tDynamic. Transition between primary colour and black\n\t\t(you can set a secondary colour different from black,\n\t\tbut for that is better to use dual mode).\n"
	" wave\t\tDynamic. Wave in the keyboard between primary and\n\t\tsecondary colour.\n\t\tFor touchpad and front only take effect secondary colour.\n"
	" dual\t\tDynamic. Transition between primary and secondary colour.\n\n"
	"All options accepts random.\n\n"
	"Example:\n\t"
	"%s -m breathing -l random:00ff00:010305 -c white:teal -r 02AF42\n\n";

	unsigned int opt = 0;
	const char *op = "p:m:l:c:r:g:i:d:t:nh";
	const struct option options[] = {
		{ "preset",		1, NULL, 'p'},
		{ "mode",		1, NULL, 'm'},
		{ "left",		1, NULL, 'l'},
		{ "center",		1, NULL, 'c'},
		{ "right",		1, NULL, 'r'},
		{ "logo",		1, NULL, 'g'},
		{ "front-left",		1, NULL, 'i'},
		{ "front-right",	1, NULL, 'd'},
		{ "touchpad",		1, NULL, 't'},
		{ "no-save",		0, NULL, 'n'},
		{ "help",		0, NULL, 'h'},
		{ NULL,			0, NULL,  0 }
	};

	hid_device *handle;

	handle = hid_open(0x1770, 0xff00, NULL);

	if (!handle) {
		perror("Unable to open MSI Led device");
		return 1;
	}

	message[kMode] = 0xFF;
	for (unsigned char i = 1; i < kSize; i += 9) {
		for (unsigned char j = 0; j < 6; j++)
			message[i + j] = 0x00;
		for (unsigned char j = 6; j < 9; j++)
			message[i + j] = 0x03;
	}

	while((opt = getopt_long(argc, (char *const *) argv, op, options, NULL)) != -1)
		switch(opt) {
			case 'p':
				if ((flags & FLAG_PRESET) == FLAG_PRESET) {
					perror("Option --preset repeated.");
					return 1;
				}
				flags |= FLAG_PRESET;

				if (strcmp(optarg, "random") == 0) {
					srand(time(NULL));
					preset = rand() % 8;
				}

				if (preset == 0 || strcmp(optarg, "default") == 0)
					for (int i = 0; i < kSize; i++)
						message[i] = defaultConf[i];
				else if (preset == 1 || strcmp(optarg, "night") == 0)
					for (int i = 0; i < kSize; i++)
						message[i] = night[i];
				else if (preset == 2 || strcmp(optarg, "work") == 0)
					for (int i = 0; i < kSize; i++)
						message[i] = work[i];
				else if (preset == 3 || strcmp(optarg, "sea") == 0)
					for (int i = 0; i < kSize; i++)
						message[i] = sea[i];
				else if (preset == 4 || strcmp(optarg, "magma") == 0)
					for (int i = 0; i < kSize; i++)
						message[i] = magma[i];
				else if (preset == 5 || strcmp(optarg, "alien") == 0)
					for (int i = 0; i < kSize; i++)
						message[i] = alien[i];
				else if (preset == 6 || strcmp(optarg, "dragon") == 0)
					for (int i = 0; i < kSize; i++)
						message[i] = dragon[i];
				else if (preset == 7 || strcmp(optarg, "heavenhell") == 0)
					for (int i = 0; i < kSize; i++)
						message[i] = heavenhell[i];
				break;
			case 'm':
				if ((flags & FLAG_MODE) == FLAG_MODE) {
					perror("Option --mode repeated.");
					return 1;
				}
				flags |= FLAG_MODE;
				message[kMode] = parse_mode(optarg);
				break;
			case 'l':
				if ((flags & FLAG_LEFT) == FLAG_LEFT) {
					perror("Option --left repeated.");
					return 1;
				}
				flags |= FLAG_LEFT;
				parse_area(optarg, area);
				for (unsigned char i = 0; i < sizeof(area); i++)
					message[i + colourLeft1R] = area[i];
				break;
			case 'c':
				if ((flags & FLAG_CENTER) == FLAG_CENTER) {
					perror("Option --center repeated.");
					return 1;
				}
				flags |= FLAG_CENTER;
				parse_area(optarg, area);
				for (unsigned char i = 0; i < sizeof(area); i++)
					message[i + colourCenter1R] = area[i];
				break;
			case 'r':
				if ((flags & FLAG_RIGHT) == FLAG_RIGHT) {
					perror("Option --right repeated.");
					return 1;
				}
				flags |= FLAG_RIGHT;
				parse_area(optarg, area);
				for (unsigned char i = 0; i < sizeof(area); i++)
					message[i + colourRight1R] = area[i];
				break;
			case 'g':
				if ((flags & FLAG_LOGO) == FLAG_LOGO) {
					perror("Option --logo repeated.");
					return 1;
				}
				flags |= FLAG_LOGO;
				parse_area(optarg, area);
				for (unsigned char i = 0; i < sizeof(area); i++)
					message[i + colourLogo1R] = area[i];
				break;
			case 'i':
				if ((flags & FLAG_FRONT_LEFT) == FLAG_FRONT_LEFT) {
					perror("Option --front-left repeated.");
					return 1;
				}
				flags |= FLAG_FRONT_LEFT;
				parse_area(optarg, area);
				for (unsigned char i = 0; i < sizeof(area); i++)
					message[i + colourFrontLeft1R] = area[i];
				break;
			case 'd':
				if ((flags & FLAG_FRONT_RIGHT) == FLAG_FRONT_RIGHT) {
					perror("Option --front-right repeated.");
					return 1;
				}
				flags |= FLAG_FRONT_RIGHT;
				parse_area(optarg, area);
				for (unsigned char i = 0; i < sizeof(area); i++)
					message[i + colourFrontRight1R] = area[i];
				break;
			case 't':
				if ((flags & FLAG_TOUCHPAD) == FLAG_TOUCHPAD) {
					perror("Option --touchpad repeated.");
					return 1;
				}
				flags |= FLAG_TOUCHPAD;
				parse_area(optarg, area);
				for (unsigned char i = 0; i < sizeof(area); i++)
					message[i + colourTouchpad1R] = area[i];
				break;
			case 'n':
				if ((flags & FLAG_NO_SAVE) == FLAG_NO_SAVE) {
					perror("Option --no-save repeated.");
					return 1;
				}
				flags |= FLAG_NO_SAVE;
				break;
			case 'h':
				printf(usage, argv[0]);
				return 0;
				break;
			default:
				printf("Config loaded. Use --help for usage instructions.");
				break;
		}

	/* If there is no data or no need to save, get the home path */
	if (message[kMode] == 0xFF || (flags & FLAG_NO_SAVE) != FLAG_NO_SAVE)
		 path = strcat(getenv("HOME"), "/");

	if (flags == 0 || flags == FLAG_NO_SAVE) {
		if (load(message, path, filename) != 0)
			for (int i = 0; i < kSize; i++)
				message[i] = defaultConf[i];
		flags |= FLAG_NO_SAVE;
	}

	if (message[kMode] == MODE_OFF)
		send_mode(handle, MODE_OFF);
	else if (message[kMode] == MODE_NORMAL)
		mode_normal(handle, message);
	else if (message[kMode] == MODE_GAMING)
		mode_gaming(handle, message);
	else if (message[kMode] == MODE_AUDIO)
		mode_audio(handle);
	else if (message[kMode] == MODE_BREATHING || message[kMode] == MODE_WAVE || message[kMode] == MODE_DUAL)
		mode_animated(handle, message);
	else {
		perror("Invalid mode.");
		return 1;
	}

	if ((flags & FLAG_NO_SAVE) != FLAG_NO_SAVE)
		save(message, path, filename);

	return 0;
}
