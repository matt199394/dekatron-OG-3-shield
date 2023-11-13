/*
  Dekatron Demo tester  

  Code example taken from https://threeneurons.wordpress.com/dekatron-stuff/
  by Michael Moorrees
  
 */

#define INTERVALLO 100

int D_count = 0;
int speed = 100;
int counter = 0;
int i_rate = 15;
int i_delay = 100;
int LED = 13;         // Test LED
int Guide1 = 5;       // Guide 1 - G1 pin of 2-guide Dekatron
int Guide2 = 6;       // Guide 2 - G2 pin of 2-guide Dekatron
int Index  = 7;       // Index   - NDX input pin. High when glow at K0
int Ndx = 0;          // K0 index indicator variable
int state = 0;
int demo  = 0;
int revert = 0;
unsigned long t0, dt;

void G_step(int CINT) // Dekatron Stepper
{
  if (CINT > 2) CINT = 0;
  if (CINT == 0)
  {
    digitalWrite(Guide1, LOW);
    digitalWrite(Guide2, LOW);
  }
  if (CINT == 1)
  {
    digitalWrite(Guide1, HIGH);
    digitalWrite(Guide2, LOW);
  }
  if (CINT == 2)
  {
    digitalWrite(Guide1, LOW);
    digitalWrite(Guide2, HIGH);
  }
}

void D_adv()                    // Dekatron Advance - Clockwise
{
  D_count++;
  if (D_count == 3) D_count = 0;
  G_step(D_count);
}

void D_rev()                    // Dekatron Reverse - Counter-Clockwise
{
  D_count--;
  if (D_count == -1) D_count = 2;
  G_step(D_count);
}

void demo1(){

  if (counter  > 16) {demo = 1;
           counter = 0;
           Ndx = 0;
           delay (1000);
           return;}
           
  dt = millis() - t0; 
  if ( dt >= INTERVALLO ) {
  t0 = millis();
  speed --;
  if (speed <5) speed = 100;
  }

  if (Ndx) state = !state;
                                      
  switch (state) {
    case 0:                              
      D_adv();    
      break; 
    case 1:                              
      D_rev();
      break; 
  }
 
delay (speed);
}

void demo2(){
  if (counter  > 10) {
    demo = 2;
    counter = 0;
    Ndx = 0;
    delay (1000);
    return;}
    
  if (Ndx) {
     i_rate = 16;
     i_delay = (3 * i_rate) + 8;
  }
  i_rate--;
  i_delay = (3 * abs(i_rate)) + 8;
  delay(i_delay); // wait per i_rate
  D_adv();
  }

void demo3(){
  if (counter  > 10) {
    demo = 3;
    counter = 0;
    Ndx = 0;
    delay (1000);
    return;}
    
  if (Ndx) {
     i_rate = 16;
     i_delay = (3 * i_rate) + 8;
  }
  i_rate--;
  i_delay = (3 * abs(i_rate)) + 8;
  delay(i_delay); // wait per i_rate
  D_rev();
  }

void demo4(){
  
    if (counter  > 16) {
           demo = 0;
           counter = 0;
           Ndx = 0;
           delay (1000);
           return;}                     
    D_adv();    
    delay (10);
}

// setup() runs once, at reset, to initialize system
void setup() {
  pinMode(Guide1, OUTPUT);
  pinMode(Guide2, OUTPUT);
  pinMode(Index, INPUT);
  pinMode(LED, OUTPUT);

  D_count = 0;
  i_delay = 100;
  Ndx = 0;
  G_step(D_count);
  digitalWrite(LED, LOW);

  t0 = millis();
}

// the loop function runs over and over again forever
void loop() {
  
  Ndx = digitalRead(Index); // Sample for glow at K0
  if (Ndx) {digitalWrite(LED, HIGH);
  counter ++;
  }
  else {digitalWrite(LED, LOW);}
  
  switch (demo) {
    case 0:                              
      demo1();    
      break; 
    case 1:                              
      demo2();
      break;
      case 2:                              
      demo3();
      break;
      case 3:                              
      demo4();
      break;      
}
}
