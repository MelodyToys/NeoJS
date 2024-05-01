// Use appropriate names for functions, in this case 'setup' and 'loop' are used as they are reserved keywords in Arduino IDE
void setup() {
  Serial.begin(9600); // Initialize the serial communication with a baud rate of 9600
  Serial.println("Hello World"); // Print the message to the serial monitor
}

void loop() {
  // Add any code that needs to be executed repeatedly in the loop
  // For now, the loop is empty. You can add your code inside this function
}

/*
Commented out the complex ASCII art as it is unnecessary and makes the code hard to read
If you still want to include it, consider moving it to a separate file or using a tool to generate it
*/
