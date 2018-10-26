import datetime
import ntplib
import ssl
from urllib import request
# import base64
# import curses
# import urwid

# client = ntplib.NTPClient()
# http://193.204.114.232/
# 	[58.220.207.226](本节点由*方糖科技*赞助),
# [202.112.29.82] [202.108.6.95] [120.25.108.11] [182.92.12.11] [115.28.122.198]
# response = client.request('58.220.207.226')
# print (datetime.datetime.fromtimestamp(response.tx_time))
#
# array = [0,0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0,8, 0, 0, 0, 0, 8, 0, 0, 0, 4, 8, 16, 0, 0, 8, 0, 8, 0, 0, 8, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 127, 0, 0, 0, 192, 128, 1, 0, 16, 48, 0, 6, 4, 96, 24, 0, 12, 3, 0, 12, 0, 0, 0, 0, 4, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 128, 63, 0, 0, 1, 64, 64, 0, 0, 1, 32, 128, 0, 0, 1, 30, 0, 7, 30, 129, 1, 0, 24, 0, 193, 0, 0, 16, 0, 65, 0, 0, 32, 0, 65, 0, 0, 32, 0, 194, 0, 0, 32, 0, 130, 1, 0, 16, 0, 4, 30, 0, 12, 0, 12, 112, 240, 3, 96, 24, 128, 15, 0, 16, 48, 0, 0, 0, 0, 64, 8, 4, 2, 0, 0, 8, 4, 1, 0, 0, 12, 2, 1, 0, 8, 0, 2, 0, 0, 8, 0, 0, 0, 0, 4, 32, 16, 0, 0, 0, 32, 16, 0, 0, 0, 32, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
#
# print(array);


# str = "have a good day! have a good day! have a good day! have a good day! have a good day!"
# i = 0
# str16 = ''

# print (strArr)
# 5f67cea40b16ca231d849068efcf337ab13479c8   GDWeatherStation token
context = ssl._create_unverified_context()
url = 'https://raw.githubusercontent.com/goldhan/GDWeatherStation/master/Service/userData.json'
# self.heWeatherAPI = 'https://free-api.heweather.com/v5/weather?city=' + self.city + '&key=' + self.heWeatherKey + '&lang=EN'
with request.urlopen(url,context=context) as f:
    data = f.read()
    jsonStr = data.decode('utf-8')
    print(jsonStr)
