#include <SD.h>
#include <ADXL335.h>
#include <Wire.h>
#include"SPI.h"
#include "RTClib.h"


const int pin_x = A0;
const int pin_y = A1;
const int pin_z = A2;
const float aref = 3.3;
String dataString ="";
int string_width;
float x;
float y;
float z;


String Year = "";
String Month = "";
String Day = "";
String Hour = "";
String Minute = "";
String currentTime ="";




ADXL335 accel(pin_x, pin_y, pin_z, aref);
RTC_DS1307 RTC;
File myFile;

// ##########################################Setup########################################################
void setup(){

  Serial.begin(9600);
  Serial.print("Initializing SD card...");
   pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
   Wire.begin();
   RTC.begin();
   if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
 

}

// #############################################loop##############################################################


void loop()
{
  timeStamp();
  accel.update();
  x = accel.getX();
  y = accel.getY();
  z = accel.getZ();
  myFile = SD.open(currentTime, FILE_WRITE);

  
  if (myFile) {
//    Serial.print("Writing to test.txt...");
    dataString = String(x) + "," + String(y) + "," + String(z);
    saveData();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}



// ########################################################################################################################



void saveData(){
  if(SD.exists(currentTime)){ // check the card is still there
    
    if (myFile){
      myFile.println(dataString);
      myFile.close(); // close the file
//      Serial.println("done.");
      }
    }
  else{
  Serial.println("Error writing to file !");
  } 
}

void timeStamp(){
    DateTime now = RTC.now(); 
    Year = String((now.year()));
    Month = String((now.month()));
    Day = String((now.day()));
    Hour = String((now.hour()));
    Minute = String((now.minute()));
    currentTime = Day + "_" + Hour + "_" + Minute +".csv";
  }



