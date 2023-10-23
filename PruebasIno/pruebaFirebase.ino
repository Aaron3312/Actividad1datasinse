#include <WiFi.h>
#include <FirebaseESP32.h>




/*Define the API Key */
#define API_KEY "AIzaSyDf7wTRJCNVYvtnHUVJQsmUcNI6aLK__74"

/*Credenciales Proyecto Firebase */
const char *FIREBASE_HOST="https://console.firebase.google.com/u/1/project/iot-robotarm/database/iot-robotarm-default-rtdb/data/~2F"; 
const char *FIREBASE_AUTH="69d147c63f754cf42d66b03b37d10c979d95ec11";


#define FIREBASE_HOST "https://console.firebase.google.com/u/1/project/iot-robotarm/database/iot-robotarm-default-rtdb/data/~2F"
#define FIREBASE_AUTH "AIzaSyDf7wTRJCNVYvtnHUVJQsmUcNI6aLK__74"

#define WIFI_SSID "Xiaomi"
#define WIFI_PASSWORD "12345678"



FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Conectando a Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Conectado a la red WiFi, dirección IP: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // Sube datos a Firebase
  Firebase.setFloat(firebaseData, "/sensor/temperatura", 25.5);
  delay(1000);
}
