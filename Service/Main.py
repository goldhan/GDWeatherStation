# coding=utf-8

from GDWeatherJson import GDWeatherJson
import time,sys
from GDUserData import UserJSON

userJson = UserJSON()
userJson.Load()


weather = GDWeatherJson()
weather.city = userJson.city
weather.heWeatherKey = userJson.heWeatherKey
weather.qiuShiAPI = userJson.qiuShiAPI
weather.heWeatherYeelinkAPI = userJson.heWeatherYeelinkAPI
weather.yeelinkKey = userJson.yeelinkKey
weather.qiushiYeelinkAPI = userJson.qiushiYeelinkAPI
weather.pushYeelinkAPI = userJson.pushYeelinkAPI
weather.bitMapYeelinkAPI1 = userJson.bitMapYeelinkAPI1
weather.title = userJson.title
weather.detail = userJson.detail


def start():

    # weather.uploadPush()

    weather.getWeather()
    weather.uploadWeather()

    weather.getQiuShi()
    weather.uploadQiuShi()



def waitTime(sec):
    for i in range(sec):
        sys.stdout.write(str(sec - i))
        sys.stdout.flush()
        time.sleep(1)
        sys.stdout.write('\r')
        sys.stdout.flush()

while True:
    start()
    waitTime(30)
    sys.stdout.write('\r')
    sys.stdout.flush()




