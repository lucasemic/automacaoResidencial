//coisa pro blynk =====================================================
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL2xGIuGhOn"
#define BLYNK_TEMPLATE_NAME "Lucas Michaelsen"
#define BLYNK_AUTH_TOKEN "jYiw-u0k1kXwJdlZFwKayTZjb2yLyT-E"

//conexão wifi
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//id e senha da rede
char ssid[] = "Elizete";
char pass[] = "CEML525818";

#define WIFI_SSID "Elizete"
#define WIFI_PASSWORD "CEML525818"

//coisa pro servo =====================================================
#include <ESP32Servo.h>
static const int servoPin = 21;
Servo servo1;

//Coisa pro dh11  =====================================================
#include <DHT.h>
#include <Adafruit_Sensor.h>

//Define Modelo do DHT e pino
#define DHTTYPE DHT11
const int DHTPIN = 19;

//Inicialização dht11
DHT dht(DHTPIN, DHTTYPE);
float umid = 0;
float temp = 0;

//coisa pro pir  =====================================================
const int led = 18;
const int sensor = 22;
int state = LOW;
int val = 0;
int mov = 0;

//coisa pro mq2  =====================================================
int MQ2PIN = 25;
bool fumaca = 0;

//coisa pro buzzer  =====================================================
int buz = 14;
int x = 0;

//-----------------------------Conexão da API-------------------------------

//Bibliotecas
#include <Arduino.h>
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#elif __has_include(<WiFiNINA.h>)
#include <WiFiNINA.h>
#elif __has_include(<WiFi101.h>)
#include <WiFi101.h>
#elif __has_include(<WiFiS3.h>)
#include <WiFiS3.h>
#endif
#include <ESP32Time.h>
#include <ESP_Google_Sheet_Client.h>
#include <GS_SDHelper.h>



ESP32Time rtc(3600);
unsigned long ms = 0;
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif
void tokenStatusCallback(TokenInfo info);

//Infos da Planilha
#define PROJECT_ID "api-dos-guri"
#define CLIENT_EMAIL "conta-de-servico-dos-guri@api-dos-guri.iam.gserviceaccount.com"
#define USER_EMAIL "gustavo_gaida@estudante.sesisenai.org.br"
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDnFFDq2VpZXdia\nFbRaPwkHTUcEVM6tjhduTNV3TyR3fkvSz/P7AXY2A4A/hXcSWtbutQXjEjd/mhFU\nBCePYsbN2oGJ01f9/riSkcbd/dSGBFuGAOnDwE3wOTI41S0gpTfwWB151pvTZAiT\nppF2n67ODiPr7OF3A6YFu+a19ivX4VALDPCu+ObESK6EfUBBCbJ4AuigpmFptQar\nguQkI10YC9ivNLwM/Q71eL7+1jhOTMNeuNW7GODdagVVJCz2uiA/8S/kdLI3sol9\nwmifiKUowlC4zSVM9dIXNsNREi4i9Qc6t7QoDj9CJvDQ4ixRPUJdEUZR4vIHcol8\nD/4CE2kbAgMBAAECggEAB0RkIYTcRyaoIEKh7VRsRzXJcz95+u6Ii/9QCU1a0Wfj\nrq0tqg11xYjCUZmJNJwuLwSlnrGVzZDocZnqSpVGRy+and1n1Gh49hODdi08dxFl\nA67K5CKZ8OFgDOgQtWxJMgWmDzexpvhPWBMrPkovbXJM8+dtDjxn3Eu/jVCkjcia\ngwT5Dn3MlqHALy09lWfGvoF4GracG7oGF7Q3yq9F+sb6/z0bMUk8H9OPEBtkoKmD\neSvfHdiRkMAanYijX8r3SSmoLpJfRSDUN8u5UvV7QzgpYci//8gJxOhmBW2oAfEx\np8FD2pNmIJ4ZpYAaOAj7ERwEiojACYA2P+Mm9vpVfQKBgQD752TBCVeesCZZnS+h\nT6OvcYzeQYv5FRkIwYiFBRNcH4f//nrmjb5irK8wx9fquvmKBbdmN/mXs1Y/8Nwt\nEsq5P0rtywE0oY8m8Q97/Slq32mPwWDK46k1WiBY3JMGAuTEtB0BOWLsi20XQUyD\n2CgJAkP+4lbsvs3ZYz5I8+IG/QKBgQDq1jxbaD9nCSeemj3JV4kk5+u4lBQ2Xu4I\nelaf0XyFSaDAvT6LkK1vuafxf6kfTRMhKozg9M4OyAkEIJrGawuUuQei0oH7AJDB\nbd41twkP0R2cdoGgZ9h1H3ecVRWhDquHWbL5nNxMSZLrT2ZwSwg1/yyMealN4UAd\n/PlnOtDH9wKBgHR+mlW7YE3+4H1o9/H9xpEITkEqxvS2ERG/jscVhdKAsoBsy6F7\nw6QWgB5rDSt8tJJj+mDHWiIRyb1gQjKGEkKBRsGZtEEGxhEYQjTw6wqFr2fP4ldx\n2XrW50axGz0YcXuWYCOEyn7iK90pUZ1XhYxFA/UH73Mk+kWiY9eREeJxAoGBAIpm\neGvmpHc1DgSLIp7m2AzIIkRGASOKDv8wGp1V+O0U14i//3yBZ7XQ1QmfEy0/X2bM\njPqHTGmpuqaUEKOfstOTuMxdA/3J94YIGk3N8alAtRLhRMQkb42XXgbknjqtSqoa\nU0CJEcxkEBJeWSEVF2G7YaXojb84YXFLBjGwmBtBAoGAAgWddKBVWe4EKZl9xM3l\nwOrk5w8QU6HgM+73BkvZxGKM6cGpuT/Ng64yCcdELq4E/placDrMZ6YXqTnfEuye\nZWj0r80tECCriQCySlXh6zSqGzYUqHTBo4MyJe+YoOlSKvM32sjEFjaOEWSuRmdv\nMRXx/GKNz/AxJg3sJv7G+0k=\n-----END PRIVATE KEY-----\n";

