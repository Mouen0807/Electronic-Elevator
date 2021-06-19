#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include <string>
#include <SoftwareSerial.h>
SoftwareSerial mySerialWithArduino(4, 5);  //D2, D1

using namespace std;

//connection information
const char* SSID = "watchDogs";
const char* PASSWORD = "mdkf0807";
char localLevel[] = "0";
const int port = 9090;
bool test=true;
String s;
bool drapeau = true;


char fromArduino;
char *tmp ="";
int size_tmp = 0;


ESP8266WebServer webServer(port); // 

void setup() {
  mySerialWithArduino.begin(115200);
  Serial.begin(115200);
  
  //Mode de Connexion
  WiFi.mode(WIFI_STA);
  //Démarrage de la connexion
  WiFi.begin(SSID,PASSWORD);

  //Mise en place d'un serveur web
  config_rest_server_routing();
  webServer.begin();
  delay(1000);
  Serial.println("");
  Serial.println("ESP 8266 disponible à l'adresse :" + WiFi.localIP().toString());
}

void config_rest_server_routing()
{
    webServer.on("/api/", HTTP_GET, []() {
        webServer.send(200, "text/html",
                    "Welcome to the ESP8266 REST Web Server");
    });
    webServer.on("/api/startElevator", HTTP_GET,startElevator);
    webServer.on("/api/stopElevator", HTTP_GET, stopElevator);
    webServer.on("/api/goToLevel", HTTP_GET, goToLevel);
    webServer.on("/api/goToLevelInterior", HTTP_GET, goToLevelInterior);
    webServer.on("/api/actualLevel", HTTP_GET, actualLevel);
    /*webServer.onNotFound(handleNotFound);*/
}
void sendCORS(){
        webServer.sendHeader("Access-Control-Allow-Origin", "*",true);
        
}
/*void handleNotFound()
{
    if (webServer.method() == HTTP_OPTIONS)
    {
        webServer.sendHeader("Access-Control-Allow-Origin", "*");
        webServer.sendHeader("Access-Control-Max-Age", "10000");
        webServer.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
        webServer.sendHeader("Access-Control-Allow-Headers", "*");
        webServer.send(204);
    }
    else
    {
        webServer.send(404, "text/plain", "");
    }
}*/
void faireVarier(char* localLevel){
  if(drapeau){
     localLevel[0]='1';
     drapeau=!drapeau;
  }
  else{
     localLevel[0]='2';
     drapeau=!drapeau;
  }
  
}

// http://192.168.1.100/api/actualLevel
void actualLevel(){
  sendCORS();
  delay(2);
  //faireVarier(localLevel);
  webServer.send(200 ,"text/html", localLevel);
  Serial.print("actual Level ");
  Serial.print(localLevel);
  Serial.println(" show from ESP8266 "+WiFi.localIP().toString());
}

// http://192.168.1.100/api/goToLevel?number=?
void goToLevel(){
    String response;
   if(webServer.args()>0){
       if(webServer.argName(0)=="number"){
         //envoyer reponse à arduino pour arrêter
         response="add level: "+ webServer.arg(0)+ " to pile" ;
         Serial.println("add level: "+ webServer.arg(0)+ " to pile");
         char x = webServer.arg(0)[0];
         mySerialWithArduino.write(x);
       }
       else{
          response = "Not recognize argument";
       }
   }
   else{
      response="not argument available on route startElevator on IP Adresse: "
              +WiFi.localIP().toString();  
      
   }
  
  sendCORS();
  delay(2);
  webServer.send(200 ,"text/html", "");
}

// http://192.168.1.100/api/goToLevelInterior?number=?
void goToLevelInterior(){
    String response;
   if(webServer.args()>0){
       if(webServer.argName(0)=="number"){
         //envoyer reponse à arduino pour arrêter
         response="add level: "+ webServer.arg(0)+ " to pile" ;
         Serial.println("add level: "+ webServer.arg(0)+ " to pile");
         char x = webServer.arg(0)[0];
         mySerialWithArduino.write(x);
       }
       else{
          response = "Not recognize argument";
       }
   }
   else{
      response="not argument available on route startElevator on IP Adresse: "
              +WiFi.localIP().toString();  
      
   }
  
  sendCORS();
  delay(2);
  webServer.send(200 ,"text/html", "");
}

// http://192.168.1.10/api/startElevator?start=true
void startElevator(){

  String response;
   if(webServer.args()>0){
       if(webServer.argName(0)=="start" && webServer.arg(0)=="true"){
         //envoyer reponse à arduino pour arrêter
         response="Start Elevator";
         Serial.println("Start Elevator");
       }
       else{
          response = "Not recognize argument";
       }
   }
   else{
      response="not argument available on route startElevator on IP Adresse: "
              +WiFi.localIP().toString();  
      
   }
  
  sendCORS();
  delay(2);
  webServer.send(200 ,"text/html", "");
}
//http://192.168.1.100/api/stopElevator?stop=true
void stopElevator(){
   String response;
   if(webServer.args()>0){
       if(webServer.argName(0)=="stop" && webServer.arg(0)=="true"){
         //envoyer reponse à arduino pour arrêter
         response="stop Elevator";
         Serial.println(response);
       }
       else{
          response = "Not recognize argument";
       }
   }
   else{
      response="par d'argument fournit pour la route stopElevator à l'adresse:"
              +WiFi.localIP().toString();  
      
   }
   sendCORS();
   delay(2);
   webServer.send(200 ,"text/html", "");
   
}

String convertToString(char a){
  String s;
  s+=a;
  return s;
}



void loop() {
      
      if(Serial.available()>0)
      {
        byte x = Serial.read();
        mySerialWithArduino.write(x);
      }
      if(mySerialWithArduino.available()>0)
      {
        fromArduino = (char)mySerialWithArduino.read();
        
        
        localLevel[0] = fromArduino;
        Serial.println(localLevel);
        
        
      }
    
    if(WiFi.isConnected()){
       delay(2);
       webServer.handleClient(); //prise en charge des clients
       /*Serial.println(WiFi.localIP().toString());     */   
    }
    else{
      //webServer.onNotFound(handleNotFound);
    }
}
