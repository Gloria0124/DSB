/**
 * TemperatureCloudUpload
 *
 * ESP32C3 + DS18B20 温度传感器 → 华为云 IoTDA 上报
 *

 */

#include "config.h"

#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// ============ WiFi ============
WiFiClient espClient;
#if USE_TLS
#include <WiFiClientSecure.h>
WiFiClientSecure espClientSecure;
#endif

// ============ DS18B20 ============
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ============ MQTT ============
PubSubClient mqttClient(espClient);

// ============ 上报 Topic ============
#define HUAWEI_MQTT_REPORT_TOPIC "$oc/devices/" HUAWEI_DEVICE_ID "/sys/properties/report"

// ============ 函数声明 ============
void setupWiFi();
void setupMQTT();
void connectMQTT();
void reportTemperature(float temp);
void blinkLED(int times, int ms);

// ======================== setup ========================
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("[系统] ESP32C3 温度上云启动...");

  // LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_ACTIVE_HIGH ? LOW : HIGH);

  // DS18B20
  sensors.begin();

  // WiFi
  setupWiFi();

  // MQTT
  setupMQTT();
}

// ======================== loop ========================
void loop() {

  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.loop();

  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  if (temp == DEVICE_DISCONNECTED_C) {
    Serial.println("[DS18B20] 传感器未连接或读取失败！");
    blinkLED(3, 200);
    delay(SAMPLE_INTERVAL_MS);
    return;
  }

  Serial.print("Temperature:");
  Serial.println(temp);

  reportTemperature(temp);


  blinkLED(1, 100);

  delay(SAMPLE_INTERVAL_MS);
}

// ======================== WiFi 连接 ========================
void setupWiFi() {
  Serial.print("[WiFi] 正在连接 ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED) {
    //正在连WiFi时，让灯闪烁
    digitalWrite(LED_PIN, LED_ACTIVE_HIGH ? HIGH : LOW);
    delay(250);
    digitalWrite(LED_PIN, LED_ACTIVE_HIGH ? LOW : HIGH);
    delay(250);

    retry++;
    if (retry > 40) {
      ESP.restart();
    }
  }

  // WiFi 连上，让灯保持常亮
  digitalWrite(LED_PIN, LED_ACTIVE_HIGH ? HIGH : LOW);
  Serial.println();
  Serial.print("[WiFi] 连接成功！IP: ");
  Serial.println(WiFi.localIP());
}

// ======================== MQTT 设置 ========================
void setupMQTT() {
#if USE_TLS
  espClientSecure.setInsecure();  
  mqttClient.setClient(espClientSecure);
#endif
  mqttClient.setServer(HUAWEI_MQTT_BROKER, HUAWEI_MQTT_PORT);
  mqttClient.setKeepAlive(60);
}

// ======================== MQTT 连接 ========================
void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.println("[MQTT] 正在连接华为云 IoTDA...");

    if (mqttClient.connect(HUAWEI_MQTT_CLIENT_ID, HUAWEI_MQTT_USERNAME, HUAWEI_MQTT_PASSWORD)) {
      Serial.println("[MQTT] 连接成功！");

      // 连华为云成功 灯熄灭
     
      digitalWrite(LED_PIN, LED_ACTIVE_HIGH ? LOW : HIGH);

    } else {
      // 连接失败，灯5次报警
      blinkLED(5, 100);
      delay(5000);
    }
  }
}

// ======================== 温度上报 ========================
void reportTemperature(float temp) {
  StaticJsonDocument<256> doc;
  JsonArray services = doc.createNestedArray("services");

  JsonObject service = services.createNestedObject();
  service["service_id"] = HUAWEI_SERVICE_ID;

  JsonObject properties = service.createNestedObject("properties");
  properties[HUAWEI_PROPERTY_NAME] = serialized(String(temp, 1));

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);

  Serial.print("[上报] Topic: ");
  Serial.println(HUAWEI_MQTT_REPORT_TOPIC);


  if (mqttClient.publish(HUAWEI_MQTT_REPORT_TOPIC, jsonBuffer)) {
    Serial.println("[上报] 成功！");
  } else {
    Serial.println("[上报] 失败！");
  }
}

// ======================== LED 闪烁 ========================
void blinkLED(int times, int ms) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, LED_ACTIVE_HIGH ? HIGH : LOW);
    delay(ms);
    digitalWrite(LED_PIN, LED_ACTIVE_HIGH ? LOW : HIGH);
    delay(ms);
  }
}
