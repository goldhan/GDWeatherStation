#include "GDDraw.h"

void setup()
{
    char ssid[] = "ChinaNet-toto"; // wifi ssid
    char password[] = "hanjin117"; // wifi password
    char apiKey[] = "c85bd9d844646649b69a6476d53cae6f"; // yeelink apiKey
    char url[] = "http://api.yeelink.net/v1.0/device/355774/sensor/402747/datapoints"; // yeelink url
    Serial.begin(115200);
    u8g2Begin();
    GDWifiBegin(ssid, password, apiKey, url);

    // theFirst();
}
void loop()
{
    char apiKey[] = "c85bd9d844646649b69a6476d53cae6f"; // yeelink apiKey
    char url[] = "http://api.yeelink.net/v1.0/device/355774/sensor/402747/datapoints"; // yeelink url
    GDStart(apiKey, url);
}
