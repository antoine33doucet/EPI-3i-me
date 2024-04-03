// ANTOINE DOUCET
// 02/2021

#include <Servo.h>

const byte VoletHaut = 0;
const byte VoletGauche = 1;
const byte VoletDroite = 2;

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int Min = 0;
int Max = 90;

int VitesseVolet = 25;

unsigned long last_click_timestamp = 0;
int fast_clicks = 1;
bool tease_mode = true;

void setup()
{
  myservo1.attach(5);
  myservo2.attach(6);
  myservo3.attach(7);
  myservo4.attach(8);
  Serial.begin(9600);
  Serial.println("Setup done");
}

int Ouvrir(int CVolet)
{
  if (CVolet == VoletHaut)
  {
    //2 et 4
    for (int pos = Max; pos > Min; pos -= 1)
    {
      myservo4.write(pos);
      myservo2.write(Max - pos);
      delay(VitesseVolet);
    }
    Serial.println("Volet Haut Ouvert");
  }
  if (CVolet == VoletGauche)
  {
    //3
    for (int pos = Max; pos > Min; pos -= 1)
    {
      myservo3.write(pos);
      delay(VitesseVolet);
    }
    Serial.println("VoletGauche Ouvert");
  }
  if (CVolet == VoletDroite)
  {
    //1
    for (int pos = Max; pos > Min; pos -= 1)
    {
      myservo1.write(Max - pos);
      delay(VitesseVolet);
    }
    Serial.println("VoletDroite Ouvert");
  }
}

int Fermer(int CVolet)
{
  if (CVolet == VoletHaut)
  {
    //2 et 4
    for (int pos = Max; pos > Min; pos -= 1)
    {
      myservo2.write(pos);
      myservo4.write(Max - pos);
      delay(VitesseVolet);
    }
    Serial.println("Volet Haut Fermer");
  }
  if (CVolet == VoletGauche)
  {
    //3
    for (int pos = Max; pos > Min; pos -= 1)
    {
      myservo3.write(Max - pos);
      delay(VitesseVolet);
    }
    Serial.println("VoletGauche Fermer");
  }
  if (CVolet == VoletDroite)
  {
    //1
    for (int pos = Max; pos > Min; pos -= 1)
    {
      myservo1.write(pos);
      delay(VitesseVolet);
    }
    Serial.println("VoletDroite Fermer");
  }
}

void loop()
{

//  Ouvrir(VoletHaut);
//  delay(5000);
//  Fermer(VoletHaut);
//  delay(5000);
//  Ouvrir(VoletGauche);
//  delay(5000);
//  Fermer(VoletGauche);
//  delay(5000);
  Ouvrir(VoletDroite);
  delay(5000);
  Fermer(VoletDroite);
  delay(5000);

}
