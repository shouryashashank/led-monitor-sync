# LED Monitor Sync
This project demonstrates how to build a monitor sync ambient light system using an Arduino, WS2812B LED strip, and Prismatik software. The system synchronizes the colors of the LED strip with the colors displayed on your monitor, creating an immersive lighting experience.

## Media
<img src="https://github.com/user-attachments/assets/15a042a9-b362-4695-aea5-289d7082f8a4" height="350px" />

[Video Demonstration](https://photos.app.goo.gl/R8GosLrnR3qGENdPA)

## Components
- Arduino (e.g., Arduino Uno)
- WS2812B LED strip
- Prismatik software
- USB cable
- Power supply for the LED strip

## Files
- `ADALIGHT_WS2812.ino`: Arduino code to control the WS2812B LED strip using the Adalight protocol.
- `CORNER_SHIFT.py`: Python script to adjust LED positions.
- `SHOURYA_LIGHTPACK_PROFILE_DYNMIC_WHITEBALANCE.ini`: Configuration file for Prismatik.
- `README.md`: Project documentation.

## Setup
### Hardware Setup:
1. Connect the WS2812B LED strip to the Arduino. Connect the data pin of the LED strip to pin 3 of the Arduino.
2. Provide power to the LED strip according to its specifications.
3. Connect the Arduino to your computer using a USB cable.

### Software Setup:
1. Install the FastLED library in the Arduino IDE.
2. Upload the `ADALIGHT_WS2812.ino` code to the Arduino.
3. Install the Prismatik software on your computer.
4. Configure Prismatik to use the Adalight protocol and set the correct COM port for your Arduino.

## Working
### Arduino Code:
- The Arduino code initializes the WS2812B LED strip and sets up the serial communication with the computer.
- It waits for the "Magic Word" from Prismatik to start receiving LED color data.
- The received data is used to update the colors of the LEDs on the strip.

### Prismatik Software:
- Prismatik captures the colors displayed on your monitor.
- It sends the color data to the Arduino using the Adalight protocol.
- The Arduino updates the LED strip to match the colors on the monitor.

### Python Script:
- The `CORNER_SHIFT.py` script can be used to adjust the positions of the LEDs if needed.
- It reads the LED configuration from a file, applies the shift, and writes the updated configuration back to the file.

## Usage
1. Start Prismatik and configure it to use the Adalight protocol.
2. Ensure the Arduino is connected and the correct COM port is selected in Prismatik.
3. Run the Python script if you need to adjust the LED positions.
4. Enjoy the synchronized ambient lighting as you use your monitor.

## Resources
- [Prismatik Software](https://github.com/psieg/Lightpack/releases)
- [FastLED Library](https://github.com/FastLED/FastLED)
- [Adalight Protocol](https://github.com/adafruit/Adalight)

## License
This project is open-source and available under the AGPL License. Feel free to contribute and improve the project.

Enjoy your immersive lighting experience! If you have any questions or issues, please refer to the resources or open an issue on the project's GitHub page.
