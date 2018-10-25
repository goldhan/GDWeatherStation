//GDWifi.h
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <U8g2lib.h>
#include <WiFiUdp.h>
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/D6, /* data=*/D5, /* reset=*/U8X8_PIN_NONE);

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
  char title[12];
  char detail1[16];
  char detail2[16];
  char detail3[16];
  char detail4[16];
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
    "message",
    "          ",
    "**no message**",
    "          ",
    "          "};
//     // ""};

void startProcess(char *title, int num)
{
  u8g2.setFont(u8g2_font_baby_tf);
  u8g2.drawStr(14, 30, title);
  u8g2.drawRFrame(9, 20, 110, 25, 5);
  u8g2.drawFrame(14, 34, 100, 6);
  u8g2.drawBox(14, 34, num, 6);
}

void netStartUI(char *title, int num, bool isFirst)
{

  u8g2.firstPage();
  do
  {
    startProcess(title, num);
  } while (u8g2.nextPage());
}

void jsonParse(String j, bool isFirst)
{
  netStartUI("JsonParse......", 20, isFirst);
  StaticJsonDocument<800> jsonBuffer;
  Serial.println("print json below");
  Serial.println(j);
  Serial.println("json parse start");
  netStartUI("JsonParse......", 25, isFirst);
  char json[j.length() + 1];
  for (int i = 0; i < j.length(); i++)
  {
    json[i] = j[i];
  }
  netStartUI("JsonParse......", 30, isFirst);
  DeserializationError error = deserializeJson(jsonBuffer, json);
  if (error) Serial.println("json parse Error!");
  JsonObject root = jsonBuffer.as<JsonObject>();
  weather.tody.cod = root["value"]["tody"]["status"];
  strcpy(weather.tody.date, root["value"]["tody"]["date"]);
  strcpy(weather.tody.range, root["value"]["tody"]["range"]);
  strcpy(weather.tody.status, root["value"]["tody"]["s"]);
  netStartUI("JsonParse......", 40, isFirst);
  weather.tom.cod = root["value"]["tom"]["status"];
  strcpy(weather.tom.date, root["value"]["tom"]["date"]);
  strcpy(weather.tom.range, root["value"]["tom"]["range"]);
  strcpy(weather.tom.status, root["value"]["tom"]["s"]);
  netStartUI("JsonParse......", 50, isFirst);
  weather.afterTom.cod = root["value"]["afterTom"]["status"];
  strcpy(weather.afterTom.date, root["value"]["afterTom"]["date"]);
  strcpy(weather.afterTom.range, root["value"]["afterTom"]["range"]);
  strcpy(weather.afterTom.status, root["value"]["afterTom"]["s"]);
  netStartUI("JsonParse......", 60, isFirst);
  strcpy(weather.now, root["value"]["tody"]["now"]);
  strcpy(weather.pm25, root["value"]["pm25"]);
  strcpy(weather.city, root["value"]["city"]);
  strcpy(weather.qlty, root["value"]["qlty"]);
  netStartUI("JsonParse......", 70, isFirst);
  strcpy(weather.title, root["value"]["title"]);
  strcpy(weather.detail1, root["value"]["detail"][0]);
  strcpy(weather.detail2, root["value"]["detail"][1]);
  strcpy(weather.detail3, root["value"]["detail"][2]);
  strcpy(weather.detail4, root["value"]["detail"][3]);
  // strcpy(weather.detail4, root["value"]["detail"][4]);
  netStartUI("JsonParse......", 80, isFirst);
  Serial.println("json parse end");
  netStartUI("JsonParse Successful!", 100, isFirst);
}

void GDWeatherGet(char *yeelinkKey, char *url, bool isFirst)
{
  netStartUI("Start Http Get!", 0, isFirst);
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "text/html; charset=UTF-8");
  http.addHeader("U-ApiKey", yeelinkKey);
  netStartUI("Start Http Get!", 10, isFirst);
  if (http.GET() == 200)
  {
    Serial.println("********");
    Serial.println("Get succ End");
    netStartUI("Http Get Successful!", 20, isFirst);
    String j = http.getString();
    http.end();
    jsonParse(j, isFirst);
  }
  else
  {
    netStartUI("Start Http Get FAIL!!", 20, isFirst);
    Serial.println("Get Fail......    code:");
    Serial.println(http.GET());
    http.end();
  }
}
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "58.220.207.226", 3600 * 8, 30);
void NTPRequest(bool isFirst)
{
  timeClient.update();
  String j = timeClient.getFormattedTime();
  Serial.println("NTP******");
  Serial.println(j);
  Serial.println("NTP******");
  char times[j.length() + 1];
  for (int i = 0; i < j.length(); i++)
  {
    times[i] = j[i];
    if (i >= 4)
    {
      break;
    }
  }
  strcpy(weather.time, times);
}

void GDWifiBegin(char *SSID, char *PASSWORD, char *yeelinkKey, char *url)
{
  netStartUI("WiFi Connection......", 0, true);
  Serial.println(SSID);
  Serial.println(PASSWORD);
  WiFi.begin(SSID, PASSWORD);
  netStartUI("WiFi Connection......", 6, true);
  while (WiFi.status() != WL_CONNECTED)
  {
    netStartUI("WiFi Connection......", 10, true);
    delay(500);
    Serial.print(".");
  }
  netStartUI("WiFi Connection......", 50, true);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  netStartUI("WiFi Connected!", 100, true);
  timeClient.begin();
  NTPRequest(true);
  GDWeatherGet(yeelinkKey, url, true);
}
