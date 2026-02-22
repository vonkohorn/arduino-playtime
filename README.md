# arduino-playtime

Arduino sketches for various sensors, devices, and applications — a personal playground for experimenting with the Arduino ecosystem.

The home automation, autopilot flight stabilizer, and joystick controller are meant to be customizable.

Most of these applications run on the Nano, but some are for the Mega and for the Yun.

Some of the GPS applications do not work and have been abandoned.

Let me know if you need hardware schematics for anything.

---

## Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) (1.8.x or 2.x)
- Arduino board (Nano, Mega, or Yun depending on the sketch)
- Required hardware components (sensors, servos, etc.) — see individual sketch comments for details
- Any third-party libraries referenced in a sketch should be installed via the Arduino Library Manager or placed in the `libraries/` folder

## Building and Uploading a Sketch

1. Open the desired sketch folder in the Arduino IDE (e.g., `oled_servo_pot/`).
2. Select the correct board under **Tools → Board**.
3. Select the correct port under **Tools → Port**.
4. Click **Upload** (▶) to compile and flash the sketch.

## Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) before opening a pull request.

## License

This project is licensed under the [MIT License](LICENSE).  
Copyright (c) 2017-2026 vonkohorn
