//Vitrine00 version 231114a. Test avec 4 fleches sur interruptions
//BleKeyboard library code    and doc here : https://github.com/T-vK/ESP32-BLE-Keyboard
//TODO : use press and release on interrupts
//TODO bleKeyboard.setDelay(10)
//Type de carte : choisir FirebeetleESP32 ou ESP32Dev module suivant le module ESP32
#define BOARD ESP32 //ESP32 (clavier BLUETOOTH) ou LEONARDO (clavier USB)

//#include <BleMouse.h>
#include <BleKeyboard.h>
//debug//usb bt
//BleMouse bleMouse;
//BleKeyboard bleKeyboard;
BleKeyboard vKeyboard("ESP32LudCamGi", "ESAAIX", 60);

#define DBGBUTTON 0 //A mettre a 0 pour desactiver le DEBUG boutons et ameliorer la reactivité'input LAG

//Definition des broches (fleches directionelles + jump)
//NB ; broches pour ESP32. Mais pour leonardo, les broches interruptibles sont : 3 2 0 1 7
#define PIN_UP  D2 //13
#define PIN_DN  D3
//Variables utilisees pour les differents boutons
int UPstate , UPstateOld = HIGH;
int DNstate , DNstateOld = HIGH;
bool bConnected = false;

void setup()
{
  pinMode(PIN_UP , INPUT_PULLUP);
  pinMode(PIN_DN , INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  //Initialisation
  vKeyboard.begin();
  //Connection
  int ret = 0;
  while ( ret != 1)
  {
    ret = vKeyboard.isConnected();
    //ret = bleMouse.isConnected();
    Serial.println("conn"); Serial.println(ret);
    delay(500);
  }
  Serial.println("BLE Connected!");
}

// Gestion d'un appui touche : on envoie juste les commandes pout indiquer
// qu'on a appuyé ou relaché une touche, pour ne pas encombrer la liaison USB ou Bluetooth
// Fonction générique pour toutes les touches
void manageKey(int PIN_NB, uint8_t KEY, int* state, int* stateOld)
{
  *state = digitalRead(PIN_NB);
  if (  *stateOld != *state)
  {
#if DBGBUTTON
    Serial.print(PIN_NB);
    Serial.print("chgto");
    Serial.println(*state);
#endif
    if (*state == HIGH)
    {
      //vKeyboard.press(KEY);
      vKeyboard.release(KEY);
    }
    else
    {
      vKeyboard.press(KEY);
      //vKeyboard.release(KEY);
    }
    *stateOld = *state;
  }
}

bool bPressed1 = false;
int pot1Value;
int pot1ValueOld;

bool bPressed2 = false;
int pot2Value;
int pot2ValueOld;

void loop()
{
  if (vKeyboard.isConnected() == 1 )
  {
    bConnected = true;
    //manageKey( PIN_UP , KEY_UP_ARROW   , &UPstate , &UPstateOld  );
    manageKey( PIN_UP , ' '   , &UPstate , &UPstateOld  );
    delay(1);
    //manageKey( PIN_DN , KEY_DOWN_ARROW , &DNstate , &DNstateOld  );
    manageKey( PIN_DN , 's' , &DNstate , &DNstateOld  );
    delay(1);

    //Gestion potentiometre 1
    pot1Value = analogRead(A1);
    Serial.print("pot1Value");
    Serial.println(pot1Value);
    if (bPressed1 == false)
    {
      if (pot1Value  < 1000)
      {
        vKeyboard.press('w');
        bPressed1 = true;
      }
      else if (pot1Value  > 3000)
      {
        vKeyboard.press('s');
        bPressed1 = true;
      }
      pot1ValueOld = pot1Value;
    }
    if ( (pot1Value >= 1000 ) &&  (pot1Value <= 3000 ) )
    {
      bPressed1 = false;
      vKeyboard.releaseAll();
      delay(100);
    }

    //Gestion potentiometre 2
    pot2Value = analogRead(A2);
    Serial.println(pot2Value);
    if (bPressed2 == false)
    {
      if (pot2Value  < 1000)
      {
        vKeyboard.press('a');
        bPressed2 = true;
      }
      else if (pot2Value  > 3000)
      {
        vKeyboard.press('d');
        bPressed2 = true;
      }
      pot2ValueOld = pot2Value;
    }
    if ( (pot2Value >= 1000 ) &&  (pot2Value <= 3000 ) )
    {
      bPressed2 = false;
      vKeyboard.releaseAll();
      delay(100);
    }
  }
  else // Si déconnexion détectée
  {
    bConnected = false;
    Serial.println("Waiting 3 seconds for connection...");
    delay(3000);    // Attente avant de retenter une connection
    esp_restart();  // Reconnection par reset de la carte
  }
}
