/* 

Made by Thomas Ouellet Fredericks
Comments and questions: tof@danslchamp.org
Use as you like.
Orignal version: 27th of June 2006.
Approximative library size: 500 bytes.


SimpleMessageSystem is a library for Arduino. It facilitates communication with terminals 
or message based programs like Pure Data or Max/Msp.

*/


#ifndef SimpleMessageSystem_h
#define SimpleMessageSystem_h



// ---- FUNCTIONS ----
	
	// RECEIVING
	// If the message has been terminated, returns the size of the message including spaces.
	// WARNING: if you make a call to messageBuild() it will discard any previous message!
	int messageBuild();
	
	// If a word is available, returns it as a char. If no word is available it will return 0.
	// WARNING: if you send something like "foo", it will return 'f' and discard "oo".
	char messageGetChar();
	
	// If a word is available, returns it as an integer. If no word is available it will return 0.
	 int messageGetInt();
	 
	// SENDING
	// Send a character, prepend a space if it the second element sent.
	 void messageSendChar(char value);
	
	// Send an integer, prepend a space if it the second element sent.
	 void messageSendInt(int value);
	
	// Terminate the message to signal the target that the message can be processed.
	 void messageEnd();
	

#endif



