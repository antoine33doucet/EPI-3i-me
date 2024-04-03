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
  Serial.begin(9600);
}

int VChiffre = -1;
int VDate =  0;
void loop()
{
  int numPoussoir;

  VChiffre = EtatBouton();
  if (VChiffre != -1)
  {
    Serial.print(VChiffre);
    if (VChiffre == 1)
    {
      VDate =  1;
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
  }
  if (VDate == 1689)
  {
     VDate =  1;
     Serial.println("Montequieu");
  }
  if (VDate == 1885)
  {
     VDate =  1;
     Serial.println("Mauriac");
  }



  /*  Serial.print( lirePoussoirs(1);
    Serial.print(" ");
    Serial.print( lirePoussoirs(2));
    Serial.print(" ");
    Serial.print( lirePoussoirs(3));
    Serial.print(" ");
    Serial.print( lirePoussoirs(4));
    Serial.print(" ");
    Serial.print( lirePoussoirs(5));
    Serial.print(" ");
    Serial.println(" ");*/
  delay(30);
}
