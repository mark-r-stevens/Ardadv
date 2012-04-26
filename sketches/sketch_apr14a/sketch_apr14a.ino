#include <ros.h>
#include <rosserial_arduino/Adc.h>

rosserial_arduino::Adc adc_msg;
ros::NodeHandle nh;
ros::Publisher p("adc", &adc_msg);

void setup()
{ 
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.advertise(p);
}
void loop()
{
  adc_msg.adc0 = analogRead(0);
  adc_msg.adc1 = analogRead(1);
  adc_msg.adc2 = analogRead(2);
  adc_msg.adc3 = analogRead(3);
  adc_msg.adc4 = analogRead(4);
  adc_msg.adc5 = analogRead(5);
  p.publish(&adc_msg);
  nh.spinOnce();
}

