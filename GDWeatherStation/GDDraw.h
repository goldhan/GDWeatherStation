// GDDraw.h

#include "GDIcon.h"
#include "GDWifi.h"
#define Times 5000 // 页面显示时间 毫秒

void side_dotNOSec(int num)
{
    int y = (64 - num * 4 - (num - 1) * 4);

    for (int i = 0; i < num; i++)
    {
        u8g2.drawCircle(4, y + 8 * i, 2);
    }
}

void side_dot(int sec, int num)
{
    int y = (64 - num * 4 - (num - 1) * 4);
    u8g2.drawDisc(4, y + 8 * sec, 2);
}

void side_status(bool isOK)
{
    if (isOK)
    {
        u8g2.drawXBM(0, 0, 10, 10, netIcon);
    }
}

void str(const char *string, int x, int yy, int y, const uint8_t *font)
{
    u8g2.setFont(font);
    u8g2.setCursor(x, yy - y);
    u8g2.print(string);
    // u8g2.drawStr(x, yy - y, string);
}

void strNoFont(const char *string, int x, int yy, int y)
{
    u8g2.setCursor(x, yy - y);
    u8g2.print(string);
}
void side_temperature(bool isRefresh)
{
    if (isRefresh)
    {
        u8g2.drawXBM(0, 53, 8, 10, refresh);
    }
    else
    {

        // str(weather.now, 1, 63, 0, u8g2_font_trixel_square_tr);
    }
}

void Time(bool isMes, bool isR, int time)
{
    if (isR)
    {
        u8g2.drawRFrame(3, 10, 32, 12, 5);
    }
    if (isMes)
    {
        str("*", 4, 21, 0, u8g2_font_roentgen_nbp_t_all);
    }
    str(Time_c.time, 14, 19, 0, u8g2_font_trixel_square_tn);
}

void rectangle(int y)
{
    u8g2.drawRFrame(10, 0 - y, 118, 64, 5);
}

void icon(int x, int yy, int y, int statu)
{

    switch (statu)
    {
    case 1:
        u8g2.drawXBM(x, yy - y, 24, 24, umbrella);
        break;
    case 2:
        u8g2.drawXBM(x, yy - y, 10, 10, netIcon);
        break;
    case 3:
        u8g2.drawXBM(x, yy - y, 8, 10, refresh);
        break;
    case 100:
        u8g2.drawXBM(x, yy - y, 40, 40, suny);
        break;
    case 101:
    case 103:
        u8g2.drawXBM(x, yy - y, 40, 40, cloudy);
        break;
    case 102:
        u8g2.drawXBM(x, yy - y, 40, 40, partlyCloudy);
        break;
    case 104:
        u8g2.drawXBM(x, yy - y, 40, 40, overcast);
        break;
    case 300:
    case 301:
    case 302:
    case 303:
    case 304:
        u8g2.drawXBM(x, yy - y, 40, 40, thunderShowe);
        break;
    case 305:
    case 309:
        u8g2.drawXBM(x, yy - y, 40, 40, lightRain);
        break;
    case 306:
    case 313:
        u8g2.drawXBM(x, yy - y, 40, 40, moderateRain);
        break;
    case 307:
    case 308:
    case 310:
    case 311:
    case 312:
        u8g2.drawXBM(x, yy - y, 40, 40, heavyRain);
        break;
    case 400:
        u8g2.drawXBM(x, yy - y, 40, 40, lightSnow);
        break;
    case 401:
    case 407:
        u8g2.drawXBM(x, yy - y, 40, 40, moderateSnow);
        break;
    case 402:
    case 403:
        u8g2.drawXBM(x, yy - y, 40, 40, heavySnow);
        break;
    case 404:
    case 405:
    case 406:
        u8g2.drawXBM(x, yy - y, 40, 40, sleet);
        break;
    default:
        u8g2.drawXBM(x, yy - y, 40, 40, unknown);
        break;
    }
}

