---
title: 教你用 ESP8266 / ESP32 做一个天气预报 GDWeatherStation
date: 2018-12-17 10:00:00
tags: 
    - ESP32
    - ESP8266 
    - 12864
    - Arduino
    - Weather
cover: /img/GDWeatherStation/UI_0.png
---

# 教你用 ESP8266 / ESP32 做一个天气预报 GDWeatherStation

[点我ESP8266分支](https://github.com/goldhan/GDWeatherStation/tree/ESP8266)

## 大纲

- 说明
    > 简介以及说明

- 前期准备
    > 你需要准备什么？

- 接口说明
    > 你需要准备的接口说明，以及申请工作

- Python端
    > Python端服务脚本说明

- Arduino端
    > Arduino端说明

- UI说明
    > 关于UI设计

- 后续
    > 进一步改进

## 说明

### 最终效果说明

> 通过ESP8266 / ESP32 连接WIFI访问网络获取天气，网络时间，自定义的信息，然后进行显示

### 需要了解的技术栈

- Arduino
- C
- Python

### 流程说明

利用Python获取申请的api返回信息，进行整理，上传到中转的稳定的api接口，Arduino端再访问此中转的api接口，进行数据展示

## 前期准备

### 硬件准备

- ESP8266 OR ESP32 模块
    > 注意 ESP8266 模块有差别，但是基本都是一样的，需要注意引脚定义
- 12864 OLED 模块 i2c接口 OR SPI
    > 当然也可以使用SPI接口，只是需要更改 Arduino程序代码即可
- 连接线若干
- __可选__ usb 下载器
    > 有些 ESP8266 没有自带 usb下载功能，需要自己买个usb下载器，进行程序烧录

> 本人ESP32开发板，使用的是 M5Stick core，自带电池，12864，很方便，如果使用其他的开发版，可能需要修改GDWifi里 `U8G2_SH1107_64X128_1_4W_HW_SPI u8g2(U8G2_R1, 14,27,33);`,不同的屏幕，驱动芯片不一样。

### 环境准备

- Arduino IDE
    > 百度下，有下载
- usb下载器驱动
    > 根据自己型号去驱动，多数店家会有提供，百度也能找到
- Python3 环境

### 所需要的第三发库

#### Arduino IDE 需要的库

> 具体怎么去安装库，请自行百度，关键字：Arduino 添加库，__Arduino 添加ESP8266支持__、__Arduino 添加ESP32支持__

``` C
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <U8g2lib.h>
#include <WiFiUdp.h>
```

#### Python

无

## 接口说明

### 你需要申请

#### 一个空的Git仓库

需要申请一个空Git仓库，随便那一家都可以，申请很简单，这里不做详细描述

#### 和风天气API Key

> [和风天气API申请地址](http://www.heweather.com/)

申请很简单，这里不做详细描述，只需要申请免费的即可，一天有限制请求次数，不过已经足够，注意记住申请后的Key

## Python端

### 服务器端——Python实现

#### 为啥要写个这样的程序

- 首先单片机性能有限，并且来来回回烧录程序比较麻烦，目前网上的接口对于单片机来讲数据量还是比较大的，解析会耗费很大的硬件资源，且接口不稳定。所以想自己组装一个自己能够把控的接口。
- 自己组装接口可以只要自己想要的信息，使数据量变的小巧，适合单片机的解析，并且可以保证接口的稳定

#### 目前已经实现的功能

- 定时从网上的接口获取数据，解析成自己组装的接口并且上传到指定的git仓库上
- 定时上传和天气数据
- ~~定时上传糗事百科段子~~ （已删除此功能）
- 定时push自己的自定义信息

#### 使用

- 程序有一个json文件，当第一次使用时需要配置自己的申请的一些接口，和key
- userData.json 文件存放着所用的接口及key

``` json
{
  "city": "shenzhen",  // 城市拼音
  "heWeatherKey": "xxxxxx", // 和风天气Key
  "qiuShiAPI": "http://m2.qiushibaike.com/article/list/text?count=5&page=1",
  "gitUrl": "https://xxxxxxx.git", // 所申请的 Git 仓库地址
  "title": "about me", // 推送标题
  "detail": "qq:xxxxxx    have a good Day! This is my first push!" // 推送内容
}
```

1. `git clone https://github.com/goldhan/GDWeatherStation.git`
2. 修改 service 目录下的 userData.json 文件
3. 终端 cd 到 Service 目录下
4. `python3 Main.py` 即可

#### 问题

> 已经删除关于糗事百科的功能，所以没有了中文的烦恼，不过自定义的推送内容依然不支持中文

- ~~目前糗事百科接口都是中文，但是ESP8266 上的程序不支持中文（不知道有没有英语版的类似糗事百科的接口~~
- ~~还是中文中文中文！~~
- ESP32支持中文

#### 注意

- 当请求有问题时程序会停止，请注意。
- 请严格的按照json文件里的格式进行填写，不要乱加多余的空格或者其他不必要的字符。
- 注意定义推送消息不要多，因为屏幕显示区域有限
- 因为对应的ESP8266 端的程序不支持中文，所以请用英语写推送消息。
- ESP32支持中文显示，可以用中文写自定义的推送消息

## Arduino端

> __ESP8266__ 源码，使用 Arduino 烧录到 ESP8266

### Arduino 使用说明

> __注意所需要的库，上边有说明__

#### GDWeatherStation.ino

``` c
#include "GDDraw.h"

void setup()
{
    char ssid[] = "xxx"; // wifi ssid
    char password[] = "xxx"; // wifi password
    char url[] = "https://raw.githubusercontent.com/goldhan/MockJSON/master/GDWeather.json"; // git url
    // SHA1 fingerprint of the certificate  
    //把你需要调用的请求地址用浏览器访问，然后打开调试工具选择“安全”即可看到对应请求的fingerprint，复制到这个地方即可
    char fingerprint[] = "CC AA 48 48 66 46 0E 91 53 2C 9C 7C 23 2A B1 74 4D 29 9D 33"; 
    Serial.begin(115200);
    u8g2Begin();
    GDWifiBegin(ssid, password, fingerprint, url);

    // theFirst();
}
void loop()
{
    // SHA1 fingerprint of the certificate  
    //把你需要调用的请求地址用浏览器访问，然后打开调试工具选择“安全”即可看到对应请求的fingerprint，复制到这个地方即可
    char fingerprint[] = "CC AA 48 48 66 46 0E 91 53 2C 9C 7C 23 2A B1 74 4D 29 9D 33";
    char url[] = "https://raw.githubusercontent.com/goldhan/MockJSON/master/GDWeather.json"; // git url
    GDStart(fingerprint, url);
}

```

> __请按照注释去填写对应的值__

#### 注意

- 接线

`U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/D6, /* data=*/D5, /* reset=*/U8X8_PIN_NONE);`
代码已经很明确了，请对应接线即可，也可以按照自己的喜好去换引脚端口，OLED屏幕支持 i2c, SPI,本代码用的是 i2c协议，可以按照自己的需求去更改下代码即可，具体不懂可以百度，关键字：U8G2 spi，
类似：`U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0,/* clock=*/4, /* data=*/ 5, /* cs=*/ 3, /* dc=*/ 6, /* reset=*/ 7); `

- url 地址

url 地址是git里面可以直接访问json的地址，一般都是以 `https://raw` 为开头的地址

- fingerprint

由于是https请求，所以请用浏览器访问上边的地址，打开调试工具选择“安全”即可看到对应请求的fingerprint，__SHA1__

## UI说明

 >关于设计方面的说明

### UI 展示

![01](/UI_Design/weather1.png)
![02](/UI_Design/weather2.png)
![03](/UI_Design/weather3.png)

具体源文件 [Sketch](https://github.com/goldhan/GDWeatherStation/tree/master/UI_Design)

### 12864 OLED

由于此模块网上有很多成熟的代码，所有选择12864显示模块，只需要显示简单的信息，已经足够。OLED的特性，所以显示效果还不错。

### 设计思路

#### 简单，美观

显示模块所提供的可显示的区域其实不多，再加上单片机性能有限，所以尽量简单明了，只需要显示所需要的信息即可，但是本人大学艺术专业，所以还是要求自己在足够简单的同时，尽量美观！所以只运行了简单的圆角框即可，外加一点元素点缀即可。

#### 卡片

由于显示的信息一个屏幕肯定不足够，所有设计成上下轮播的卡片展示。已足够显示，网络时间、今日天气、以及明日天气和少许的自定义信息。

## 后续

> 关于后续计划

### 不足

由于本人不会 C++ 所以一些 C++代码写的比较乱，甚至只能说是 C代码，Python 也是只会一点皮毛，所以写的也不好，不过还是可以用

### 计划

1. 自己设计3D外壳（哈哈，还好我之前就是做三维的，3ds Max,VRay,对于我来讲都很熟练），然后利用3D打印出来
2. 优化Wifi接入，利用 Airkiss

### 其他

反正都是瞎折腾
