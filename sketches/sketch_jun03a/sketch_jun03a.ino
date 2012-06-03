
/*
JPEG Camera Example Sketch
The sketch will take a picture on the JPEG Serial Camera and store the jpeg to an SD card
on an SD Shield
Written by Ryan Owens
SparkFun Electronics

Hardware Notes:
This sketch assumes the arduino has the microSD shield from SparkFun attached.
The camera Rx/Tx should be attached to pins 2 and 3.
IMPORTANT: The JPEG camera requires a TTL level shifter between the camera output
and the arduino. Bypassing this may damage the Arduino pins.
*/

// This example requires the MemoryCard, SdFat, JPEGCamera and NewSoftSerial libraries
//
#include <JPEGCamera.h>

// Create an instance of the camera
//
JPEGCamera camera;

//Create a character array to store the cameras response to commands
//
char response[32];

void setup()
{
    // Setup the camera, serial port and memory card
    //
    camera.begin();
    
    // Set up the serial line
    //
    Serial.begin(9600);

    // Reset the camera
    //
    camera.reset(response);
    
    // Wait
    //
    delay(3000);
}

void loop()
{
  
    // Start a timer
    //
    unsigned long start = millis();
    
    // Take a picture
    //
    int count = camera.takePicture(response);
    
    // Print the response to the 'TAKE_PICTURE' command.
    //
    Serial.write(response);
    Serial.write(count);
    Serial.println();

    // Get the size of the picture
    //
    int size = 0;
    count = camera.getSize(response, &size);
    
    // Print the size
    //
    Serial.print("Size: ");
    Serial.println(size);

    // Starting at address 0, keep reading data until we've read 'size' data.
    //
    int eof = 0;
    int address = 0;
    while(address < size)
    {
        // Read the data starting at the current address.
        //
        count = camera.readData(response, address);
        
        // Do something with the data
        //
        for(int i = 0; i < count; i++)
        {
            //Check the response for the eof indicator (0xFF, 0xD9). If we find it, set the eof flag
            //
            if ((response[i] == (char)0xD9) && (response[i-1]==(char)0xFF))
            {
              eof=1;
            }
            
            //If we found the eof character, get out of this loop and stop reading data
            //
            if (eof == 1) 
            { 
              break;
            }
        }
        
        // Increment the current address by the number of bytes we read
        //
        address += count;
        
        // Make sure we stop reading data if the eof flag is set.
        //
        if (eof == 1)
        {
          break;
        }
    }

     Serial.print("Done.");
    // Wait
    //
    delay(3000);

}
