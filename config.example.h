/**
 * config.example.h — 配置模板
 *
 * 使用方法：
 *   1. 复制本文件并重命名为 config.h
 *   2. 在 config.h 中填写你自己的 WiFi 和华为云参数
 *   3. 不要把真实 config.h 上传到公开仓库！
 */

#ifndef CONFIG_H
#define CONFIG_H

// ======================== WiFi 配置 ========================
#define WIFI_SSID     "你的WiFi名称"
#define WIFI_PASSWORD "你的WiFi密码"

// =================== 华为云 IoTDA 配置 ====================
// 在华为云 IoTDA 控制台 → 设备详情 → 接入信息 中获取以下参数
#define HUAWEI_DEVICE_ID          "你的设备ID"           // 例如: 6412xxx_xxx
#define HUAWEI_MQTT_CLIENT_ID     "你的MQTT客户端ID"     // 通常与 DEVICE_ID 相同
#define HUAWEI_MQTT_USERNAME      "你的MQTT用户名"       // 通常与 DEVICE_ID 相同
#define HUAWEI_MQTT_PASSWORD      "你的MQTT密码/密钥"    // 设备密钥或生成的密码

// MQTT 接入地址（在 IoTDA 控制台 → 总览 → 接入信息 中查看）
#define HUAWEI_MQTT_BROKER        "你的MQTT接入地址"     // 例如: a123bcde.iot-mqtts.cn-north-4.myhuaweicloud.com
#define HUAWEI_MQTT_PORT          1883                   // 普通MQTT用1883，TLS用8883

// =================== 产品模型配置 ========================
// 这两个值必须和 IoTDA 产品模型中定义的完全一致（区分大小写）
#define HUAWEI_SERVICE_ID         "Temperature"
#define HUAWEI_PROPERTY_NAME      "temperature"

// =================== TLS 配置 ============================
#define USE_TLS                   0     // 课堂演示用0（普通MQTT），正式项目建议用1（MQTTS）

// =================== 硬件引脚配置 ========================
#define ONE_WIRE_BUS              3     // DS18B20 数据引脚，课堂推荐 GPIO3，旧版可用 GPIO2
#define LED_PIN                   10    // LED 引脚，必须串联 330Ω 限流电阻
#define LED_ACTIVE_HIGH           1     // 1=高电平点亮，0=低电平点亮

// =================== 采样间隔 ============================
#define SAMPLE_INTERVAL_MS        5000  // 温度采样间隔（毫秒）

#endif // CONFIG_H
