#include <Servo.h>

const int MESSAGE_LENGTH = 5;
const char MESSAGE_BEGIN = '$';
const char MESSAGE_END = '~';
const char COMMAND_SUCCESS = 'Y';
const char COMMAND_FAILURE = 'N';
const int LIMIT_MAX = 180;
const int LIMIT_MIN	= 15; // For some reason this is the mechanical left limit.
const int BAUD_RATE = 9600;
const int PAN_PIN = 9;
const int TILT_PIN = 10;
unsigned char buffer [MESSAGE_LENGTH - 2];
Servo panServo, tiltServo;
int i;
int byteCount;
byte incomingByte;

void setup() 
{
  Serial.begin (BAUD_RATE);
  panServo.attach(PAN_PIN);
  tiltServo.attach (TILT_PIN);
  byteCount = 0;
}

void loop() 
{
  ServiceSerial ();
}

void ServiceSerial ()
{
  // Service the serial port and process any available data.
  if (Serial.available ())
  {
    //... then pull it in for processing
    incomingByte = Serial.read ();

    if (incomingByte == MESSAGE_BEGIN)  // Check for new message
    {
      // A new command is on its way. Set the counter.
      byteCount = 1;
    }
    else if (byteCount > 0 && byteCount < MESSAGE_LENGTH - 1)
    {
      // Update counter and populate the buffer.
      byteCount++;
      buffer [byteCount - 2] = incomingByte;
    }
    else if (incomingByte == MESSAGE_END)
    {
      if (byteCount == MESSAGE_LENGTH - 1)
      {
        byteCount = -1;
        ProcessBuffer ();
      }
    }
  }
}

void ProcessBuffer ()
{
  if (buffer [0] == 'P')
  {
    if (buffer [1] == 'T' && buffer [2] == '?')
    {
        Serial.write (COMMAND_SUCCESS);
    }
    else
        moveServo (panServo, RetrieveAngle (buffer [1], buffer [2]));
  }
  else if (buffer [0] == 'T')
      moveServo (tiltServo, RetrieveAngle (buffer [1], buffer [2]));
      
  //Serial.flush ();
}

int RetrieveAngle (char a, char b)
{
  return (convertCharToInt (a) << 4) | convertCharToInt (b);
}

void moveServo (Servo servo, int angle)
{
  if (angle >= LIMIT_MIN && angle <= LIMIT_MAX)
  {
    servo.write (angle);
    Serial.write (COMMAND_SUCCESS);
  }
  else
    Serial.write(COMMAND_FAILURE);
}

int convertCharToInt (char input)
{
  switch (input)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return input - '0';
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
      return input - '7';
  }
}