// Outros
int posicaoServo = 0;
int buzPir = 0;
int buzz = 0;
int buzMq = 0;
int MqLeu = 0;
int PirLeu = 0;

//leds da casa
int ledSala = 12;
int ledCosinha = 2;
int ledQuarto1 = 5;
int ledQuarto2 = 4;
int ledExterno = 13;
//FUNÇÕES



//Funcão temperatura dht11  =====================================================
int dht11Temperatura() {

  float temp = dht.readTemperature();
  delay(500);
  if (isnan(temp)) {
    Serial.println(F("Falha na leitura do sensor"));
  }
  //Retorna a temperatura
  return temp;
}

//Funcão umidade dht11  =====================================================
int dht11Umidade() {

  float umid = dht.readHumidity();
  delay(500);
  if (isnan(umid)) {
    Serial.println(F("Falha na leitura do sensor"));
  }
  //Retorna a umidade
  return umid;
}

//Funcão buzzer  =====================================================
//funciona da seguinte forma: chame a função e coloque como parametro o tempo que o alarme deve soar em segundos
/*void buzzer(int tempo){
  for(int i = 0; i <= tempo; i++){
    digitalWrite(buz, HIGH);
    delay(500);
    digitalWrite(buz, LOW);
    delay(500);
  }
}*/

//Funcão ligar buzzer pelo blynk =====================================================
BLYNK_WRITE(V1)  // Slider Widget for Servo 1 on V0
{
  x = param.asInt();
  if (x == 1) {
    digitalWrite(buz, HIGH);
    buzz = 0;
  };

  if (x == 0) {
    digitalWrite(buz, LOW);
    buzz = 1;
  };
}

//Funcão abrir/fechar servo pelo blynk =====================================================
BLYNK_WRITE(V0) {
  int pos1 = param.asInt();
  if (pos1 == 1) {
    for (int posDegrees = 47; posDegrees <= 126; posDegrees++) {
      servo1.write(posDegrees);
      posicaoServo = posDegrees;
      delay(20);
    }
  };

  

  if (pos1 == 0) {
    for (int posDegrees = 126; posDegrees >= 47; posDegrees--) {
      servo1.write(posDegrees);
      posicaoServo = posDegrees;
      delay(20);
    }
  };
}

