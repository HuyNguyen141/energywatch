//#include <RS485_protocol.h>

#include <ESP8266WiFi.h>
#include <time.h>
//#include <SoftwareSerial.h>
#include <Ticker.h>  //Ticker Library
 
Ticker blinker;

#include <FirebaseArduino.h>
//SoftwareSerial mySerial(4,5);//rx,tx
//#define FIREBASE_HOST "esp-android-45417.firebaseio.com"
//#define FIREBASE_AUTH "q1D40Nuj8OymmG1f7flGqvL2LmcGIOrdSiRtYpau"
#define FIREBASE_HOST "nodemcu-6edef.firebaseio.com"
#define FIREBASE_AUTH "SAAcgZRobeLw4eEBmltPc9AbfJyhsvFEwy5lKAyA"

#define WIFI_SSID "HAKARU_VNPT"
#define WIFI_PASSWORD "Hakaru+0007"
//#define MAX485_DE      4
//#define MAX485_RE_NEG  5

unsigned char RxData[11]={
  0x01
};
unsigned char TxMsg [8]={0x01,0x04,0x0F,0xA1,0x00,0x03,0xe2,0xfd};
unsigned char i,j=0,FLG,Rxflag;
unsigned short CRC;
unsigned long Time1,a;
int dem;
int timezone = 7;
int dst = 0;

void CRC_RX(unsigned char Data[],unsigned char length)
      {
        unsigned char *Pointer;
        int i;
        unsigned int crc = 0xFFFF;
        unsigned char ByteCtr;
        Pointer=(unsigned char *)Data;
        ByteCtr =length-2;
        while (ByteCtr) {

          crc ^= *Pointer++;          // XOR byte into least sig. byte of crc

          for (i = 8; i != 0; i--) {    // Loop over each bit
            if ((crc & 0x0001) != 0) {      // If the LSB is set
              crc >>= 1;                    // Shift right and XOR 0xA001
              crc ^= 0xA001;
            }
            else                            // Else LSB is not set
              crc >>= 1;                    // Just shift right
          }
          ByteCtr--;
        }
        int crcl = (crc & 0xFF00)/256; //Swaping  the bytes
        int crch = (crc & 0x00FF);
        CRC = crch <<8| crcl;
        //if (CRC==Data[length-2]*256+Data[length-1]) FLG=1; else FLG=0;
        if (CRC==(Data[length-2]<<8|Data[length-1])) FLG=1; else FLG=0;
      }

 time_t rawtime;
 struct tm * timeinfo;
 char buffer [80];
 char buffer1 [80];
void receivedata(){
 // postTrans();
  while (Serial.available()>0)
  {
    a=millis()-Time1;
    Time1=millis(); 
    if(a>=800) {j=0;}
    RxData[j]=Serial.read();
    j+=1;
    if (j==11) {FLG=0;CRC_RX(RxData,11);j=0;}
  }
      
  if(FLG==1){
      digitalWrite(14,HIGH);
      
      String d= "Data/";
      d=d+dem;
      String date=d+"/Date";
      String timE=d+"/Time";
      Firebase.setString(timE,buffer);
      String hour=d+"/Hour";
      String minu=d+"/Minute";
      String second=d+"/Second";
       
      
     // Firebase.setString("STARTup","ok"); 
      Firebase.setInt(hour,(int)RxData[3]<<8|RxData[4]); 
      Firebase.setInt(minu,(int)RxData[5]<<8|RxData[6]); 
      Firebase.setInt(second,(int)RxData[7]<<8|RxData[8]);
      
      Firebase.setString(date,buffer1);
      Firebase.setInt("numberdata",dem);
      digitalWrite(14,LOW);
      }
  
      if(FLG==0) //digitalWrite(0,LOW);
      {//Firebase.setString("STARTup","fail"); 
     // Firebase.setInt("Rx0",RxData[0]); 
      //Firebase.setInt("Rx1",RxData[1]); 
     //// Firebase.setInt("Rx2",RxData[2]); 
     // Firebase.setInt("Rx3",RxData[3]); 
     // Firebase.setInt("Rx4",RxData[4]); 
    //  Firebase.setInt("Rx5",RxData[5]); 
    //  Firebase.setInt("Rx6",RxData[6]); 
    //  Firebase.setInt("Rx7",RxData[7]); 
      digitalWrite(14,LOW);
      dem--;}
 
      FLG=0;
      dem++;
     // preTrans();
  
};
void Request(){
      int k=0;
      for(k=0;k<8;k++)
      {Serial.write(TxMsg[k]);
      delayMicroseconds(1200);
      };  
}
void setup(){
  Time1=0;
  //pinMode(MAX485_RE_NEG, OUTPUT);
 // pinMode(MAX485_DE, OUTPUT);
  pinMode(14,OUTPUT);
  digitalWrite(14,LOW);
  // Init in receive mode
 // digitalWrite(MAX485_RE_NEG, 0);
 // digitalWrite(MAX485_DE, 0);
    Serial.begin(9600,SERIAL_8E1);
   /*  int k=0;
      for(k=0;k<8;k++)
      {Serial.write(TxMsg[k]);
      delayMicroseconds(1200);
      };*/  
    //Serial.swap();
  //mySerial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  };
  //Serial.println();
  //Serial.print("connected: ");
  //Serial.println(WiFi.localIP());
  configTime(timezone * 3600, dst * 0, "pool.ntp.org", "time.nist.gov");
  //Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
    //Serial.print(".");
    delay(1000);
  }
  
      
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("STARTup","ready"); 
  dem= Firebase.getInt("numberdata")+1;
  blinker.attach(5, Request);
}


void loop(){          //xong,chạy ngon, nhớ nối đất chung.

  //while (WiFi.status() == WL_CONNECTED) {
     
      time (&rawtime);
      timeinfo = localtime (&rawtime);
      strftime (buffer,80,"%X",timeinfo);
      strftime (buffer1,80,"%d-%m-%Y",timeinfo);
    
      receivedata();
      //delay(2000);
    //}
  }
