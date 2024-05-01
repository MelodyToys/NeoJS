// Use appropriate names for functions, in this case 'setup' and 'loop' are used as they are
// reserved keywords in Arduino IDE. The 'setup' function is called once when the program starts
// to initialize variables, input and output pin modes, and start using libraries.
void setup() {
  Serial.begin(9600); // Initialize the serial communication with a baud rate of 9