//Funcão mq2 =====================================================
int mq2() {
  //Lendo o pino os dados do mq2
  int leitura = digitalRead(MQ2PIN);



  Serial.print("Gas: ");
  Serial.println(leitura);

  if (leitura == 0) {
    Serial.println("FODEO RAPAZIADA");
    digitalWrite(buz, HIGH);
    digitalWrite(led, HIGH);
    MqLeu = 1;
    buzMq = 0;
    delay(3500);
  } else if (x == 0){
    digitalWrite(led, LOW);
    digitalWrite(buz, LOW);
    MqLeu = 0;
    buzMq = 1;
  }

  delay(700);
  return leitura;
}

//Funcão pir =====================================================
void pir() {
  val = digitalRead(sensor);
  if (val == HIGH && mov == 1) {
    digitalWrite(led, HIGH);
    digitalWrite(buz, HIGH);
    delay(500);  // Delay of led is 500
    PirLeu = 1;
    buzPir = 0;
    if (state == LOW) {
      Serial.println("  Motion detected ");
      state = HIGH;
    }
  }else if (x == 0){
    digitalWrite(led, LOW);
    digitalWrite(buz, LOW);
    delay(500);
    PirLeu = 0;
    buzPir = 1;
    if (state == HIGH) {
      Serial.println("The action/ motion has stopped");
      state = LOW;
    }
  }
}

//função auxuliar para pegar se o botão do PIR está ativado no blynk =====================================================
BLYNK_WRITE(V2) {
  mov = param.asInt();
}

//Funções auxiliares que leem se os botões dos leds estão ativados no blynk =====================================================
BLYNK_WRITE(D12) {
  ledSala = param.asInt();
}
BLYNK_WRITE(D4) {
  ledCosinha = param.asInt();
}
BLYNK_WRITE(D5) {
  ledQuarto1 = param.asInt();
}
BLYNK_WRITE(D13) {
  ledQuarto2 = param.asInt();
}
BLYNK_WRITE(D2) {
  ledExterno = param.asInt();
}

//VOID SETUP E LOOP

void setup() {
  //begin para o funcionamento
  Serial.begin(115200);
  //Serial.print("10");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  servo1.attach(servoPin);
  // Serial.print("11");
  dht.begin();

  pinMode(ledSala, INPUT);
  pinMode(ledCosinha, INPUT);
  pinMode(ledQuarto1, INPUT);
  pinMode(ledQuarto2, INPUT);
  pinMode(ledExterno, INPUT);

  //inicializandio pinos
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(buz, OUTPUT);
  pinMode(MQ2PIN, INPUT);

  //----------------------API-------------------------
  //Google sheets
  GSheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);

  //Wifi e hora
  ESP32Time rtc(3600);
  rtc.setTime(30, 24, 15, 17, 1, 2021);

  //Da API
#if defined(ESP32) || defined(ESP8266)
  WiFi.setAutoReconnect(true);
#endif

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  multi.addAP(WIFI_SSID, WIFI_PASSWORD);
  multi.run();
#else
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
    if (millis() - ms > 10000)
      break;
#endif
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  GSheet.setTokenCallback(tokenStatusCallback);

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  GSheet.clearAP();
  GSheet.addAP(WIFI_SSID, WIFI_PASSWORD);
#endif

  GSheet.setPrerefreshSeconds(10 * 60);

  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

void loop() {
  //Horárioo e Wifi
  ESP32Time rtc(3600); 

  Blynk.run();

  //exemplo chamando função do dht11
  temp = dht11Temperatura();
  Serial.print("Temperatura: ");
  Serial.println(temp);
  umid = dht11Umidade();
  Serial.print("Umidade: ");
  Serial.println(umid);
  //exemplo chamando função do mq2
  mq2();
  //exemplo chamando função do pir
  pir();

  //Subir dados
  subirdados();
}

//-----------------Funções da API-------------------

