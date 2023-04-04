#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"



#define bouton1 A0
#define bouton2 A1
#define bouton3 A2
#define bouton4 A3
#define bouton5 2
#define bouton6 3
#define bouton7 4
#define bouton8 5
#define bouton9 6
#define volumeplus 7
#define volumemoins 8
#define potvolume A5


#define AUDIOPINTX 11
#define AUDIOPINRX 10

#define BLPINRX 8
#define BLPINTX 9


SoftwareSerial mySoftwareSerial(AUDIOPINRX, AUDIOPINTX ); // RX, TX
SoftwareSerial moduleBluetooth(BLPINRX, BLPINTX ); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

//fonction d'affichage serial port
void printDetail(uint8_t type, int value);

void setup()
{

  // param DF3Player
  mySoftwareSerial.begin(9600);
  //moduleBluetooth.begin(9600);
  Serial.begin(9600);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(15);  //Set volume value. From 0 to 30
  //myDFPlayer.play(1);  //Play the first mp3
  

  // Boutons en entrée
  pinMode(bouton1, INPUT_PULLUP);
  pinMode(bouton2, INPUT_PULLUP);
  pinMode(bouton3, INPUT_PULLUP);
  pinMode(bouton4, INPUT_PULLUP);
  pinMode(bouton5, INPUT_PULLUP);
  pinMode(bouton6, INPUT_PULLUP);
  pinMode(bouton7, INPUT_PULLUP);
  pinMode(bouton8, INPUT_PULLUP);
  pinMode(bouton9, INPUT_PULLUP);


  
}

//varible globale
int volume = 15;
char val;
char set = 1;

void loop()
{

  //getion du module bluetooth
  // if (moduleBluetooth.available()) {

  //   val = moduleBluetooth.read();
  //   Serial.println(val);
  // }



  //getion du volume avec potentiomètre
  //Serial.println(analogRead(potvolume));


  //Serial.println( moduleBluetooth.read() );

  
//  set = moduleBluetooth.read();

//   if(set == "1")
//     Serial.println("1");
//   if(set == "2")
//     Serial.println("2");
  



  //Serial.println(abs(map(analogRead(potvolume), 0, 1023, 1, 30)-volume));
  if(abs(map(analogRead(potvolume), 0, 1023, 1, 30)-volume) > 1){
    volume = map(analogRead(potvolume), 0, 1023, 1, 30);
    myDFPlayer.volume(volume);
    Serial.println(volume);
  }

 


  if(digitalRead(bouton1) == LOW){
    myDFPlayer.play(1);
    Serial.println("SON-1");
  }
  if(digitalRead(bouton2) == LOW){
    myDFPlayer.play(2);
    Serial.println("SON-2");
  }
  if(digitalRead(bouton3) == LOW){
    myDFPlayer.play(3);
    Serial.println("SON-3");
  }
  if(digitalRead(bouton4) == LOW){
    myDFPlayer.play(4);
    Serial.println("SON-4");
  }
  if(digitalRead(bouton5) == LOW){
    myDFPlayer.play(5);
    Serial.println("SON-5");
  }
  if(digitalRead(bouton6) == LOW){
    myDFPlayer.play(6);
    Serial.println("SON-6");
  }
  if(digitalRead(bouton7) == LOW){
    myDFPlayer.play(7);
    Serial.println("SON-7");
  }
  if(digitalRead(bouton8) == LOW){
    myDFPlayer.play(8);
    Serial.println("SON-8");
  }
  if(digitalRead(bouton9) == LOW){
    myDFPlayer.play(9);
    Serial.println("SON-9");
  }



}





void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
