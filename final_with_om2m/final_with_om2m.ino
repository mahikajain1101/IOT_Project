#define SPEED_OF_SOUND 340/10000
#define TRIGGER_PIN 27
#define ECHO_PIN 14
#define BUZZ 26
#define BUZZ2 34
#define SERVOP 15
#define DHTPIN 32
#define DHTTYPE DHT11
#include <ArduinoJson.h>
#include "WiFi.h"
#include "WebServer.h"
#include "HTTPClient.h"
#include "time.h"
#include "DHT.h"
DHT dht(DHTPIN,DHTTYPE);

char* wifi_ssid = "OnePlus Nord2 5G";
char* wifi_pwd = "dontknow";
String cse_ip = "192.168.175.83"; // YOUR IP from ipconfig/ifconfig;
String cse_port = "8080";
String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String ae = "Project_DHT6";
String cnt = "Temperature";
String cnt2 = "Delta";
String ae2 = "Project_Ultra6";
String cnt3 = "Humidity";
WiFiClient client; 
//#include "BluetoothSerial.h"
#include <Servo.h>

Servo myservo;
//BluetoothSerial SerialBT;
//WebServer server(80);

void setup(){

  WiFi.begin(wifi_ssid,wifi_pwd);   
  while(WiFi.status()!=WL_CONNECTED)
  {
   delay(500);
   Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  dht.begin();
  

    myservo.attach(SERVOP);
    myservo.write(45);
    Serial.begin(115200);
//  SerialBT.begin("ESP32Ultra37");
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

}
void createCI1(String& val){
  
  HTTPClient http;
  http.begin(server + ae + "/" + cnt + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");
  Serial.println(code);
  if (code == -1) {
  Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}
void createCI2(String& val){
  
  HTTPClient http;
  http.begin(server + ae2 + "/" + cnt2 + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");
  Serial.println(code);
  if (code == -1) {
  Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}
void createCI3(String& val){
  
  HTTPClient http;
  http.begin(server + ae + "/" + cnt3 + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");
  Serial.println(code);
  if (code == -1) {
  Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}


float controlData[10]={200,200,200,200,200,200,200,200,200,200};
float currentData[10]={};
float lastData[10]={};
float firstEverData[10]={};
int arrayOfFlags[5]={};
int isItFirstObservation=0;
int Greater();
int countGood=0;
int flag=0;
int indices[10]={};

float deltaDistance=20;

int peopleCounter=0;
int breadth = 0;

void emptyObjects()
{
    for(int i=0;i<10;i++)
    {
        currentData[i]=0;
//      lastData[i] = controlData[i];
    }
    countGood = 0;
}
int pos=45;
int delta = 1;
void rotate()
{

    for(int i=0;i<9;i++)
    {
        pos=pos+2*delta;
        myservo.write(pos);
        if(pos>=135 || pos <=45 )
            delta*=-1;
        delay(5);

    }
}

float takeObservation(int i)
{
    float duration, distanceInCm, distanceInInch;

    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distanceInCm = (duration * SPEED_OF_SOUND) / 2;
    distanceInInch = distanceInCm * 0.393;


    currentData[i] =  distanceInCm;
}
void CopyCurrentToLast()
{
    for(int i=0;i<10;i++)
        lastData[i]= currentData[i];
}
void checkFlag()
{
   
    for(int i=0;i<10;i++)
    {
        if(abs(currentData[i]-controlData[i]) < deltaDistance || currentData[i] > 170 || currentData[i] <= 10)
        {
            //  We ignore given observation.
        }
        else
        {
            countGood++;
        }
    }
//    Serial.println(countGood);
    if(countGood >= 2) {
        if (flag == 0)
            flag = 1;
        else if (flag == 1)
            flag = 2;
    }
    else flag =0;
}
void findIndices()
{
    for(int i=0;i<10;i++)
    {
        if( currentData[i] < 200 && abs(currentData[i]-controlData[i]) < deltaDistance && currentData[i]>10) {
            indices[i] = 1;
        }
    }
}
void ifflag1()
{
        int twoInRow = 0;
        findIndices();
        for(int i=0;i<9;i++)
        {
            if(indices[i] && indices[i+1] )
            {
                twoInRow++;
                i++;
            }

        }
        if(countGood >= 6)
        {
            breadth = 2; // 2 people 
        }
        else if(twoInRow == 2) {
            breadth = 2;
        }
        else if(twoInRow == 1 || countGood >=3) {
            breadth = 1;
        }
        else {
            breadth = 0;
        }

       // breadth =1;
}

int compareWithFirst() {

    int count = 0;
    for(int i=0;i<10;i++)
    {
        float diff = firstEverData[i] - lastData[i];
        if(lastData[i] < 10 || firstEverData[i] < 10 || firstEverData[i] > 170 || lastData[i] > 170 )
          continue;        
        if( abs(diff)  >= 10  )
        {
            if(diff > 0)
                count++;
            else 
                count--;
        }
    }  
//    Serial.print("This is count in compareWith First ");
//    Serial.println(count);
        if(count >=0)
            return 1;
        else 
            return 0;
    
}
   
void printArray(float arr[])
{
        for(int i=0;i<10;i++)
        {
            Serial.print(arr[i]);
            Serial.print(" ");
//            SerialBT.print(arr[i]);
//            SerialBT.print(" ");
        }
        Serial.println();
//        SerialBT.println();
}
void loop() {for(int i=0;i<5;i++){
   /*   while(Serial.available() ==0)
      {}
      
*/      int z=Serial.read();
        emptyObjects();
        for(int i=0;i<10;i++)
        {
            rotate(); //18 degrees
            takeObservation(i);
        }
        checkFlag();
//        Serial.println(countGood);
//        Serial.println(flag);
        if (flag == 1)
        {
          for(int i=0;i<10;i++)
            firstEverData[i] = currentData[i];
        }
        if(flag==0 )
        {
            if(compareWithFirst()) {
                peopleCounter += 1 * breadth;
            }
            else {
                peopleCounter -= 1 * breadth;
            }
            breadth = 0;
            for(int i=0;i<10;i++)
                firstEverData[i] = controlData[i];

            CopyCurrentToLast();
            countGood = 0;
        }
        else if(countGood > 2)
        {
            ifflag1();

            for(int i=0;i<10;i++)
            {
                lastData[i] = controlData[i];
            }
        }
        else {
            flag = 0;
            countGood = 0;
        }
    
//  TakeDifferenceWithControlArray(); // Assign grade and flags;
//  TakeDifferenceWithLastArray();    // Last and firstEverData
  CopyCurrentToLast();
//  delay(2500);
    printArray(currentData);
    String h = String(dht.readHumidity()); 
    String t = String(dht.readTemperature());
    String f = String(dht.readTemperature(true));
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  createCI1(t);
  createCI3(h);
  String people = String(peopleCounter);
  createCI2(people);
   
    Serial.println(peopleCounter);
//    SerialBT.println(peopleCounter);
    delay(500);
}
  delay(5000);
     
}
