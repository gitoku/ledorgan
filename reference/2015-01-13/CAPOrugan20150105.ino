#include <CapSense.h>

#define CAPSENS_OUT     4
#define CAPSENS_PIN1    18
#define CAPSENS_PIN2    17


CapSense cs_0=CapSense(CAPSENS_OUT,CAPSENS_PIN1);
CapSense cs_1=CapSense(CAPSENS_OUT,CAPSENS_PIN2);


#define AVE_NUM             4
#define CAPSENSE_SAMPLING  20

#define CAPSENSE_MIN_TH   100
#define CAPSENSE_MAX_TH   300



void setup(){
  
 pinMode(CAPSENS_OUT,OUTPUT);
 pinMode(CAPSENS_PIN1,INPUT);
 pinMode(CAPSENS_PIN2,INPUT);
 pinMode(CAPSENS_PIN3,INPUT);
 pinMode(CAPSENS_PIN4,INPUT);
 
 cs_0.set_CS_AutocaL_Millis(0xFFFFFFFF);
 cs_1.set_CS_AutocaL_Millis(0xFFFFFFFF);
 cs_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
 cs_3.set_CS_AutocaL_Millis(0xFFFFFFFF);
 
Serial.begin(9600);
 
}

void loop(){
  

  long cs[2];

  

    cs[0]+=cs_0.capSense(CAPSENSE_SAMPLING);
    cs[1]+=cs_1.capSense(CAPSENSE_SAMPLING);
  
  Serial.print(cs[0]);
  Serial.print("/t");
   Serial.print(cs[1]);
  Serial.print("/n");
  
  delay(100);
 
  } 
  

