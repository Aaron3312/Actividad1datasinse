//https://smartfarm-2368a-default-rtdb.firebaseio.com/
//        smartfarm-2368a-default-rtdb	
//69x5q2OWo9x9KBD95YbSitTAvYc0ySKDBRiM2dFb
//AIzaSyAFJfZ7gnZrO8uyWI54RUr-ndFc5YpZTNg

#include <WiFi.h>
#include <WiFiClient.h>
#include <FirebaseESP32.h>
//#include <DHT.h>


//#define TecWifi



//////////////////////////////////////////////////////////////////////////////////
//                              INPUT-OUTPUT DEFINITION
//////////////////////////////////////////////////////////////////////////////////
const int outputPin = 16; // pin de salida
const int inputPin = A0; //pin entrada de luz

//////////////////////////////////////////////////////////////////////////////////
//                              DHT CONFIGURATION
//////////////////////////////////////////////////////////////////////////////////
/*
#define DHTPIN 2          // Digital pin 4

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11     // DHT 11
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
//SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  int valorLDR = analogRead(inputPin);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
}
*/
//////////////////////////////////////////////////////////////////////////////////
//                              FIREBASE CONFIGURATION
//////////////////////////////////////////////////////////////////////////////////
/*Define the API Key */
#define API_KEY "AIzaSyDf7wTRJCNVYvtnHUVJQsmUcNI6aLK__74"

/*Credenciales Proyecto Firebase */
const char *FIREBASE_HOST="https://console.firebase.google.com/u/1/project/iot-robotarm/database/iot-robotarm-default-rtdb/data/~2F"; 
const char *FIREBASE_AUTH="69d147c63f754cf42d66b03b37d10c979d95ec11";

// Firebase Data object in the global scope
FirebaseData firebaseData;

bool iterar = true;
//////////////////////////////////////////////////////////////////////////////////
//                              FUNCTION DEFINITION
//////////////////////////////////////////////////////////////////////////////////
//Wifi Function
#ifdef TecWifi
void TecWifiConnection(void);
#else
void HouseWifiConnection(void);
#endif 
 
void EBlink(void);

//////////////////////////////////////////////////////////////////////////////////
//                              WIFI CONFIGURATION
//////////////////////////////////////////////////////////////////////////////////
//If TEC wifi
#ifdef TecWifi
WiFiServer server(80);
extern "C" {
#include "user_interface.h"
#include "wpa2_enterprise.h"
#include "c_types.h"
}


String header;
unsigned long lastTime, timeout = 2000;

String outputState = "apagado"; //almacenar el estado actual de la salida
// SSID to connect to
char ssid[] = "Tec";
char username[] = "L03071799";
char identity[] = "L03071799";
char password[] = "Pinzas0213-";
uint8_t target_esp_mac[6] = {0x24, 0x0a, 0xc4, 0x9a, 0x58, 0x28};

// If House wifi
#else
char ssid[] = "Xiaomi";
char password[] ="12345678";
#endif

//////////////////////////////////////////////////////////////////////////////////
//                                     SETUP
//////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(inputPin, INPUT);
  digitalWrite(outputPin,HIGH);  
  Serial.begin(115200);  
  delay(3000);
  Serial.printf("Inicializando...\n");  
  
  Serial.setDebugOutput(true);
  Serial.printf("SDK version: %s\n", system_get_sdk_version());  
  Serial.printf("Free Heap: %4d\n",ESP.getFreeHeap());
 
  #ifdef TecWifi
  TecWifiConnection();
  #else
  HouseWifiConnection();
  #endif
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  // Setup a function to be called every second
  //dht.begin();
}
//////////////////////////////////////////////////////////////////////////////////
//                              LOOP
//////////////////////////////////////////////////////////////////////////////////
void loop() {
String nodo = "Proyecto-iot";

  while (iterar)
  {
/*
    // escribir datos
   Firebase.setInt(firebaseData, "Sensor", 800);
   Firebase.setInt(firebaseData, "Temperatura", 11);
   Firebase.setString(firebaseData, "Led", "off");
   Serial.println("Los datos se escribieron con éxito");

    Firebase.setString(firebaseData, nodo + "/sensor", "DHT11");
    Firebase.setInt(firebaseData, nodo + "/temperatura", 45);
    Firebase.setBool(firebaseData, nodo + "/alarmas", true);

    // leer datos
     Firebase.getString(firebaseData, nodo + "/sensor");
     Serial.print("El sensor es: ");Serial.println(firebaseData.stringData());
     Firebase.getInt(firebaseData, nodo + "/temperatura");
     Serial.print("La última temperatura fue: ");Serial.println(firebaseData.intData());
     delay(250);
     */
     

    // push de datos
    Firebase.setString(firebaseData, "Led1", "Hola Mundo!");
    /*
    Firebase.pushInt(firebaseData, nodo + "/temperatura", 29);
    delay(150);
    Firebase.pushInt(firebaseData, nodo + "/temperatura", 31);
    delay(150);
    Firebase.pushInt(firebaseData, nodo + "/temperatura", 30);
    delay(150);
    Firebase.pushInt(firebaseData, nodo + "/Humedad", 67);
*/
    iterar = false;
    Firebase.end(firebaseData);
  }
}

//////////////////////////////////////////////////////////////////////////////////
//                              Wifi Functions
//////////////////////////////////////////////////////////////////////////////////
#ifdef TecWifi
void TecWifiConnection(void){
  // Setting ESP into STATION mode only (no AP mode or dual mode)
  wifi_set_opmode(STATION_MODE);

  struct station_config wifi_config;

  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);
  strcpy((char*)wifi_config.password, password);

  wifi_station_set_config(&wifi_config);
  wifi_set_macaddr(STATION_IF,target_esp_mac);
  

  wifi_station_set_wpa2_enterprise_auth(1);

  // Clean up to be sure no old data is still inside
  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();
  wifi_station_clear_enterprise_identity();
  wifi_station_clear_enterprise_username();
  wifi_station_clear_enterprise_password();
  wifi_station_clear_enterprise_new_password();
  
  wifi_station_set_enterprise_identity((uint8*)identity, strlen(identity));
  wifi_station_set_enterprise_username((uint8*)username, strlen(username));
  wifi_station_set_enterprise_password((uint8*)password, strlen((char*)password));

  
  wifi_station_connect();
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
#else
void HouseWifiConnection(void){
       Serial.println("Connecting to ");
       Serial.println(ssid); 
 
       WiFi.begin(ssid, password); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 
}
#endif

void EBlink (void){
  pinMode(outputPin, OUTPUT);
  for (;;){
    digitalWrite(outputPin,HIGH);
    delay(1000);
    digitalWrite(outputPin,LOW);
    delay(1000);
  }

}