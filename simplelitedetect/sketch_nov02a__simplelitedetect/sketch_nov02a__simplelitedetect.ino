

/*
Standby
Presence detected

Ultrasonic sensor distance measurement formula

Distance = (Time x Sound speed in Air (340 m/s))/2


*/

const int trigPin = 3;
const int echoPin = 2;
long duration;
int distanceCm, distanceInch;

int flagLighting = 8;
int rigLight = 4;

void setup()
{
  // put your setup code here, to run once:
  pinMode(flagLighting, OUTPUT);
  pinMode(rigLight, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}
int wallDistance = 65;
bool lighting = false;
bool detected = false;
bool timedOut = true;
int timeout = 18;
int ctimeout = 0;

void loop()
{
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.0340 / 2;
  distanceInch = duration * 0.01330 / 2;

  timedOut = timeout < ctimeout;
  detected = distanceCm < wallDistance;

  Serial.println(distanceCm);

  if (detected)
  {
    Serial.println("Presence detected - lighting");
    ctimeout = 0;
    timedOut = false;
    lighting = true;

    lite(true);
  }
  else
  {
    if (timedOut)
    {
      lite(false);
      lighting = false;
      Serial.println("Seems no one's in the scenery - Standby");
    }

    else
    {
      Serial.println("Not timed out, might be still someone there");
    }
  }

  delay(1000);
  ctimeout++;
}

void lite(bool active)
{
  if (active)
  {

    digitalWrite(flagLighting, HIGH);
    digitalWrite(rigLight, HIGH);
  }
  else
    digitalWrite(flagLighting, LOW);
  digitalWrite(rigLight, LOW);
  {
  }
}