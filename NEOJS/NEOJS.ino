#include <ArduinoOTA.h>
#ifdef ESP32
#include <FS.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESP8266mDNS.h>
#endif
#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <Adafruit_NeoPixel.h>
#include <elk.h> 

#define ALLOC     4096
#define LED_PIN   D2
#define LED_COUNT 8
#define DEBUG     0

const char* ssid = "*";
const char* password = "*";
const char * hostName = "NEOJS";
const char* http_username = "admin";
const char* http_password = "admin";
String serial_Repl = "";

struct  js *js = js_create(malloc(ALLOC), ALLOC);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

extern "C" void Neo_show() { strip.show(); }
extern "C" void Neo_clear() { strip.clear(); }
extern "C" void Neo_setPixelColor(uint16_t n, int r, int g, int b) { strip.setPixelColor(n, strip.Color(r, g, b)); }
extern "C" void Sys_delay(unsigned long milli) { delay(milli); }
extern "C" unsigned long Sys_millis() { millis(); }
extern "C" void Sys_print(jsval_t v) { Serial.println(js_str(js, v)); }
extern "C" int Neo_WheelR(int wheelpos) { return WheelR(wheelpos); }
extern "C" int Neo_WheelG(int wheelpos) { return WheelG(wheelpos); }
extern "C" int Neo_WheelB(int wheelpos) { return WheelB(wheelpos); }
extern "C" int Neo_numPixels(void) { return strip.numPixels(); }

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  jsval_t v;#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#ifdef ESP32
#include <FS.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESP8266mDNS.h>
#endif
#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <Adafruit_NeoPixel.h>
#include <elk.h> 

#define ALLOC     4096
#define LED_PIN   D2
#define LED_COUNT 8
#define DEBUG     0

struct Config {
  char wifi_sta_ssid[64];
  char wifi_sta_pass[64];
  char wifi_ap_ssid[64];
  char wifi_ap_pass[64];
  char hostName[64];
  char http_username[64];
  char http_password[64];
};

Config config;
String serial_Repl = "";
struct  js *js = js_create(malloc(ALLOC), ALLOC);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

extern "C" void Neo_show() { strip.show(); }
extern "C" void Neo_clear() { strip.clear(); }
extern "C" void Neo_setPixelColor(uint16_t n, int r, int g, int b) { strip.setPixelColor(n, strip.Color(r, g, b)); }
extern "C" void Sys_delay(unsigned long milli) { delay(milli); }
extern "C" unsigned long Sys_millis() { millis(); }
extern "C" void Sys_print(jsval_t v) { Serial.println(js_str(js, v)); }
extern "C" int Neo_WheelR(int wheelpos) { return WheelR(wheelpos); }
extern "C" int Neo_WheelG(int wheelpos) { return WheelG(wheelpos); }
extern "C" int Neo_WheelB(int wheelpos) { return WheelB(wheelpos); }
extern "C" int Neo_numPixels(void) { return strip.numPixels(); }

