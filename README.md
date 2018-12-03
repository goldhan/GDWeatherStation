---
title: GDWeatherStation_1 说明
date: 2018-10-24 13:15:14
tags: 
    - ESP8266 
    - 12864
    - Arduino
    - Weather
cover: /img/GDWeatherStation/UI_0.png
---

# GDWeatherStation_1 说明

## 目录

- [GDWeatherStation_1 说明](https://goldhan.github.io/2018/10/24/GDWeatherStation_1%E8%AF%B4%E6%98%8E/)
    > 简介以及说明

- [GDWeatherStation_2 前期准备](https://goldhan.github.io/2018/10/25/GDWeatherStation_2%E5%89%8D%E6%9C%9F%E5%87%86%E5%A4%87/)
    > 你需要准备什么？

- [GDWeatherStation_3 接口说明](https://goldhan.github.io/2018/11/05/GDWeatherStation_3%E6%8E%A5%E5%8F%A3%E8%AF%B4%E6%98%8E/)
    > 你需要准备的接口说明，以及申请工作

- [GDWeatherStation_4 Python端](https://goldhan.github.io/2018/11/05/GDWeatherStation_4Python%E7%AB%AF/)
    > Python端服务脚本说明

- [GDWeatherStation_5 Arduino端](https://goldhan.github.io/2018/11/06/GDWeatherStation_5Arduino%E7%AB%AF/)
    > Arduino端说明

- [GDWeatherStation_6 UI说明](https://goldhan.github.io/2018/11/06/GDWeatherStation_6UI%E8%AF%B4%E6%98%8E/)
    > 关于UI设计

- [GDWeatherStation_7 后续](https://goldhan.github.io/2018/12/03/GDWeatherStation_7后续/)
    > 进一步改进

## 最终效果说明

> 通过ESP8266连接WIFI访问网络获取天气，网络时间，自定义的信息，然后进行显示

## 需要了解的技术栈

- Arduino
- C
- Python

## 流程说明

利用Python获取申请的api返回信息，进行整理，上传到中转的稳定的api接口，Arduino端再访问此中转的api接口，进行数据展示
