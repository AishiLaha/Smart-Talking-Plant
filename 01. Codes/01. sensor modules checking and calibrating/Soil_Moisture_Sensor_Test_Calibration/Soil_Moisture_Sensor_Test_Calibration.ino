/*  My Smart Talking Plant v1.0
 *  20-12-2017
 *  Arduino UNO code to Test and Calibrate the Soil Moisture Sensor Module
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  // reading and printing the analog values recieved from the sensor to the Terminal
  Serial.println(analogRead(A0));
  delay(100);
}