void setup(){
      
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  
  if(!SPIFFS.begin()) {
    if(DEBUG) { Serial.println(F("SPIFFS Initialization ... failed")); }
  } else { if(DEBUG) { Serial.println(F("SPIFFS Initialize....ok")); }}

  if(!loadConfig(config)) {
    if(DEBUG) { Serial.println(F("Config Initialization ... failed")); }
  } else { if(DEBUG) { Serial.println(F("Config Initialize....ok")); }}

  strip.begin();
  strip.show();
  strip.setBrightness(50);
  
  elkInit();  

  WiFi.mode(WIFI_AP_STA);

  if(config.wifi_ap_pass != "")
    WiFi.softAP(config.wifi_ap_ssid, config.wifi_ap_pass);
  else
    if(config.wifi_ap_ssid != "")
      WiFi.softAP(config.wifi_ap_ssid);
    else
      WiFi.softAP(config.hostName);
    
  if(config.wifi_sta_ssid != "") {
    if(config.wifi_sta_pass != "")
      WiFi.begin(config.wifi_sta_ssid, config.wifi_sta_pass);
    else
      WiFi.begin(config.wifi_sta_ssid);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      if(DEBUG) { Serial.println(F("STA: Conection Failed!")); }
      WiFi.disconnect(false);
      delay(1000); //FIXME NO! delays :)
      if(config.wifi_sta_pass != "")
        WiFi.begin(config.wifi_sta_ssid, config.wifi_sta_pass);
      else
        WiFi.begin(config.wifi_sta_ssid);
    }
  }

  ArduinoOTA.onStart([]() { events.send("Update Start", "ota"); });
  ArduinoOTA.onEnd([]() { events.send("Update End", "ota"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) { char p[32]; sprintf(p, "Progress: %u%%\n", (progress/(total/100))); events.send(p, "ota");});
  ArduinoOTA.onError([](ota_error_t error) { if(error == OTA_AUTH_ERROR) events.send("Auth Failed", "ota"); else if(error == OTA_BEGIN_ERROR) events.send("Begin Failed", "ota"); else if(error == OTA_CONNECT_ERROR) events.send("Connect Failed", "ota"); else if(error == OTA_RECEIVE_ERROR) events.send("Recieve Failed", "ota"); else if(error == OTA_END_ERROR) events.send("End Failed", "ota");});
  ArduinoOTA.setHostname(config.hostName);
  ArduinoOTA.begin();

  MDNS.addService("http","tcp",80);

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  events.onConnect([](AsyncEventSourceClient *client){
    client->send("hello!",NULL,millis(),1000);
  });
  server.addHandler(&events);

#ifdef ESP32
  server.addHandler(new SPIFFSEditor(SPIFFS, config.http_username,config.http_password));
#elif defined(ESP8266)
  server.addHandler(new SPIFFSEditor(config.http_username,config.http_password));
#endif

  server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = "[";
    int n = WiFi.scanComplete();
    if(n == -2){
      WiFi.scanNetworks(true);
    } else if(n){
      for (int i = 0; i < n; ++i){
        if(i) json += ",";
        json += "{";
        json += "\"rssi\":"+String(WiFi.RSSI(i));
        json += ",\"ssid\":\""+WiFi.SSID(i)+"\"";
        json += ",\"bssid\":\""+WiFi.BSSIDstr(i)+"\"";
        json += ",\"channel\":"+String(WiFi.channel(i));
        json += ",\"secure\":"+String(WiFi.encryptionType(i));
        json += ",\"hidden\":"+String(WiFi.isHidden(i)?"true":"false");
        json += "}";
      }
      WiFi.scanDelete();
      if(WiFi.scanComplete() == -2){
        WiFi.scanNetworks(true);
      }
    }
    json += "]";
    request->send(200, "application/json", json);
    json = String();
  });
  
  server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(ESP.getFreeHeap()));
  });
  
  server.on("/reload", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(elkReload()));
  }); 
   
  //get heap status, analog input value and all GPIO statuses in one json call
  server.on("/all", HTTP_GET, [](AsyncWebServerRequest *request) {
    String json = "{";
    json += "\"heap\":" + String(ESP.getFreeHeap());
    json += ", \"analog\":" + String(analogRead(A0));
    json += ", \"gpio\":" + String((uint32_t)(((GPI | GPO) & 0xFFFF) | ((GP16I & 0x01) << 16)));
    json += "}";
    request->send(200, "text/json", json);
    json = String();
  });
  
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm");
  server.onNotFound([](AsyncWebServerRequest *request){
    int headers = request->headers();
    int i;
    for(i=0;i<headers;i++){
      AsyncWebHeader* h = request->getHeader(i);
    }
    int params = request->params();
    for(i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
    }
    request->send(404);
  });
  
  server.onFileUpload([](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final){

  });
  
  server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){

  });
  server.begin();
}

void loop(){
  elkLoop();
  ArduinoOTA.handle();
  ws.cleanupClients();
}

