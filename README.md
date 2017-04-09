# MSI SteelSeries LED

Control Keyboard backlight in MSI laptops with Steelseries Engine 3 and 2 Keyboards.

This software has been tested only in a MSI GT72VR 6RD Dominator and a MSI GE70 2PE ApachePro.

#### Thanks to
- https://github.com/gokuhs/MSI-Keyboard-Led-Enabler
- https://github.com/PaNaVTEC/MSI_GT_GE_Led_Enabler

## Installation
### Prerequisites
- Build dependencies: `build-essential libhidapi-dev`
- Run dependencies: `libhidapi-libusb0`

### Install
- Build the source: `make` (for Steelseries Engine 2: `make msi-steelseries-led-E2`)
- Install: `sudo make install`
- Reboot so udev rules take effect.

### Uninstall
- Uninstall: `sudo make uninstall`

## Usage

`$ msi-steelseries-led [options]`

**Options:**

| Short | Long | Description |
| ----- | ---- | ----------- |
| `-p` | `--preset` | Set one of this presets: `default`, `night`, `work`, `sea`, `magma`, `alien`, `dragon` and `heavenhell`. |
| `-m` | `--mode` | Set mode: `normal`, `gaming`, `breathing`, `wave`, `dual` (and `audio`, but it's not working). |
| `-l` | `--left` | Set colour for left area (se bellow for available colours). |
| `-c` | `--center` | Set colour for center area. |
| `-r` | `--right` | Set colour for right area. |
| `-g` | `--logo` | Set colour for the SteelSeries logo. |
| `-i` | `--front-left` | Set colour for front left area. |
| `-d` | `--front-right` | Set colour for front right area. |
| `-t` | `--touchpad` | Set colour for the touchpad. |
| `-h` | `--help` | This help. |

**Available colours:**
	`black`, `white`, `red`, `green`, `blue`, `cyan`, `magenta`, `yellow`, `orange` and `teal`.
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

## Protocol

Using USBPcap in Windows, I managed to capture the data sent by the official client from SteelSeries.

Analyzing the data with Wireshark this is what I got on Engine 3:

**Mode normal** (similar for all static modes)
```
01 02 41 09 00 00 00 00
01 02 40 01 RR GG BB 00 // Left area
01 02 40 02 RR GG BB 00 // Center area
01 02 40 03 RR GG BB 00 // Right area
01 02 40 04 RR GG BB 00 // Logo area
01 02 40 05 RR GG BB 00 // Front left area
01 02 40 06 RR GG BB 00 // Front right area
01 02 40 07 RR GG BB 00 // Touchpad area
01 02 41 01 00 00 00 00 // Set mode
```

**Mode breathing** (similar for all dynamic modes)
```
01 02 41 09 00 00 00 00
01 02 44 01 RR GG BB 00 // Left area primary
01 02 44 02 RR GG BB 00 // Left area secondary
01 02 44 03 SR SG SB 00 // Left area speed
01 02 44 04 RR GG BB 00 // Center area primary
01 02 44 05 RR GG BB 00 // Center area secondary
01 02 44 06 SR SG SB 00 // Center area speed
01 02 44 07 RR GG BB 00 // Right area primary
01 02 44 08 RR GG BB 00 // Right area secondary
01 02 44 09 SR SG SB 00 // Right area speed
01 02 44 0A RR GG BB 00 // Logo area primary
01 02 44 0B RR GG BB 00 // Logo area secondary
01 02 44 0C SR SG SB 00 // Logo area speed
01 02 44 0D RR GG BB 00 // Front left area primary
01 02 44 0E RR GG BB 00 // Front left area secondary
01 02 44 0F SR SG SB 00 // Front left area speed
01 02 44 10 RR GG BB 00 // Front right area primary
01 02 44 11 RR GG BB 00 // Front right area secondary
01 02 44 12 SR SG SB 00 // Front right area speed
01 02 44 13 RR GG BB 00 // Touchpad area primary
01 02 44 14 RR GG BB 00 // Touchpad area secondary
01 02 44 15 SR SG SB 00 // Touchpad area speed
01 02 41 03 00 00 00 00 // Set mode
```


this is what I got on Engine 2:

**Mode normal** (similar for all static modes)
```
01 02 41 01 00 00 00 00 // Set mode
01 02 40 01 RR GG BB 00 // Left area
01 02 40 02 RR GG BB 00 // Center area
01 02 40 03 RR GG BB 00 // Right area
```

**Mode breathing** (similar for all dynamic modes)
```
01 02 44 01 RR GG BB 00 // Left area primary
01 02 44 02 RR GG BB 00 // Left area secondary
01 02 44 03 SR SG SB 00 // Left area speed
01 02 44 04 RR GG BB 00 // Center area primary
01 02 44 05 RR GG BB 00 // Center area secondary
01 02 44 06 SR SG SB 00 // Center area speed
01 02 44 07 RR GG BB 00 // Right area primary
01 02 44 08 RR GG BB 00 // Right area secondary
01 02 44 09 SR SG SB 00 // Right area speed
01 02 41 03 00 00 00 00 // Set mode
```
