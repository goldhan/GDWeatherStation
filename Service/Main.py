# coding=utf-8
import time,sys,GDWeatherJson
weather = GDWeatherJson.GDWeatherJson()
def getAndUpload():
    weather.getWeather()
    weather.uploadWeather()

def waitTime(sec):
    for i in range(sec):
        sys.stdout.write(str(sec - i))
        sys.stdout.flush()
        time.sleep(1)
        sys.stdout.write('\r')
        sys.stdout.flush()

def start():
        while True:
                getAndUpload()
                waitTime(10)
                sys.stdout.write('\r')
                sys.stdout.flush()

start()

