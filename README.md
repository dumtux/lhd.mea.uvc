# UVC Sterilizer

## Downloading firmware to the board.

Install [MSPDebug](https://github.com/dlbeer/mspdebug).

```sh
sudo apt install mspdebug
```

Plug the board to the computer via USB cable.
Download the firmware to the board.

```sh
mspdebug rom-bsl -d /dev/ttyUSB0 "prog firmware/meauvc/meauvc.ino.MSP-EXP430G2ET2553LP.hex"
```

After finished, unplug the USB cable, and replug it in a few seconds. Then the MCU will be reset and start with the newly downloaded firmware.

For Windows, use the prebuilt binary of [MSPTool](https://github.com/upsidedownlabs/msptool).
