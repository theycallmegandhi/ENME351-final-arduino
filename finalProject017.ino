#include <IRremote.h>
#include <IRremoteInt.h>
#include <LiquidCrystal.h>
#include <Servo.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int x=0;
int y=0;
int in1 =7;
int in2=8;
int pwm=10;
int receiver = 6; // Signal Pin of IR receiver to Arduino Digital Pin 11
 float tim3      = millis()*1000;
  int   days      = tim3/86400;
  int  hours      = (tim3/3600)-(days*24);
  int minutes     = (tim3/60)-(hours*60)-(days*24);
  int seconds     = tim3-(minutes*60)-(hours*60)-(days*24);
  int veloc       = 0;
  int pos         = 0;
  boolean reverse = 0;
  unsigned long key_value = 0;
  
  /*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
Servo myServo;

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("rip code");
  irrecv.enableIRIn(); // Start the receiver
  y=1;
   myServo.attach(9);
}

void loop(){

  int photocellReading = analogRead(5);  
  
  Serial.print("Analog reading = ");
  Serial.print(photocellReading);     // the raw analog reading
 
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 10) {
    lcd.setCursor(0,0);
    lcd.print(" - The Mailbox");
    lcd.setCursor(0,1);
    lcd.print("is CLOSED");
  } 
   else {
    lcd.setCursor(0,0);
    lcd.print(" - Mailbox ");
    lcd.setCursor(0,1);
    lcd.print("is OPEN");
  }
  delay(1000);
  
  if(irrecv.decode(&results)){
    switch(results.value)

  {
  case 0xFFA25D: Serial.println("POWER");lcd.print("power"); break;
  case 0xFFE21D: Serial.println("FUNC/STOP");lcd.print("power"); break;
  case 0xFF629D: Serial.println("VOL+");lcd.print("power"); break;
  case 0xFF22DD: Serial.println("FAST BACK");  lcd.print("power");  break;
  case 0xFF02FD: Serial.println("PAUSE");  lcd.print("power");  break;
  case 0xFFC23D: Serial.println("FAST FORWARD");lcd.print("power");   break;
  case 0xFFE01F: Serial.println("DOWN");lcd.print("power");    break;
  case 0xFFA857: Serial.println("VOL-");lcd.print("power");    break;
  case 0xFF906F: Serial.println("UP"); lcd.print("power");   break;
  case 0xFF9867: Serial.println("EQ"); lcd.print("power");   break;
  case 0xFFB04F: Serial.println("ST/REPT"); lcd.print("power");   break;
  case 0xFF6897: Serial.println("0");lcd.print("power");    break;
  case 0xFF30CF: Serial.println("1");lcd.print("power") ; x=0;  break;
  case 0xFF18E7: Serial.println("2");lcd.print("power") ; x=2;   break;
  case 0xFF7A85: Serial.println("3");lcd.print("power") ;   break;
  case 0xFF10EF: Serial.println("4");lcd.print("power") ;   break;
  case 0xFF38C7: Serial.println("5");lcd.print("power") ;   break;
  case 0xFF5AA5: Serial.println("6"); lcd.print("power") ;  break;
  case 0xFF42BD: Serial.println("7"); lcd.print("power")  ; break;
  case 0xFF4AB5: Serial.println("8");lcd.print("power")    ;break;
  case 0xFF52AD: Serial.println("9");lcd.print("power")    ;break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  
  }}
  Serial.println( "  The value of X attop of loop 1 : ");
  Serial.println(x);
  Serial.println( "  The value of Y at top of loop 1 : ");
  Serial.println(y);
if (x==0) {y=1;}


// When Mailbox is opened for placing mail, photo cell reading > 22.  
// Keep delay for 30 seconds ( time for placing mail in mailbox and closing the mailbox
// Then Automatically lock mailbox  --- motor angle at 125

if(photocellReading > 20) { 
    delay(30000);                      //  Wait for 30 seconds for mail to be placed in box and box to be closed.
    
    for (pos = 0; pos <= 90; pos += 5) { // goes from 0 degrees to 90 degrees
                                         // in steps of 5 degrees
    myServo.write(pos);                  //  pos = 90 will lock the mailbox.
    delay(2000); }
    y=2;
    Serial.println("Mail has been Placed in the mailbox");
                         // waits 2000ms for the servo to reach the position
     Serial.println( "  The value of Y at 2 : ");
     Serial.println(y);
    
  }
  
  Serial.println( "  The value of X at this point 3 after photocellreading para is : ");
  Serial.println(x);
  Serial.println( "  The value of Y at this point 3 after photocellreading para is : ");
  Serial.println(y);
  
  //  When 2 is pressed on receiver.  The owner will keep the mailbox unlocked and retrieve Mail.  
  //  And keep it unlocked for new mail.  The door will be closed bout unlocked ( motor position at 25 )
  if(x==2 and y==2) {                 //  When 2 is pressed on the receiver and y=2 that is mail has already been placed in the box
// if(x==2 )  {
    for (pos = 95; pos >0; pos -= 5) { // goes from 95 degrees to 0 degrees
                                          // in steps of 5 degrees
    
            // tell servo to go to position in variable 'pos'
    
    
    myServo.write(pos);               //  Pos = 25 will unlock the box.  The owner will retrieve the mail.  
                                      //  The Mailbox will be kept in unlocked position.
   delay(1000); }                     // waits 1000ms for the servo to reach the position
    Serial.println("Mail has been retrieved");
    // tell servo to go to position in variable 'pos'
    delay(1000); 
      x=0;                           
      y=1;
  }
  String greph = String(photocellReading)+String(",")+String(x);
  Serial.print(greph);
//delay(1000000);
}