bool loadConfig(Config &config) {

  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    if(DEBUG) { Serial.println(F("Failed to open config file")); }
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    if(DEBUG) { Serial.println(F("Config file size is too large")); }
    return false;
  }

  StaticJsonBuffer<512> jsonBuffer;

  JsonObject &root = jsonBuffer.parseObject(configFile);

  strlcpy(config.wifi_sta_ssid, root["wifi_sta_ssid"] | "", sizeof(config.wifi_sta_ssid));
  strlcpy(config.wifi_sta_pass, root["wifi_sta_pass"] | "", sizeof(config.wifi_sta_pass));
  strlcpy(config.wifi_ap_ssid, root["wifi_ap_ssid"] | "NEOJS", sizeof(config.wifi_ap_ssid));
  strlcpy(config.wifi_ap_pass, root["wifi_ap_pass"] | "", sizeof(config.wifi_ap_pass));
  strlcpy(config.hostName, root["hostName"] | "NEOJS", sizeof(config.hostName));
  strlcpy(config.http_username, root["http_username"] | "admin", sizeof(config.http_username));
  strlcpy(config.http_password, root["http_password"] | "admin", sizeof(config.http_password));

  configFile.close();

  if (!root.success()) {
    if(DEBUG) { Serial.println(F("Failed to read file, using default configuration")); }
    return false;
  }
  return true;
}

void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  jsval_t v;

  if(type == WS_EVT_CONNECT){
    client->printf("Connected to NEOJS WebREPL (Elk %s)", ELK_VER);
    client->ping();
  } else if(type == WS_EVT_DATA){
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    String msg = "";
    if(info->final && info->index == 0 && info->len == len){
      if(info->opcode == WS_TEXT){
        for(size_t i=0; i < info->len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < info->len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }
      v = js_eval(js, msg.c_str(), 0);
      client->printf("%s", msg.c_str());
      client->printf("%s", js_str(js, v));      
      js_gc(js, v);
    } else {
      if(info->opcode == WS_TEXT){
        for(size_t i=0; i < len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }
      v = js_eval(js, msg.c_str(), 0);
      client->printf("%s", msg.c_str());
      client->printf("%s", js_str(js, v));
      js_gc(js, v);
    }
  }
}

void elkLoop(){
  jsval_t v;
  char c = 0;
  
  if(Serial.available() > 0) {
    c = Serial.read();
    if(c == '\n' || c == '\r') {
      v = js_eval(js, serial_Repl.c_str(), 0);
      Serial.println(js_str(js, v));
      js_gc(js, v);
      serial_Repl = "";
    } 
    else
      serial_Repl += c;
  }  
  js_eval(js, "loop();", 0);
}

String elkReload(){
  ws.printfAll("Connected to NEOJS WebREPL (Elk %s)", ELK_VER);
  elkInit();
  return String("Reloading Elk VM ...");
}

void elkInit() {
  if(DEBUG) { Serial.print(F("Starting VM (Elk ")); Serial.print(ELK_VER); Serial.print(F(") ")); }
  js = js_create(malloc(ALLOC), ALLOC);
  jsval_t v;
  String buffer;
  char c = 0;
  File f;
  
  js_import(js, "millis", (uintptr_t) Sys_millis, "i");
  js_import(js, "delay", (uintptr_t) Sys_delay, "vi");
  js_import(js, "print", (uintptr_t) Sys_print, "vj");
  js_import(js, "show", (uintptr_t) Neo_show, "v");
  js_import(js, "clear", (uintptr_t) Neo_clear, "v");
  js_import(js, "setPixelColor", (uintptr_t) Neo_setPixelColor, "viiii");
  js_import(js, "WheelR", (uintptr_t) Neo_WheelR, "ii");
  js_import(js, "WheelG", (uintptr_t) Neo_WheelG, "ii");
  js_import(js, "WheelB", (uintptr_t) Neo_WheelB, "ii");
  js_import(js, "jsinfo", (uintptr_t) js_info, "sm");
  js_import(js, "numPixels", (uintptr_t) Neo_numPixels, "i"); 
  
  f = SPIFFS.open("/init.js", "r");
  if (!f) {
    if(DEBUG) { Serial.println(F("init.js file open failed")); }
  } else {
    if(DEBUG) { Serial.println(F("Reading init.js script from File:")); }
    while (f.available()) {
      c = f.read();
      if(DEBUG) {Serial.write(c);}
      buffer += c;
    }  
    f.close();  //Close file
    if(DEBUG) { Serial.println(F("File Closed")); }
    v = js_eval(js, buffer.c_str(), 0);
    if(DEBUG) { Serial.print(F("js_eval() result: ")); Serial.println(js_str(js, v)); }
    js_gc(js, v);
    buffer = "";
  }
  Serial.printf("Connected to NEOJS SerialREPL (Elk %s)\n", ELK_VER);
}

int WheelR(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 255 - Pos * 3; }
  if(Pos < 170) { return 0; }
  Pos -= 170;
  return Pos * 3;
}

