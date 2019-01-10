//GDWifi.h
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#include <U8g2lib.h>
#include <WiFiUdp.h>
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/14, /* data=*/27, /* reset=*/U8X8_PIN_NONE);
U8G2_SH1107_64X128_1_4W_HW_SPI u8g2(U8G2_R1, 14,27,33);
struct Time_c {
  char time[6];
} Time_c = {
  "08:30"
};
struct Day
{
  int cod;
  char date[11];
  char range[10];
  char status[20];
};
struct Weather
{
  Day tody;
  Day tom;
  Day afterTom;
  char now[4];
  char pm25[10];
  char city[20];
  char qlty[10];
  char date[24];
  char time[6];
  char title[20];
  char detail1[20];
  char detail2[20];
  char detail3[20];
  char detail4[20];
  // char detail5[16];
} weather = {
    {0,
     "2017-01-17",
     "-- | --C",
     "Loading..."},
    {0,
     "2017-01-18",
     "-- | --C",
     "Loading..."},
    {0,
     "2017-01-19",
     "-- | --C",
     "Loading..."},
    "--",
    "PM25: ---",
    "CityName",
    "Loading",
    "2017-01-17 Tuesday",
    "08:30",
    "推送",
    "本地默认消息",
    "测试",
    "中文测试",
    "中文测试"};
//     // ""};


void startProcess(char *title, int num)
{  
  u8g2.setCursor(14, 30);
  u8g2.print(title);
  u8g2.drawRFrame(9, 17, 110, 30, 5);
  u8g2.drawFrame(14, 36, 100, 6);
  u8g2.drawBox(14, 36, num, 6);
}

void netStartUI(char *title, int num, bool isFirst)
{
  u8g2.setFont(u8g2_font_wqy12_t_gb2312);
  u8g2.firstPage();
  do
  {
    startProcess(title, num);
  } while (u8g2.nextPage());
}
void jsonParse(String j, bool isFirst)
{
  netStartUI("数据解析中...", 20, isFirst);
  StaticJsonDocument<1024> jsonBuffer;
  netStartUI("数据解析中...", 25, isFirst);
  const char *json = j.c_str();
  Serial.println("print json below");
  Serial.println(json);
  Serial.println("json parse start");
  netStartUI("数据解析中...", 30, isFirst);
  DeserializationError error = deserializeJson(jsonBuffer, json);
  if (error) {
    Serial.println("json parse Error!");
    Serial.println(error.c_str());
    Serial.println("****************");
  }
  JsonObject root = jsonBuffer.as<JsonObject>();
  weather.tody.cod = root["value"]["tody"]["status"];
  strcpy(weather.tody.date, root["value"]["tody"]["date"]);
  strcpy(weather.tody.range, root["value"]["tody"]["range"]);
  strcpy(weather.tody.status, root["value"]["tody"]["s"]);
  netStartUI("数据解析中...", 40, isFirst);
  weather.tom.cod = root["value"]["tom"]["status"];
  strcpy(weather.tom.date, root["value"]["tom"]["date"]);
  strcpy(weather.tom.range, root["value"]["tom"]["range"]);
  strcpy(weather.tom.status, root["value"]["tom"]["s"]);
  netStartUI("数据解析中...", 50, isFirst);
  weather.afterTom.cod = root["value"]["afterTom"]["status"];
  strcpy(weather.afterTom.date, root["value"]["afterTom"]["date"]);
  strcpy(weather.afterTom.range, root["value"]["afterTom"]["range"]);
  strcpy(weather.afterTom.status, root["value"]["afterTom"]["s"]);
  netStartUI("数据解析中...", 60, isFirst);
  strcpy(weather.now, root["value"]["tody"]["now"]);
  strcpy(weather.pm25, root["value"]["pm25"]);
  strcpy(weather.city, root["value"]["city"]);
  strcpy(weather.qlty, root["value"]["qlty"]);
  netStartUI("数据解析中...", 70, isFirst);
  strcpy(weather.title, root["value"]["title"]);
  strcpy(weather.detail1, root["value"]["detail"][0]);
  strcpy(weather.detail2, root["value"]["detail"][1]);
  strcpy(weather.detail3, root["value"]["detail"][2]);
  strcpy(weather.detail4, root["value"]["detail"][3]);
  // strcpy(weather.detail4, root["value"]["detail"][4]);
  netStartUI("数据解析中...", 80, isFirst);
  Serial.println("json parse end");
  netStartUI("JsonParse Successful!", 100, isFirst);
}

void GDWeatherGet(char *fingerprint, char *url, bool isFirst)
{
  netStartUI("Start Http Get!", 0, isFirst);
  HTTPClient http;
  http.begin(url);
  netStartUI("开始网络请求", 10, isFirst);
  if (http.GET() == 200)
  {
    Serial.println("********");
    Serial.println("Get succ End");
    netStartUI("网络请求成功", 20, isFirst);
    String j = http.getString();
    http.end();
    jsonParse(j, isFirst);
  }
  else
  {
    netStartUI("网络请求失败，请重启", 20, isFirst);
    Serial.println("Get Fail......    code:");
    Serial.println(http.GET());
    String j = http.getString();
    http.end();
  }
}
WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "203.107.6.88", 3600 * 8, 30);
NTPClient timeClient(ntpUDP,28800);
void NTPRequest(bool isFirst)
{
  timeClient.update();
  const char *j = timeClient.getFormattedTime().c_str();
  Serial.println("NTP******");
  Serial.println(j);
  Serial.println("NTP******");
  char times[6];
  for (int i = 0; i < 5; i++)
  {
    times[i] = j[i];
  }
  strcpy(Time_c.time, times);
  
}

void GDWifiBegin(char *SSID, char *PASSWORD, char *fingerprint, char *url)
{
  netStartUI("WiFi 连接中...", 0, true);
  Serial.println(SSID);
  Serial.println(PASSWORD);
  WiFi.begin(SSID, PASSWORD);
  netStartUI("WiFi 连接中...", 6, true);
  while (WiFi.status() != WL_CONNECTED)
  {
    netStartUI("WiFi 连接中...", 10, true);
    delay(500);
    Serial.print(".");
  }
  netStartUI("WiFi 连接中...", 50, true);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  netStartUI("WiFi 连接成功！", 100, true);
  timeClient.begin();
  NTPRequest(true);
  GDWeatherGet(fingerprint, url, true);
}
