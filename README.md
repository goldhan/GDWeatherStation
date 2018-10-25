# ESP8266 OLED WeatherStationServer

## 文件结构

``` shell
├── GDWeatherStation
│   ├── GDDraw.h
│   ├── GDIcon.h
│   ├── GDWeatherStation.ino
│   └── GDWifi.h
├── README.md
├── Service
│   ├── GDParseJson.py
│   ├── GDUserData.py
│   ├── GDWeatherJson.py
│   ├── Main.py
│   ├── pushMessage.json
│   ├── test.py
│   ├── urwidTest.py
│   ├── userData.json
│   └── userIcon.txt
└── UI_Design
    ├── 65\ Weather\ Icons.sketch
    ├── UI.sketch
    ├── icon
    │   ├── 1136818.bmp
    ...... \\ pictures

    │   ├── 1137201.png
    │   ├── Globe_10px_1070150_easyicon.net.bmp
    │   ├── Globe_10px_1070150_easyicon.net.png
    │   ├── Propeller_10px_1070201_easyicon.net.png
    │   ├── Refresh_8px_1070204_easyicon.net.bmp
    │   ├── Refresh_8px_1070204_easyicon.net.png
    │   ├── symbols-icons_40px_1137068_easyicon.net.bmp
    │   ├── symbols-icons_40px_1137068_easyicon.net.png
    │   ├── weather_40px_1137171_easyicon.net.bmp
    │   └── weather_40px_1137174_easyicon.net.bmp
    ├── weather1.png
    ├── weather2.png
    └── weather3.png
```

## GDWeatherStation

> __ESP8266__ 源码，使用 Arduino 烧录到 ESP8266

### Arduino IDE 需要的库

> 具体怎么去安装库，请自行百度，关键字：Arduino 添加库，Arduino 添加ESP8266支持

``` C
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <U8g2lib.h>
#include <WiFiUdp.h>
```

### Arduino 使用说明

#### GDWeatherStation.ino

``` c
#include "GDDraw.h"

void setup()
{
    char ssid[] = "xxxxxx"; // wifi ssid
    char password[] = "xxxxxxxx"; // wifi password
    char apiKey[] = "c85bd9d844646649b69a6476d53cae6f"; // yeelink apiKey
    char url[] = "http://api.yeelink.net/v1.0/device/355774/sensor/402747/datapoints"; // yeelink url
    Serial.begin(115200);
    u8g2Begin();
    GDWifiBegin(ssid, password, apiKey, url);

    // theFirst();
}
void loop()
{
    char apiKey[] = "c85bd9d844646649b69a6476d53cae6f"; // yeelink apiKey 和上边值相同
    char url[] = "http://api.yeelink.net/v1.0/device/355774/sensor/402747/datapoints"; // yeelink url 和上边值相同
    GDStart(apiKey, url);
}
```

> __请按照注释去填写对应的值__

## 服务器端——Python实现

### 为啥要写个这样的程序

- 首先单片机性能有限，并且来来回回烧录程序比较麻烦，目前网上的接口对于单片机来讲数据量还是比较大的，解析会耗费很大的硬件资源，且接口不稳定。所以想自己组装一个自己能够把控的接口。
- 自己组装接口可以只要自己想要的信息，使数据量变的小巧，适合单片机的解析，并且可以保证接口的稳定

### 目前已经实现的功能

- 定时从网上的接口获取数据，解析成自己组装的接口并且上传到yeelink上
- 定时上传和天气数据
- 定时上传糗事百科段子
- 定时push自己的自定义信息

### 使用

- 程序有两个json文件，当第一次使用时需要配置自己的申请的一些接口，和key
- userData.json 文件存放着所用的接口及key
- pushMessage.json 如果不需要推送你的自定义消息，可以不用去修改
- 当需要推送消息时，要去修改pushMessage.json文件

### 问题

- 目前糗事百科接口都是中文，但是ESP8266 上的程序不支持中文（不知道有没有英语版的类似糗事百科的接口）
- 还是中文中文中文！

### 注意

- 当请求有问题时程序会停止，请注意。
- 请严格的按照json文件里的格式进行填写，不要乱加多余的空格或者其他不必要的字符。
- 因为yeelink的泛值接口最多只能支持1024个字符串，所以填写推送消息时请注意不要超出。
- 因为对应的ESP8266 端的程序不支持中文，所以请用英语写推送消息。
