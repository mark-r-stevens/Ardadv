/*
 * RoombaBumpTurn 
 * --------------
 * Implement the RoombaComm BumpTurn program in Arduino
 * A simple algorithm that allows the Roomba to drive around 
 * and avoid obstacles.
 * 
 * Arduino pin 0 (RX) is connected to Roomba TXD
 * Arduino pin 1 (TX) is connected to Roomba RXD
 * Arduino pin 2      is conencted to Roomba DD
 * 
 * Updated 20 November 2006
 * - changed Serial.prints() to use single print(v,BYTE) calls instead of 
 *    character arrays until Arduino settles on a style of raw byte arrays
 *
 * Created 1 August 2006
 * copyleft 2006 Tod E. Kurt <tod@todbot.com>
 * http://hackingroomba.com/
 */

int ddPin = 2;

void setup() 
{
   Serial.begin(9600);
  Serial.flush();

  // Roomba operates at a default baud rate of 57600
  //
  Serial3.begin(57600);

  // wake up the robot
  pinMode(ddPin,  OUTPUT);   // sets the pins as output
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  delay(2000);
  
  // Start Command opcode: 128 Number of data bytes: 0
  // Starts the SCI. The Start command must be sent before 
  // any other SCI commands. This command puts the SCI in
  //  passive mode.
  //
  serialWrite(128); 
  delay(100);
  
  // Control Command opcode: 130 Number of data bytes: 0
  // Enables user control of Roomba. This command must be 
  // sent after the start command and before any control 
  // commands are sent to the SCI. The SCI must be in passive 
  // mode to accept this command. This command puts the SCI in 
  // safe mode.
  //
  serialWrite(130);  
  delay(100);
  
  // Full Command opcode: 132 Number of data bytes: 0
  // Enables unrestricted control of Roomba through the SCI 
  // and turns off the safety features. The SCI must be in 
  // safe mode to accept this command. This command puts the 
  // SCI in full mode.
  //
  serialWrite(132);  
  delay(100);
}

void loop() 
{
  Serial.println("goForward");
  goForward();
  delay(1000);
}

void serialWrite(uint8_t value)
{
  Serial3.write(value);
}
void goForward() 
{
  // Drive Command opcode: 137 Number of data bytes: 4
  // Controls Roomba’s drive wheels. The command takes
  // four data bytes, which are interpreted as two 16 bit 
  // signed values using twos-complement. The first two 
  // bytes specify the average velocity of the drive wheels 
  // in millimeters per second (mm/s), with the high byte 
  // sent first. The next two bytes specify the radius, in 
  // millimeters, at which Roomba should turn. The longer 
  // radii make Roomba drive straighter; shorter radii make 
  // it turn more. A Drive command with a positive velocity 
  // and a positive radius will make Roomba drive forward 
  // while turning toward the left. A negative radius will 
  // make it turn toward the right. Special cases for the 
  // radius make Roomba turn in place or drive straight,
  //  as specified below. The SCI must be in safe or full 
  // mode to accept this command. This command does change 
  // the mode.
  //
  serialWrite(137);   // DRIVE
  serialWrite(0x00);   // 0x00c8 == 200
  serialWrite(0xc8);
  serialWrite(0x80);
  serialWrite(0x00);
}

