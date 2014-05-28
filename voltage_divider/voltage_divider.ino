int analogPin = 3;
int val = 0;                           // variable to store the value read
float volt = 0.0;

void setup() {
  Serial.begin(9600);                  //  setup serial
  while (!Serial);
}

void loop() {
  val = analogRead(analogPin);         // read the input pin
  volt = (float)val * 5.0 / 1023.0 ;   // convert to Volts
  Serial.print(volt, 3);               // display on Serial with 3 decimals precision
  Serial.println(" V");
  delay(250);
}
