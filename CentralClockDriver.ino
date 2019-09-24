/* Simple central clock driver for clocks that require alternate positive / negative inputs
 * Uses 2 pins to drive optoisolated input
 * Clock source is Arduino crystal, so this might drift a lot
 * Uses timer+interrupt so that code execution does not affect timing. You can use loop() for other stuff
 */

#define ledPin 13
#define clockPin1 12
#define clockPin2 11

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(clockPin2, OUTPUT);

  // initialize timer1 

  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 62500;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts
  

}

volatile int secCount = 0;
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  if(30==secCount) {
    digitalWrite(clockPin1, 0);
    digitalWrite(clockPin2, 1);
  } else if (90==secCount) {
    digitalWrite(clockPin1, 1);
    digitalWrite(clockPin2, 0);
  } else {
    digitalWrite(clockPin1, 0);
    digitalWrite(clockPin2, 0);
  }
  secCount++;

  if(120==secCount) {
    secCount=0;
  }

    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);   // toggle LED pin

}


void loop()

{

  // your program here…

}
