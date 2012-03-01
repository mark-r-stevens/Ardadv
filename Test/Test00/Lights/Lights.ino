// Demonstration of using LED and pushbuttons on an Arduino UNO
//
// Copyright (C) 2012 Mark R. Stevens
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#define LedPinR 10
#define LedPinG 11
#define LedPinY 12

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(LedPinR, OUTPUT);     
  pinMode(LedPinG, OUTPUT);     
  pinMode(LedPinY, OUTPUT);     
}

void loop() {
  digitalWrite(LedPinG, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(LedPinG, LOW);    // set the LED off
  delay(1000);              // wait for a second

  digitalWrite(LedPinY, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(LedPinY, LOW);    // set the LED off
  delay(1000);              // wait for a second

  digitalWrite(LedPinR, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(LedPinR, LOW);    // set the LED off
  delay(1000);              // wait for a second

}
