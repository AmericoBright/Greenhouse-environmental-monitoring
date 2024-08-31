// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <SoftwareSerial.h>

// // 定义SIM7600CE-T的串口
// #define MODEM_RST 5
// #define MODEM_PWRKEY 4
// #define MODEM_POWER_ON 23
// #define MODEM_TX 27
// #define MODEM_RX 26

// // 定义WiFi SSID和密码
// const char* ssid = "李";
// const char* password = "xflj61225";

// // 定义服务器URL
// const char* server = "http://38.207.137.48:8081/api/gpsdata"; // 替换为你的服务器地址

// // 创建GSM客户端
// SoftwareSerial SerialAT(MODEM_RX, MODEM_TX);

// void setup() {
//   // 初始化串口
//   Serial.begin(115200);
//   delay(10);

//   // 初始化WiFi连接
//   Serial.println("Connecting to WiFi...");
//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.print(".");
//   }
//   Serial.println("Connected to WiFi");

//   // 启动SIM7600CE-T模块
//   SerialAT.begin(9600);
//   delay(3000);

//   // 获取模块信息
//   Serial.println("Modem Info: ");
//   Serial.println(getModemInfo());
// }

// void loop() {
//   // 读取GPS数据
//   String gpsData = getGpsData();
//   if (gpsData.length() > 0) {
//     // 打印解析后的GPS数据
//     Serial.println("Parsed GPS Data: " + gpsData);
//     // 发送GPS数据到服务器
//     sendGpsData(gpsData);
//   }

//   // 等待10秒钟再读取下一次
//   delay(10000);
// }

// String getModemInfo() {
//   // 发送AT指令获取模块信息
//   SerialAT.println("AT+CGMM");
//   delay(1000);
//   String response = "";
//   while (SerialAT.available()) {
//     response += char(SerialAT.read());
//   }
//   return response;
// }

// String getGpsData() {
//   // 发送AT指令获取GPS信息
//   SerialAT.println("AT+CGNSINF");
//   delay(1000);
//   String response = "";
//   while (SerialAT.available()) {
//     response += char(SerialAT.read());
//   }
//   Serial.println("GPS Data: " + response);

//   // 解析GPS数据
//   // 示例数据: 2927.353048,N,10631.718533,E,020624,080031.0,230.9,0.0,84.4
//   String gpsData = parseGpsData(response);
//   return gpsData;
// }

// String parseGpsData(String gpsData) {
//   // 解析GPS数据并返回JSON格式的字符串
//   gpsData.trim();
//   String values[8];
//   int i = 0;
//   while (gpsData.length() > 0 && i < 8) {
//     int commaIndex = gpsData.indexOf(",");
//     if (commaIndex == -1) {
//       values[i++] = gpsData;
//       break;
//     } else {
//       values[i++] = gpsData.substring(0, commaIndex);
//       gpsData = gpsData.substring(commaIndex + 1);
//     }
//   }

//   // 构建JSON字符串
//   String jsonData = "{";
//   jsonData += "\"latitude\":\"" + values[0] + "\",";
//   jsonData += "\"longitude\":\"" + values[2] + "\",";
//   jsonData += "\"date\":\"" + values[4] + "\",";
//   jsonData += "\"time\":\"" + values[3] + "\",";
//   jsonData += "\"speed\":\"" + values[5] + "\",";
//   jsonData += "\"altitude\":\"" + values[6] + "\",";
//   jsonData += "\"direction\":\"" + values[7] + "\"";
//   jsonData += "}";
//   return jsonData;
// }

// void sendGpsData(String jsonData) {
//   // 创建HTTP客户端
//   HTTPClient http;
//   http.begin(server);
//   http.addHeader("Content-Type", "application/json");

//   // 发送HTTP POST请求
//   int httpResponseCode = http.POST(jsonData);
//   if (httpResponseCode > 0) {
//     String response = http.getString();
//     Serial.println("HTTP Response code: ");
//     Serial.println(httpResponseCode);
//     Serial.println("Response: ");
//     Serial.println(response);
//   } else {
//     Serial.print("Error on sending POST: ");
//     Serial.println(httpResponseCode);
//   }

//   // 结束HTTP请求
//   http.end();
// }
//}

#include <WiFi.h>
#include <HTTPClient.h>

// 定义WiFi SSID和密码
const char* ssid = "李";
const char* password = "xflj61225";

// 定义本地服务器URL
const char* server = "http://192.168.69.179:8081/api/gpsdata"; // 替换为你的本地服务器地址

void setup() {
  // 初始化串口
  Serial.begin(115200);
  delay(10);

  // 初始化WiFi连接
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // 发送固定的JSON数据到服务器
  sendGpsData();
}

void loop() {
  // 等待10秒钟再发送下一次
  delay(10000);
  sendGpsData();
}

void sendGpsData() {
  // 固定的JSON数据
  // String jsonData = "{";
  // jsonData += "\"latitude\":\"2927.353048\",";
  // jsonData += "\"longitude\":\"10631.718533\",";
  // jsonData += "\"date\":\"020624\",";
  // jsonData += "\"time\":\"080031.0\",";
  // jsonData += "\"speed\":\"230.9\",";
  // jsonData += "\"altitude\":\"0.0\",";
  // jsonData += "\"direction\":\"84.4\"";
  // jsonData += "}";
    String jsonData = "{";
  jsonData += "\"latitude\":\"2927.353048\",";
  jsonData += "\"longitude\":\"10631.718533\",";
  jsonData += "\"date\":\"160624\",";
  jsonData += "\"time\":\"080031.0\",";
  jsonData += "\"speed\":\"230.9\",";
  jsonData += "\"altitude\":\"0.0\",";
  jsonData += "\"direction\":\"84.4\"";
  jsonData += "}";

  // 创建HTTP客户端
  HTTPClient http;
  http.begin(server);
  http.addHeader("Content-Type", "application/json");

  // 发送HTTP POST请求
  int httpResponseCode = http.POST(jsonData);
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println("Response: " + response);
    Serial.println("Sent JSON Data: " + jsonData);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    Serial.println("WiFi Status: " + String(WiFi.status()));
    Serial.println("Server URL: " + String(server));
    Serial.println("Sent JSON Data: " + jsonData);
  }

  // 结束HTTP请求
  http.end();
}