//Subir os dados
void subirdados(){
        
    bool ready = GSheet.ready();

    if (ready && millis() - ms > 5000)
    {
        ms = millis();
        FirebaseJson response;
        Serial.println("\nAppend spreadsheet values...");
        Serial.println("----------------------------");
        FirebaseJson valueRange;
        val = false;
        valueRange.add("majorDimension", "COLUMNS");
        valueRange.set("values/[0]/[0]", subirLedsLigados());
        valueRange.set("values/[1]/[0]", subirHumidade());
        valueRange.set("values/[2]/[0]", subirTemperaura());
        valueRange.set("values/[3]/[0]", subirServoMotor());
        valueRange.set("values/[4]/[0]", subirBuzzer());
        valueRange.set("values/[5]/[0]", subirMq2());
        valueRange.set("values/[6]/[0]", subirPir());
        valueRange.set("values/[8]/[0]", subirLedQuarto1());
        valueRange.set("values/[9]/[0]", subirLedQuarto2());
        valueRange.set("values/[10]/[0]", subirLedCosinha());
        valueRange.set("values/[11]/[0]", subirLedSala());
        valueRange.set("values/[12]/[0]", subirLedExterno());
        valueRange.set("values/[7]/[0]", (getFormattedTime(rtc)));

        bool success = GSheet.values.append(&response /* returned response */, "14Lt0NT0aC6Eo51Oo4mp6mh4ebSmAkCS3P1TYdvcCCQg" /* spreadsheet Id to append */, "Sheet1!B3" /* range to append */, &valueRange /* data range to append */);
        if (success)
            response.toString(Serial, true);
        else
            Serial.println(GSheet.errorReason());
        Serial.println();
#if defined(ESP32) || defined(ESP8266)
        Serial.println(ESP.getFreeHeap());
#elif defined(PICO_RP2040)
        Serial.println(rp2040.getFreeHeap());
#endif
    }
}

//Subir quantia de leds
String subirLedsLigados(){
  int quarto1 = digitalRead(5);
  int quarto2 = digitalRead(4);
  int cosinha = digitalRead(2);
  int sala = digitalRead(12);
  int externo = digitalRead(13);
  int i = 0;
  if(quarto1 == HIGH){
    i = i+1;
  }
  if(quarto2 == HIGH){
    i = i+1;
  }
  if(sala == HIGH){
    i = i+1;
  }
  if(cosinha == HIGH){
    i = i+1;
  }
  if(externo == HIGH){
    i = i+1;
  }

  return String(i);
}
String subirLedQuarto1(){
  int quarto1 = digitalRead(5);
  int i = 0;
  if(quarto1 == HIGH){
    i = i+1;
  }
  return String(i);
}
String subirLedQuarto2(){
  int quarto2 = digitalRead(4);
  int i = 0;
  if(quarto2 == HIGH){
    i = i+1;
  }
  return String(i);
}
String subirLedCosinha(){
  int cosinha = digitalRead(2);
  int i = 0;
  if(cosinha == HIGH){
    i = i+1;
  }
  return String(i);
}
String subirLedSala(){
  int sala = digitalRead(12);
  int i = 0;
  if(sala == HIGH){
    i = i+1;
  }
  return String(i);
}
String subirLedExterno(){
  int externo = digitalRead(13);
  int i = 0;
  if(externo == HIGH){
    i = i+1;
  }
  return String(i);
}

//Subir humidade
String subirHumidade(){
  return String(dht11Umidade());
}

//Subir temperatura
String subirTemperaura(){
  return String(dht11Temperatura());
}

//Subir servomotor
String subirServoMotor(){
  if(posicaoServo == 0){
    posicaoServo = 47;
  }
  return String(posicaoServo);
}

//Subir buzzer
String subirBuzzer(){
  int i = 1;
  if (buzPir == 0 || buzMq == 0 || buzz == 0){
  i = 0;
  buzz = 1;
  buzPir = 1;
  buzMq = 1;}
  return String(i);
}

//Subir MQ2
String subirMq2(){
  int i = MqLeu;
  MqLeu = 0;
  return String(i);
  MqLeu = 0;
}

//Subir PIR
String subirPir(){
  int i = PirLeu;
  PirLeu = 0;
  return String(i);
  PirLeu = 0;
}

//Subir data
String getFormattedTime(ESP32Time rtc) {
  
  struct tm timeinfo = rtc.getTimeStruct();
  
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d", 
           timeinfo.tm_year + 1900,
           timeinfo.tm_mon + 1,    
           timeinfo.tm_mday, 
           timeinfo.tm_hour, 
           timeinfo.tm_min, 
           timeinfo.tm_sec);

  return String(buffer);
}

//Funções da API

void tokenStatusCallback(TokenInfo info)
{
    if (info.status == token_status_error)
    {
        GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
        GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
    }
    else
    {
        GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    }
}