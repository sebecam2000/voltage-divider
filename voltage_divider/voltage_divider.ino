int analogPin = 3;
int resSwitch = 12;

int val = 0;                           // variable to store the value read
float volt = 0.0;
float valR1 = 0.0;
float valR2 = 0.0;

float valUt = 4.92;                    // exact value of the 5V on the board
float R2Hmes = 100000.0 + 100.0;       // measured values of R
float R2Lmes = 100.0 + 35.0;           // add internal resistor value

void setup() {
  Serial.begin(9600);                  //  setup serial
  while (!Serial);
  
  pinMode(resSwitch, INPUT);
  valR2 = 100100.0;

}

void loop() {
  int valid = 0;
  float prevValR1 = 0.0;
  
  // get 3 identical consecutive values to validate the measure
  while (valid <= 3) {
    val = analogRead(analogPin);         // read the input pin
    volt = val * valUt / 1023.0 ;        // convert to Volts
    //Serial.print(volt, 3);               // display on Serial with 3 decimals precision
    //Serial.println(" V");
    Serial.print(valR2);
    Serial.println(" = R2");
    valR1 = (float)valR2 * (valUt - volt) / volt;    // calculate R1 value
    
    if (valR1 == prevValR1) {            // check if identical to previous value
      valid++;
    } else {
      valid = 0;
    }
    prevValR1 = valR1;
    delay(250);
  }
  
  if (valR1 < 2350 && valR2 > 50000.0) {                    // check if R1 is inside the "precision" zone
    Serial.println(" use lower R2");
    pinMode(resSwitch, OUTPUT);
    analogWrite(resSwitch, LOW);
    valR2 = R2Lmes;
  } else if (valR1 > 2350 && valR2 < 50000.0) {
    Serial.println(" use higher R2");
    pinMode(resSwitch, INPUT);
    valR2 = R2Hmes;
  } else {
    Serial.print(valR1);
    Serial.println(" Ohms");
  }
  
  //delay(1000);
}
