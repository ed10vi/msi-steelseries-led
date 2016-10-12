# MSI SteelSeries LED

Control Keyboard backlight in MSI laptops with Steelseries Engine 3 Keyboards.

This software has been tested only in a MSI GT72VR 6RD Dominator.

## Installation
### Prerequisites
- Build dependencies: `build-essential libhidapi-dev`
- Run dependencies: `libhidapi-libusb0`

### Install
- Build the source: `make`
- Install: `sudo make install`
- Reboot

### Uninstall
- Uninstall: `sudo make uninstall`

## Usage

`$ msi-steelseries-led [options]`

**Options:**

| Short | Long | Description |
| ----- | ---- | ----------- |
| `-p` | `--preset` | Set one of this presets: `default`, `night`, `work`, `sea`, `magma`, `alien`, `dragon` and `heavenhell`. |
| `-m` | `--mode` | Set mode: normal, gaming, breathing, wave, dual. |
| `-l` | `--left` | Set colour for left area (se bellow for available colours). |
| `-c` | `--center` | Set colour for center area. |
| `-r` | `--right` | Set colour for right area. |
| `-g` | `--logo` | Set colour for the SteelSeries logo. |
| `-i` | `--front-left` | Set colour for front left area. |
| `-d` | `--front-right` | Set colour for front right area. |
| `-t` | `--touchpad` | Set colour for the touchpad. |
| `-h` | `--help` | This help. |

**Available colours:**
	black, white, red, green, blue, cyan, magenta, yellow, orange and teal.
	Or any colour by its hexadecimal code.
	Black if not defined.

**Set a color:** `primary[:secondary][:hex speed]`

**Modes:**

| Mode | Type | Description |
| ---- | ---- | ----------- |
| `normal` | Static | Only take effect primary colour. |
| `gaming` | Static | Turns on left area with the primary colour. |
| `breathing` | Dynamic | Transition between primary colour and black. (you can set a secondary colour different from black, but for that is better to use dual mode). |
| `wave` | Dynamic | Wave in the keyboard between primary and secondary colour. For touchpad and front only take effect secondary colour. |
| `dual` | Dynamic | Transition between primary and secondary colour. |

All options accepts `random`.

**Example:**
	`$ msi-steelseries-led -m breathing -l random:00ff00:010305 -c white:teal -r 02AF42`
