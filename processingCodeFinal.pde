import processing.serial.*; // add the serial library
Serial myPort; // the serial port to monitor
void setup() {
 size(600, 600); // set the window size, size() also sets width and height variables
 // first argument = width, second argument = height
 printArray(Serial.list()); // list all available serial ports
 myPort = new Serial(this, Serial.list()[0], 9600); // define input port
 myPort.clear(); // clear the port of any initial junk
 fill(0, 0, 255); // pick the fill color (r,g,b)
}


void draw () {
 if (myPort.available () > 0) { // make sure port is open
 String inString = myPort.readStringUntil('\n'); // read input string
 if (inString != null) { // ignore null strings
 inString = trim(inString); // trim off any whitespace
 String[] xyRaw = splitTokens(inString, ","); // extract x & y into an array
 // proceed only if correct # of values extracted from the string:
if (xyRaw.length == 2) {
 int x = int(xyRaw[0]);
 int y = int(xyRaw[1]);
 if(x>10)
 {
   textSize(50);
   fill(0,255,0);
   text("you have mail!",100,300);
   text("mailbox is locked",100,100);
 }
 if(y==2){
   background(0,0,255);
   textSize(50);
   fill(255,0,0);
   text("mail has been received",250,300);
 }}}}}
