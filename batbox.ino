int numSamples=0;
long t, t0;

void setup()
{
  Serial.begin(115200);

  ADCSRA = 0;             // clear ADCSRA register
  ADCSRB = 0;             // clear ADCSRB register
  ADMUX |= (0 & 0x07);    // set A0 analog input pin
  ADMUX |= (1 << REFS0);  // set reference voltage to 1.1V
  ADMUX |= (1 << REFS1);  // set reference voltage to 1.1V
//  ADMUX |= (1 << ADLAR);  // left align ADC value to 8 bits from ADCH register

  // sampling rate is [ADC clock] / [prescaler] / [conversion clock cycles]
  // for Arduino Uno ADC clock is 16 MHz and a conversion takes 13 clock cycles
  //ADCSRA |= (1 << ADPS2) | (1 << ADPS0);    // 32 prescaler for 38.5 KHz
  ADCSRA |= (1 << ADPS2);                     // 16 prescaler for 76.9 KHz
  //ADCSRA |= (1 << ADPS1) | (1 << ADPS0);    // 8 prescaler for 153.8 KHz

  ADCSRA |= (1 << ADATE); // enable auto trigger
  ADCSRA |= (1 << ADIE);  // enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN);  // enable ADC
  ADCSRA |= (1 << ADSC);  // start ADC measurements

	pinMode(2, OUTPUT); 
	pinMode(3, INPUT); 

}

ISR(ADC_vect)
{
  unsigned int x = ADCH;  // read 8 bit value from ADC
  x<<=8;
	x+=ADCL;
  if (numSamples<1000) {
	Serial.print(x);Serial.print(" ");
	numSamples++;
	}
}
  
void loop()
{
  if (numSamples>=1000)
  {
    Serial.println(digitalRead(3));
    delay(1000);
    
	digitalWrite(2, HIGH);
	delayMicroseconds(10);
	digitalWrite(2, LOW);
    numSamples=0;
  }
}


//unsigned int V;

//void setup()
//{
//	Serial.begin(115200);
//	analogReference(INTERNAL); analogRead(A1); delay(100); // needed to allow Voltage reference setup
//	pinMode(2, OUTPUT); 
// pinMode(3, INPUT); 
//}

//void loop()
//{
//	Serial.println();
//	delay(1000);
//}
