// ANTOINE DOUCET
// 02/2021

#include <Servo.h>


const byte NON_PRESSE = 0;
const byte ENFONCE = 1;
const byte PRESSE = 2;

byte etatAutomate = NON_PRESSE;
int etatPoussoir = -1;

byte Bouton1 = NON_PRESSE;
byte Bouton2 = NON_PRESSE;
byte Bouton3 = NON_PRESSE;
byte Bouton4 = NON_PRESSE;
byte Bouton5 = NON_PRESSE;
byte Bouton6 = NON_PRESSE;
byte Bouton7 = NON_PRESSE;
byte Bouton8 = NON_PRESSE;
byte Bouton9 = NON_PRESSE;
byte Bouton0 = NON_PRESSE;

const byte AUCUN_EVENEMENT = 0;
const byte EVENEMENT_PRESSE = 1;
const byte EVENEMENT_RELACHE = 2;

const int pinPoussoirs = 3;

const byte VoletHaut = 0;
const byte VoletGauche = 1;
const byte VoletDroite = 2;

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int Min = 0;
int Max = 90;

int VitesseVolet = 15;

int PosVolH = 0;
int PosVolG = 0;
int PosVolD = 0;

unsigned long last_click_timestamp = 0;
int fast_clicks = 1;
bool tease_mode = true;

int lirePoussoirs(int NumPin)
{
  int resultat;
  int numPoussoir = (analogRead(NumPin)) / 256;
  int nouvelEtatPoussoir = etatPoussoir; /* à priori rien ne change */
  return numPoussoir;
}

int EtatBouton()
{

  //etat 3 rine d'appuyer 0 le plus petit et 1 le plus grand

  // 3 8 = pin 1
  //  Etat = lirePoussoirs(1);
  if (lirePoussoirs(3) == 0)
  {
    if (Bouton1 == NON_PRESSE)
    {
      Bouton1 = PRESSE;
      return 1;
    }
  }
  else if (lirePoussoirs(2) == 0)
  {
    if (Bouton2 == NON_PRESSE)
    {
      Bouton2 = PRESSE;
      return 2;
    }
  }
  else if (lirePoussoirs(1) == 0)
  {
    if (Bouton3 == NON_PRESSE)
    {
      Bouton3 = PRESSE;
      return 3;
    }
  }
  else if (lirePoussoirs(4) == 0)
  {
    if (Bouton4 == NON_PRESSE)
    {
      Bouton4 = PRESSE;
      return 4;
    }
  }
  else if (lirePoussoirs(5) == 0)
  {
    if (Bouton5 == NON_PRESSE)
    {
      Bouton5 = PRESSE;
      return 5;
    }
  }
  else if (lirePoussoirs(3) == 1)
  {
    if (Bouton6 == NON_PRESSE)
    {
      Bouton6 = PRESSE;
      return 6;
    }
  }
  else if (lirePoussoirs(2) == 1)
  {
    if (Bouton7 == NON_PRESSE)
    {
      Bouton7 = PRESSE;
      return 7;
    }
  }
  else if (lirePoussoirs(1) == 1)
  {
    if (Bouton8 == NON_PRESSE)
    {
      Bouton8 = PRESSE;
      return 8;
    }
  }
  else if (lirePoussoirs(4) == 1)
  {
    if (Bouton9 == NON_PRESSE)
    {
      Bouton9 = PRESSE;
      return 9;
    }
  }
  else if (lirePoussoirs(5) == 1)
  {
    if (Bouton0 == NON_PRESSE)
    {
      Bouton0 = PRESSE;
      return 0;
    }
  }
  else
  {
    //Serial.print("R");
    Bouton0 = NON_PRESSE;
    Bouton1 = NON_PRESSE;
    Bouton2 = NON_PRESSE;
    Bouton3 = NON_PRESSE;
    Bouton4 = NON_PRESSE;
    Bouton5 = NON_PRESSE;
    Bouton6 = NON_PRESSE;
    Bouton7 = NON_PRESSE;
    Bouton8 = NON_PRESSE;
    Bouton9 = NON_PRESSE;
  }
  return -1;
}

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
  int pos;
  if (CVolet == VoletHaut)
  {
    //2 et 4
    for (pos = PosVolH; pos < Max; pos += 1)
    {
      myservo2.write(90+pos);
      myservo4.write(Max - pos);
      delay(VitesseVolet);
    }
    PosVolH = pos;
    Serial.println("Volet Haut Ouvert");
  }
  if (CVolet == VoletGauche)
  {
    //3
    for (pos = PosVolG; pos < Max; pos += 1)
    {
      myservo3.write(Max - pos);
      delay(VitesseVolet);
    }
    PosVolG = pos;
    Serial.println("VoletGauche Ouvert");
  }
  if (CVolet == VoletDroite)
  {
    //1
    for (pos = PosVolD; pos < Max; pos += 1)
    {
      myservo1.write(90+pos);
      delay(VitesseVolet);
    }
    PosVolD = pos;
    Serial.println("VoletDroite Ouvert");
  }
}

int Fermer(int CVolet)
{
  int pos;
  if (CVolet == VoletHaut)
  {
    //2 et 4
    for (pos = PosVolH; pos > Min; pos -= 1)
    {
      myservo2.write(90+pos);
      myservo4.write(Max - pos);
      delay(VitesseVolet);
    }
    PosVolH = pos;
    Serial.println("Volet Haut Fermer");
  }
  if (CVolet == VoletGauche)
  {
    //3
    for (pos = PosVolG; pos > Min; pos -= 1)
    {
      myservo3.write(Max - pos);
      delay(VitesseVolet);
    }
    PosVolG = pos;
    Serial.println("VoletGauche Fermer");
  }
  if (CVolet == VoletDroite)
  {
    //1
    for (pos = PosVolD; pos > Min; pos -= 1)
    {
      myservo1.write(90+pos);
      delay(VitesseVolet);
    }
    PosVolD = pos;
    Serial.println("VoletDroite Fermer");
  }
}


int VChiffre = -1;
int VDate =  0;
  int numPoussor;
  int VoletOuvert = 0;
void loop()
{

  VChiffre = EtatBouton();
  if (VChiffre != -1)
  {
    Serial.println(VChiffre);
    if (VoletOuvert == 1)
    {
      Fermer(VoletHaut);
      Fermer(VoletGauche);
      Fermer(VoletDroite);
    }
    
    
    Serial.print(VChiffre);
    if (VChiffre == 1)
    {
      VDate =  1;
    }
    else if (VChiffre == 2)
    {
      VDate =  2;
    }
    else if (VDate < 10000)
    {
      VDate = VDate * 10   + VChiffre;
    }
    Serial.print("_");
    Serial.println(VDate);
  }

  if (VDate == 1533)
  {
     VDate =  1;
     Serial.println("Montaigne");
     Ouvrir(VoletHaut);
     VoletOuvert = 1;
  }
  if (VDate == 1689)
  {
     VDate =  1;
     Serial.println("Montequieu");
     Ouvrir(VoletGauche);
     VoletOuvert = 1;
  }
  if (VDate == 1885)
  {
     VDate =  1;
     Serial.println("Mauriac");
     Ouvrir(VoletDroite);
     VoletOuvert = 1;
  }
  if (VDate == 2006)
  {
     VDate =  1;
     Serial.println("Antoine");
     Ouvrir(VoletGauche);
     Ouvrir(VoletDroite);
     Ouvrir(VoletHaut);
     VoletOuvert = 1;
  }
   delay(20);
}
/*
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

}*/
