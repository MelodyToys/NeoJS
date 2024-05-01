// Use appropriate names for functions, in this case 'setup' and 'loop' are used as they are reserved names in Arduino.
void initializeSystem() {
  Serial.begin(9600); // Initialize the serial communication with a baud rate of 9600.
  Serial.println("Hello World");
}

void runSystem() {
  // Do nothing in this example, but you can add your code here to be executed repeatedly.
}

void setup() {
  // Call the initialization function.
  initializeSystem();
}

void loop() {
  // Call the runSystem function.
  runSystem();
}
