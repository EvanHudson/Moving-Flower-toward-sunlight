README for Servo-controlled Light Display

This Arduino sketch controls a servo motor and an LED light display based on input from a Light Dependent Resistor (LDR) sensor and a button. The servo motor moves a light source in different patterns and modes, creating a dynamic light display.
Features

    Servo Control: The sketch utilizes the Servo library to control a servo motor connected to pin 9.

    LDR Input: The LDR sensor, connected to pin A0, detects ambient light conditions. The servo's movement is influenced by the LDR value.

    Button Input: A button connected to pin 5 is used to cycle through different display modes. The button has a debounce mechanism to avoid false readings.

    LED Display: Two LEDs, one on pin 13 (green) and the other on pin 11 (red), indicate different states and modes of the display.

    Modes: The sketch includes various display modes, including slow and fast servo movements, spinning left and right, blinking, and playing musical tunes.

Setup

    Servo Connection: Connect the servo motor to pin 9.

    LDR Connection: Connect the LDR sensor to pin A0.

    Button Connection: Connect the button to pin 5.

    LED Connections: Connect LEDs to pins 13 (green) and 11 (red).

    Upload the Sketch: Upload the provided Arduino sketch to your Arduino board.

    Monitor Serial Output: Open the Serial Monitor at 9600 baud to view the LDR values and modes.

Usage

    Power On: Once powered on, the LEDs will blink as part of the initialization process.

    Modes: Press the button to cycle through different display modes. Each mode is associated with a unique light pattern and servo movement.

    LDR Value: The current LDR value is displayed in the Serial Monitor. The servo movement and LED patterns are influenced by the ambient light conditions.

    Resting State: If the LDR value exceeds 300, indicating a well-lit environment, the display enters a resting state.

Display Modes

The display has various modes, including regular blinking, slow and fast servo movements, spinning left and right, and playing musical tunes. Each mode is indicated by different LED patterns and servo movements.
Notes

    Debounce: The button has a debounce mechanism to prevent false readings.

    Resting State: If the ambient light is above a certain threshold, the display enters a resting state, turning off the LEDs.

    Servo Movement: The servo moves in different patterns and speeds based on the selected mode.

    Musical Tunes: Some modes play musical tunes using the playSong function.

Contributions

Feel free to contribute by improving the existing code, adding new modes, or enhancing the documentation. Create pull requests or open issues to discuss potential changes.
