# ESP32 Piano

This project allows you to create a simple piano using an ESP32 microcontroller and a buzzer. The ESP32 acts as a Wi-Fi hotspot, providing a web interface to play musical notes by clicking on virtual piano keys.

## Features

- **Wi-Fi Hotspot**: The ESP32 creates a Wi-Fi hotspot named "ESP32Piano" with the password "playmusic".
- **Web Interface**: A responsive web interface that simulates a piano keyboard with 25 keys (C4 to C6).
- **Note Playback**: Each key plays a specific musical note when clicked.

## Components Required

- ESP32 development board
- Buzzer
- Jumper wires (if needed)

## Wiring

Connect the buzzer to pin 14 of the ESP32. You can connect the other terminal of the buzzer to the ground.

## Code Explanation

The code includes the following key components:

1. **Wi-Fi Configuration**: 
   - The ESP32 is set up to create a Wi-Fi access point with specified SSID and password.
   
2. **Web Server**: 
   - A web server is initialized on port 80. It serves the piano interface and handles note playback requests.

3. **HTML/CSS for Web Interface**: 
   - The web interface is designed with HTML and CSS, providing visual representation of the piano keys.
   
4. **Tone Generation**: 
   - The buzzer plays specific frequencies corresponding to the musical notes using the `tone()` function.

## How to Use

1. Upload the code to your ESP32 using the Arduino IDE or PlatformIO.
2. Connect to the Wi-Fi network named "ESP32Piano" with the password "playmusic".
3. Open a web browser and navigate to `http://192.168.4.1`.
4. Click on the piano keys to play different notes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by various online resources and tutorials on ESP32 and Arduino projects.
