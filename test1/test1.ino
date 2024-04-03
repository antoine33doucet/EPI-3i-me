const byte NON_PRESSE = 0;
const byte ENFONCE = 1;
const byte PRESSE = 2;

byte etatAutomate = NON_PRESSE;
int etatPoussoir = -1;

const byte AUCUN_EVENEMENT = 0;
const byte EVENEMENT_PRESSE = 1;
const byte EVENEMENT_RELACHE = 2;

const int pinPoussoirs = 3;

int lirePoussoirs()
{
  int resultat;
  int numPoussoir = (analogRead(pinPoussoirs) + 64) / 128;

  int nouvelEtatPoussoir = etatPoussoir; /* à priori rien ne change */

  switch (etatAutomate) {
    case NON_PRESSE:
      if (numPoussoir < 8)
        etatAutomate = ENFONCE;
      break;
    case ENFONCE:
      if (numPoussoir < 8) {
        etatAutomate = PRESSE;
        nouvelEtatPoussoir = numPoussoir;
      }
      else {
        etatAutomate = NON_PRESSE;
      }
      break;
    case PRESSE:
      if (numPoussoir == 8) {
        etatAutomate = NON_PRESSE;
        nouvelEtatPoussoir = -1;
      }
      break;
  }

  return nouvelEtatPoussoir;
}

/*
   construction d'un événement en comparant
   le nouvel état des poussoirs avec l'état précédent.
*/
byte lireEvenement(int *numPoussoir)
{
  byte evenement;
  int nouvelEtatPoussoir = lirePoussoirs();

  if (nouvelEtatPoussoir == etatPoussoir)
    evenement = AUCUN_EVENEMENT;
  if (nouvelEtatPoussoir >= 0 && etatPoussoir == -1)
    evenement = EVENEMENT_PRESSE;
  if (nouvelEtatPoussoir == -1 && etatPoussoir >= 0)
    evenement = EVENEMENT_RELACHE;

  etatPoussoir = nouvelEtatPoussoir;
  *numPoussoir = etatPoussoir;

  return evenement;
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int numPoussoir;
  byte evenement = lireEvenement(&numPoussoir);

  switch (evenement) {
    case EVENEMENT_PRESSE:
      Serial.print("Presse : ");
      Serial.println(numPoussoir);
      break;
    case EVENEMENT_RELACHE:
      Serial.print("Relache : ");
      Serial.println(numPoussoir);
      break;
  }
  Serial.print( analogRead(1));
  Serial.print(" ");
  Serial.print( analogRead(2));
  Serial.print(" ");
  Serial.print( analogRead(3));
  Serial.print(" ");
  Serial.print( analogRead(4));
  Serial.print(" ");
  Serial.print( analogRead(5));
  Serial.print(" ");
  Serial.println(" ");
  delay(300);
}
