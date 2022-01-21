/*
  Titre      : Feu de circulation
  Auteur     : Anis Aliouachene
  Date       : 20/01/2022
  Description: Transfer programme feu de circulation structure en POO et reussir a faire un feu rouge 
  Version    : 0.0.1
*/

#include <Arduino.h>

class Feu{
  // Declaration attribue prive
	private: 
	    int FeuPin; 
	    
	public:
    Feu(){}  // Constrecteur par defaut 

    /**
     * @brief Construct a new Feu object
     * 
     * @param Pin 
     */
    Feu(int Pin){
    	FeuPin = Pin; 
	  }
	  
    // Fonction pour la configuration de la broche 
    void initialisation(){
      pinMode(FeuPin, OUTPUT);
    }

    // Fonction d'allumage de la LED
    void AllumerLED(){
      digitalWrite(FeuPin, HIGH);
    }

    // Fonction eteindre la LED
    void EtendreLED(){
      digitalWrite(FeuPin, LOW);
      Serial.println("LED Eteint");
    }
};

class Time {
   // Declaration attribue prive
   private: 
      unsigned long TempsActuel = 0; 
      unsigned long TempsAvant = 0; 
      bool Test = false; 

   public: 
      Time(){}    //Constrecteur par default 

      // Fonction pour calculer le temps ecouler et si oui retourner True 
      bool isTime(unsigned int Target){
        Test = false;
        while (Test == false)
        {
            TempsActuel = millis();
            if (TempsActuel - TempsAvant  >= Target) {
              TempsAvant = TempsActuel; 
              Test = true; 
            }
        }
        return Test; 
        }

};


// Declaration des constante pour configurer les Broches 
const int PIN_ROUGE = 2;
const int PIN_VERT = 5; 
const int PIN_JAUNE = 3; 

// Declarartion des constantes pour le temps d'attente 
const int MS_DELAI_1 = 4000; 
const int MS_DELAI_2 = 3000;

// Declaration des objets 
Feu feuRouge(PIN_ROUGE);
Feu feuVert(PIN_VERT); 
Feu feuJaune(PIN_JAUNE);
Time delai; 

// Fonction Setup et configuration des broches 
void setup() {
  
  feuRouge.initialisation(); 
  feuJaune.initialisation(); 
  feuVert.initialisation();
  Serial.begin(9600);

}


void loop() {
  
// Test rapide des classe pour un seul Feu Rouge ; 
  feuRouge.AllumerLED();

// Attente et passage au feu vert 
  if (delai.isTime(MS_DELAI_1)) {
     feuRouge.EtendreLED();
     feuVert.AllumerLED();
    }

// Attandre puis passer au feu jaune  
  if (delai.isTime(MS_DELAI_2)){
        feuJaune.AllumerLED();
        feuVert.EtendreLED();
    }

 // Attendre puis passer au feu rouge et refaire le boucle    
  if (delai.isTime(MS_DELAI_2)) {
      feuJaune.EtendreLED();
      } 
    
}