void TodyTime(int y)
{
    str(weather.tody.date, 15, 60, y, u8g2_font_lucasfont_alternate_tr);
    str(Time_c.time, 15, 50, y, u8g2_font_courB18_tn);
    str(weather.now, 15, 17, y, u8g2_font_helvR10_tr);
    if (weather.tody.cod >= 300)
    {
        icon(67, 6, y, 1); //伞
    }
    icon(88, 4, y, weather.tody.cod);
    str(weather.tody.status, 15, 28, y, u8g2_font_baby_tf);
    rectangle(y);
}
//
void Tody(int y)
{
    rectangle(y);
    icon(36, 9, y, weather.tody.cod);
    if (weather.tody.cod >= 300)
    {
        icon(12, 26, y, 1); //伞
    }
    str(weather.now, 78, 25, y, u8g2_font_profont22_tr);                  // 12*22  现在温度
    str(weather.tody.range, 78, 40, y, u8g2_font_lucasfont_alternate_tr); // 最高与最低温度
    str(weather.pm25, 78, 52, y, u8g2_font_trixel_square_tr);             // pm2.5
    str(weather.qlty, 78, 60, y, u8g2_font_trixel_square_tr);
    str(weather.city, 14, 60, y, u8g2_font_lucasfont_alternate_tr); // 城市名字
}
//
void Two(int y)
{
    rectangle(y);
    icon(38, 6, y, weather.tom.cod);
    icon(82, 6, y, weather.afterTom.cod);
    str(weather.tom.range, 26, 56, y, u8g2_font_lucasfont_alternate_tr);      // 最高与最低温度
    str(weather.afterTom.range, 75, 56, y, u8g2_font_lucasfont_alternate_tr); // 最高与最低温度
}

void Message(int y)
{
    //  u8g2_font_wqy12_t_gb2312
    //  u8g2_font_lucasfont_alternate_tr
    if (y == 0 )
    {
        u8g2.setFont(u8g2_font_wqy12_t_gb2312);
    }
    rectangle(y);
    strNoFont(weather.title, 41, 20, y);
    strNoFont(weather.detail1, 15, 32, y);
    strNoFont(weather.detail2, 15, 44, y);
    strNoFont(weather.detail3, 15, 56, y);
    strNoFont(weather.detail4, 15, 68, y);
    // str(weather.detail5, 15, 37, y, u8g2_font_lucasfont_alternate_tr);
}

void theFirst()
{
    //	u8g2.firstPage();
    //	do {

    //	} while (u8g2.nextPage());
}
void baseUI(int dotNum, int dotSec, bool isMes, bool isShow, bool isRefresh)
{
    side_dotNOSec(dotNum);
    side_dot(dotSec, dotNum);
    if (isShow)
    {
        Time(isMes, true, 0);
    }

    icon(0, 0, 0, 2);
    side_temperature(isRefresh);
}
void u8g2Begin()
{
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFlipMode(1);
    u8g2.setColorIndex(1);
}

int sec = 0;
int num = 0;
void GDStart(char *fingerprint, char *url)
{
    int y = 2;
    if (sec == 5)
    {
        sec = 0;
    }
    do
    {
        u8g2.firstPage();
        do
        {
            if (sec == 0)
            {

                baseUI(4, sec, true, false, false);
            }
            else
            {
                if (sec == 4)
                {
                    baseUI(4, 0, true, false, false);
                }
                else
                {
                    baseUI(4, sec, true, true, false);
                }
            }
            switch (sec)
            {
            case 0:
                TodyTime(0);
                break;
            case 1:
                TodyTime(y);
                Tody(-64 + y);
                break;
            case 2:
                Tody(y);
                Two(-64 + y);
                break;
            case 3:
                Two(y);
                Message(-64 + y);
                break;
            case 4:
                Message(y);
                TodyTime(-64 + y);
                break;
            default:
                break;
            }

        } while (u8g2.nextPage());
        if (sec == 0)
        {
            break;
        }
        y += 2;
    } while (y <= 64);

    if (sec != 4)
    {
        delay(Times);
    }
    else
    {
        if (num == 10)
        {   
            GDWeatherGet(fingerprint, url, true);

            num = 0;
        }
        else if (num % 2 == 0)
        {
            NTPRequest(false);

        }
        num++;
    }
    sec++;
}
