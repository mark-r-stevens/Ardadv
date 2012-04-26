
// Simple encoder test
//
#include <AFMotor.h>

#include <avr/io.h>
#include <avr/interrupt.h>

AF_DCMotor motor1(1); // create motor #2, 64KHz pwm
AF_DCMotor motor2(2); // create motor #2, 64KHz pwm

static char global_m1a = 0;
static char global_m2a = 0;

static int global_counts_m1 = 0;
static int global_counts_m2 = 0;

static char global_error_m1 = 0;
static char global_error_m2 = 0;

static char global_last_m1a_val = 0;
static char global_last_m2a_val = 0;

inline uint8_t get_val(uint8_t pin)
{
  if (pin == 50)
  {
    return (PINB >> 3) & 1;
  }
  else if(pin == 51)
  {
    return (PINB >> 2) & 1;
  }
  return 0;
}

ISR(PCINT0_vect)
{
	unsigned char m1a_val = get_val(50);
	unsigned char m2a_val = get_val(51);

	char plus_m1 = m1a_val ^ global_last_m1a_val;
	char plus_m2 = m2a_val ^ global_last_m2a_val;

	if(plus_m1)
		global_counts_m1 += 1;
	if(plus_m2)
		global_counts_m2 += 1;

	if(m1a_val != global_last_m1a_val)
		global_error_m1 = 1;
	if(m2a_val != global_last_m2a_val)
		global_error_m2 = 1;

	global_last_m1a_val = m1a_val;
	global_last_m2a_val = m2a_val;
}

ISR(PCINT1_vect,ISR_ALIASOF(PCINT0_vect));
ISR(PCINT2_vect,ISR_ALIASOF(PCINT0_vect));

int getCountsAndResetM1()
{
	noInterrupts();
	const int tmp = global_counts_m1;
	global_counts_m1 = 0;
	interrupts();
	return tmp;
}

int getCountsAndResetM2()
{
	noInterrupts();
	const int tmp = global_counts_m2;
	global_counts_m2 = 0;
	interrupts();
	return tmp;
}
void setup()
{
  Serial.begin(9600);                           
  motor1.setSpeed(200);    
  motor2.setSpeed(200);    
  
  ::pinMode(21, INPUT);
  ::pinMode(20, INPUT);
  ::digitalWrite(21, HIGH);
  ::digitalWrite(20, HIGH);
  
  // Prevent interrupts while initializing
  //
  noInterrupts();
  
  // Pin 50 for left wheel
  //
  PCICR |= 1 << PCIE0;
  DDRB &= ~(1 << (3));
  PCMSK0 |= 1 << (3);
   
   // Pin 50 for right wheel
   //
   PCICR |= 1 << PCIE0;
   DDRB &= ~(1 << (2));
   PCMSK0 |= 1 << (2);
    
   // Clear the interrupt flags in case they were set before for any reason.
   // On the AVR, interrupt flags are cleared by writing a logical 1
   // to them.
   //
   PCIFR |= (1 << PCIF0) | (1 << PCIF1) | (1 << PCIF2);
  
   // reenable interrupts
   //
   interrupts();
}

void logger()
{
    Serial.print("left=");
    Serial.print(getCountsAndResetM1());
    Serial.print(" right=");
    Serial.println(getCountsAndResetM2());
}

void loop()
{
  
  motor2.run(FORWARD);    ::delay(1000);
  motor2.run(RELEASE);    ::delay(2000);
  
  logger();
  
  motor1.run(FORWARD);     
  delay(1000);
 
  motor1.run(RELEASE);    
  delay(2000);

  logger();
}


