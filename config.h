/**
 * config.h — 真实配置文件
 *
 * ⚠️ 不要把本文件上传到公开仓库！包含 WiFi 密码和设备认证信息！
 */

#ifndef CONFIG_H
#define CONFIG_H

// ======================== WiFi 配置 ========================
#define WIFI_SSID     "N"
#define WIFI_PASSWORD "20070124"

// =================== 华为云 IoTDA 配置 ====================
#define HUAWEI_DEVICE_ID          "6a1af58ccbb0cf6bb960105f_esp32c3_01"

// === 从华为云工具生成的完整鉴权信息 ===
#define HUAWEI_MQTT_CLIENT_ID     "6a1af58ccbb0cf6bb960105f_esp32c3_01_0_1_2026053017"
#define HUAWEI_MQTT_USERNAME      "6a1af58ccbb0cf6bb960105f_esp32c3_01"
#define HUAWEI_MQTT_PASSWORD      "17fcfdfd8b77cffca3ee8b556d8a19905a276bfc52ba39cc7fcd7cde810f8383"

// MQTT 接入地址
#define HUAWEI_MQTT_BROKER        "92ac0fc020.st1.iotda-device.cn-north-4.myhuaweicloud.com"
#define HUAWEI_MQTT_PORT          1883

// =================== 产品模型配置 ========================
// 这两个值必须和 IoTDA 产品模型中定义的完全一致（区分大小写）
#define HUAWEI_SERVICE_ID         "Temperature"
#define HUAWEI_PROPERTY_NAME      "temperature"

// =================== TLS 配置 ============================
#define USE_TLS                   0     // 课堂演示用0（普通MQTT），正式项目建议用1（MQTTS）

// =================== 硬件引脚配置 ========================
#define ONE_WIRE_BUS              6     // DS18B20 数据引脚，接 IO6
#define LED_PIN                   12    // CORE-ESP32 板载 LED1 (GPIO12)
#define LED_ACTIVE_HIGH           1     // 高电平点亮

// =================== 采样间隔 ============================
#define SAMPLE_INTERVAL_MS        5000  // 温度采样间隔（毫秒）

#endif // CONFIG_H
