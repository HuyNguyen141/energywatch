  #include <ESP8266HTTPClient.h>

#include <ESP8266WiFi.h>
#include <time.h>
#include <String.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "nodemcu-6edef.firebaseio.com"
#define FIREBASE_AUTH "SAAcgZRobeLw4eEBmltPc9AbfJyhsvFEwy5lKAyA"
#define MAX485_DE      4
#define MAX485_RE_NEG  5
const char* ssid = "HAKARU_VNPT";
const char* password = "Hakaru+0007";
int timezone = 7;
int dst = 0;
unsigned char RxData[11];
unsigned char i,j,FLG,Rxflag;
unsigned short CRC;
unsigned long Time1,a;
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
        if (CRC==Data[length-2]*256+Data[length-1]) FLG=1; else FLG=0;
        //if (CRC==(Data[length-2]<<8|Data[length-1])) FLG=1; else FLG=0;
      }

void setup() {
  Time1=0;
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
  
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 // Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
 //   Serial.print(".");
    delay(1000);
  }
  configTime(timezone * 3600, dst * 0, "pool.ntp.org", "time.nist.gov");
 // Serial.println("\nWaiting for time");
  while (!time(nullptr)) {
 //   Serial.print(".");
    delay(1000);
  }
//  Serial.println("");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
}

void loop() {
  int t,t2,h,m,s;
  time_t rawtime;
  struct tm * timeinfo;
   char buffer [80];
  char buffer1 [80];
  t=Firebase.getInt("numberdata");
  t2=t+1;
  while (1){ 
  while (WiFi.status() == WL_CONNECTED) {
        while (Serial.available()>0)
  {
    //a= millis()- Time1;
    //Time1=millis();
    //Firebase.setInt("a",a);
   // if(a>500) j=0;
    RxData[j]=Serial.read();
    j+=1;
    if (j==11) {CRC_RX(RxData,11);j=0;Serial.end();
    if(FLG==1){
    
 // Firebase.setInt("Rx_1",(int)RxData[3]<<8|RxData[4]); 
//  Firebase.setInt("Rx_2",(int)RxData[5]<<8|RxData[6]); 
 // Firebase.setInt("Rx_3",(int)RxData[7]<<8|RxData[8]);
   
  
  h=(int)RxData[3]<<8|RxData[4];
  m=(int)RxData[5]<<8|RxData[6];
  s=(int)RxData[7]<<8|RxData[8];
   
 

  //time_t now = time(nullptr);
  //Serial.println(ctime(&now));
  time (&rawtime);
  timeinfo = localtime (&rawtime);

  strftime (buffer,80,"%d-%m-%Y",timeinfo);
  strftime (buffer1,80,"%X",timeinfo);
 // Serial.println(buffer);
  String a1;
  String a;
  a1=String("Data/");
  a1 += t2;
  a += a1;
  a += "/Date";
  String b;

  b += a1;
  b += "/Hour";
  String c;

  c += a1;
  c += "/Minute";
  String d;
 
  d += a1;
  d += "/Second";

  String e;
  e += a1;
  e += "/Time";
 // b="Data/"+(char)t2+"Hour";
 // c="Data/"+(char)t2+"Minute";
 // d="Data/"+(char)t2+"Second";
  Firebase.setInt(b,h);
  if (Firebase.failed()) Firebase.remove(a1);
  else{
  Firebase.setInt(c,m);
  if (Firebase.failed()) Firebase.remove(a1);
  else{
  Firebase.setInt(d,s);
  if (Firebase.failed()) Firebase.remove(a1);
  else{
  Firebase.setString(a,buffer);
  if (Firebase.failed()) Firebase.remove(a1);
  else{
  Firebase.setString(e,buffer1);
  if (Firebase.failed()) Firebase.remove(a1);
  else
  Firebase.setInt("numberdata",t2);
  t2++;
  }}}}
 // delay(500);
    }Serial.begin(9600);
    }}delay(100);}}}
