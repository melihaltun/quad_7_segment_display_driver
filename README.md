# quad_7_segment_display_driver
Arduino code to drive a common cathode quad 7 segment display

This code drives a 7 segment quad display with common cathodes. The code contains an int numDisp array with 4 elements that will be shown on the 7 segment quad display. Each element of the array is displayed on a separate digit. To do that, each digit is sinked separately and they are modulated so that only one digit is shown at a time. However, with a very short delay and the persistance of vision, it will appear as if all 4 digits are shown simultaneously.  

The code is arranged to increment digits every second in a [mm:ss] clock format. However, it can be modified to show any 4 digit on display.

The setup requires an Arduino Uno, a common cathode quad 7 segment display, an 8 bit shift register with serial input, parallel output (74HC595), and four current limiting resistors (270 or 330 ohms)

A shift register is useful because it frees digital pins. Othervise this setup would use up 12 digital pins: 8 as source (7 segments + decimal dot) and 4 as sink pins. This configuration needs 7 pins. Also the LED's will be driven by the output pins of the shift register instead of Arduino's pins. 

The digits are serialized and send to the shift register. The register works as a deserializer and drives the 7 segment leds with its parralel outputs.

Ardunio digital I/O pins can sink at most 20mA. Therefore, current limiting resistors less than 270 ohms are not recommeded. 

The schematic is show below:

![image](https://user-images.githubusercontent.com/40482921/236323852-a0725c56-1f36-4cba-8198-01162e7fbde9.png)

