#include "GDDraw.h"

void setup()
{
    char ssid[] = "Xiaomi_984B"; // wifi ssid
    char password[] = "hanxixi6004"; // wifi password
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