int WheelG(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 0; }
  if(Pos < 170) { Pos -= 85; return Pos * 3; }
  Pos -= 170;
  return 255 - Pos * 3;
}

int WheelB(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return Pos * 3; }
  if(Pos < 170) { Pos -= 85; return 255 - Pos * 3; }
  return 0;
}


  if(type == WS_EVT_CONNECT){
    client->printf("Connected to NEOJS WebREPL (Elk %s)", ELK_VER);
    client->ping();
  } else if(type == WS_EVT_DATA){
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    String msg = "";
    if(info->final && info->index == 0 && info->len == len){
      if(info->opcode == WS_TEXT){
        for(size_t i=0; i < info->len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < info->len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }
      v = js_eval(js, msg.c_str(), 0);
      client->printf("%s", msg.c_str());
      client->printf("%s", js_str(js, v));      
      js_gc(js, v);
    } else {
      if(info->opcode == WS_TEXT){
        for(size_t i=0; i < len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for(size_t i=0; i < len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }
      v = js_eval(js, msg.c_str(), 0);
      client->printf("%s", msg.c_str());
      client->printf("%s", js_str(js, v));
      js_gc(js, v);
    }
  }
}

void elkLoop(){
  jsval_t v;
  char c = 0;
  
  if(Serial.available() > 0) {
    c = Serial.read();
    if(c == '\n' || c == '\r') {
      v = js_eval(js, serial_Repl.c_str(), 0);
      Serial.println(js_str(js, v));
      js_gc(js, v);
      serial_Repl = "";
    } 
    else
      serial_Repl += c;
  }  
  js_eval(js, "loop();", 0);
}

String elkReload(){
  ws.printfAll("Connected to NEOJS WebREPL (Elk %s)", ELK_VER);
  elkInit();
  return String("Reloading Elk VM ...");
}

void elkInit() {
  js = js_create(malloc(ALLOC), ALLOC);
  
  jsval_t v;
  String buffer;
  char c = 0;
  File f;
  
  js_import(js, "millis", (uintptr_t) Sys_millis, "i");
  js_import(js, "delay", (uintptr_t) Sys_delay, "vi");
  js_import(js, "print", (uintptr_t) Sys_print, "vj");
  js_import(js, "show", (uintptr_t) Neo_show, "v");
  js_import(js, "clear", (uintptr_t) Neo_clear, "v");
  js_import(js, "setPixelColor", (uintptr_t) Neo_setPixelColor, "viiii");
  js_import(js, "WheelR", (uintptr_t) Neo_WheelR, "ii");
  js_import(js, "WheelG", (uintptr_t) Neo_WheelG, "ii");
  js_import(js, "WheelB", (uintptr_t) Neo_WheelB, "ii");
  js_import(js, "jsinfo", (uintptr_t) js_info, "sm");
  js_import(js, "numPixels", (uintptr_t) Neo_numPixels, "i"); 
  
  if(SPIFFS.begin())
  {
    if(DEBUG) { Serial.println("SPIFFS Initialize....ok"); }
    f = SPIFFS.open("/init.js", "r");
    if (!f) {
      if(DEBUG) { Serial.println("init.js file open failed"); }
    } 
    else
    {
      if(DEBUG) { Serial.println("Reading init.js script from File:"); }
      while (f.available()) {
        c = f.read();
        if(DEBUG) {Serial.write(c);}
        buffer += c;
      }  
      f.close();  //Close file
      if(DEBUG) { Serial.println("File Closed"); }
      v = js_eval(js, buffer.c_str(), 0);
      if(DEBUG) { Serial.print("js_eval() result: "); Serial.println(js_str(js, v)); }
      js_gc(js, v);
      buffer = "";
    }
  }
  else
  {
    if(DEBUG) { Serial.println("SPIFFS Initialization ... failed"); }
  }
  Serial.printf("Connected to NEOJS SerialREPL (Elk %s)\n", ELK_VER);
}

void setup(){
      
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(hostName);
  WiFi.begin(ssid, password);
  
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("STA: Failed!\n");
    WiFi.disconnect(false);
    delay(1000);
    WiFi.begin(ssid, password);
  }

  ArduinoOTA.onStart([]() { events.send("Update Start", "ota"); });
  ArduinoOTA.onEnd([]() { events.send("Update End", "ota"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) { char p[32]; sprintf(p, "Progress: %u%%\n", (progress/(total/100))); events.send(p, "ota");});
  ArduinoOTA.onError([](ota_error_t error) { if(error == OTA_AUTH_ERROR) events.send("Auth Failed", "ota"); else if(error == OTA_BEGIN_ERROR) events.send("Begin Failed", "ota"); else if(error == OTA_CONNECT_ERROR) events.send("Connect Failed", "ota"); else if(error == OTA_RECEIVE_ERROR) events.send("Recieve Failed", "ota"); else if(error == OTA_END_ERROR) events.send("End Failed", "ota");});
  ArduinoOTA.setHostname(hostName);
  ArduinoOTA.begin();

  MDNS.addService("http","tcp",80);

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  events.onConnect([](AsyncEventSourceClient *client){
    client->send("hello!",NULL,millis(),1000);
  });
  server.addHandler(&events);

#ifdef ESP32
  server.addHandler(new SPIFFSEditor(SPIFFS, http_username,http_password));
#elif defined(ESP8266)
  server.addHandler(new SPIFFSEditor(http_username,http_password));
#endif
  
  server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(ESP.getFreeHeap()));
  });
  
  server.on("/reload", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", String(elkReload()));
  }); 
   
  //get heap status, analog input value and all GPIO statuses in one json call
  server.on("/all", HTTP_GET, [](AsyncWebServerRequest *request) {
    String json = "{";
    json += "\"heap\":" + String(ESP.getFreeHeap());
    json += ", \"analog\":" + String(analogRead(A0));
    json += ", \"gpio\":" + String((uint32_t)(((GPI | GPO) & 0xFFFF) | ((GP16I & 0x01) << 16)));
    json += "}";
    request->send(200, "text/json", json);
    json = String();
  });
  
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm");
  server.onNotFound([](AsyncWebServerRequest *request){
    int headers = request->headers();
    int i;
    for(i=0;i<headers;i++){
      AsyncWebHeader* h = request->getHeader(i);
    }
    int params = request->params();
    for(i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
    }
    request->send(404);
  });
  
  server.onFileUpload([](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final){

  });
  
  server.onRequestBody([](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){

  });
  
  server.begin();

  strip.begin();
  strip.show();
  strip.setBrightness(50);
  
  Serial.print("Starting VM (Elk "); Serial.print(ELK_VER); Serial.print(") ");
  elkInit();  
}

void loop(){
  elkLoop();
  ArduinoOTA.handle();
  ws.cleanupClients();
}

int WheelR(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 255 - Pos * 3; }
  if(Pos < 170) { return 0; }
  Pos -= 170;
  return Pos * 3;
}

int WheelG(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return 0; }
  if(Pos < 170) { Pos -= 85; return Pos * 3; }
  Pos -= 170;
  return 255 - Pos * 3;
}

int WheelB(int Pos) {
  Pos = 255 - Pos;
  if(Pos < 85) { return Pos * 3; }
  if(Pos < 170) { Pos -= 85; return 255 - Pos * 3; }
  return 0;
}
