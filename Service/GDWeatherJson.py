# coding=utf-8
import GDParseJson,ssl,json,datetime,sys
from GDUserData import UserJSON
from urllib import request


class GDWeatherJson():

    heWeatherKey = ''
    city = ''
    yeelinkKey = ''
    heWeatherData = ''
    qiuShiData = ''
    heWeatherYeelinkAPI = ''
    qiuShiAPI = ''

    qiushiYeelinkAPI = ''
    pushYeelinkAPI = ''
    bitMapYeelinkAPI1 = ''

    title = ''
    detail = ''

    context = ssl._create_unverified_context()

    def __init__(self):
        self.jsonParse = GDParseJson.GDJson()
        self.time = datetime.datetime
        self.userJson = UserJSON()

    def getWeather(self):
        self.heWeatherAPI = 'https://free-api.heweather.com/v5/weather?city=' + self.city + '&key=' + self.heWeatherKey + '&lang=EN'
        with request.urlopen(self.heWeatherAPI,context=self.context) as f:
            data = f.read()
            self.heWeatherData = data.decode('utf-8')
            self.data2yeelikJson()

    def uploadWeather(self):
        yeelinkReq = request.Request(self.heWeatherYeelinkAPI)
        yeelinkReq.add_header('U-ApiKey', self.yeelinkKey)
        yeelinkReq.add_header('content-type', 'application/json')
        with request.urlopen(yeelinkReq,data= bytes(self.heWeatherDic,'utf8')) as f:
            self.uploadSuccess(f, ' HeWeather')

    def getQiuShi(self):
        qiuShiReq = request.Request(self.qiuShiAPI)
        qiuShiReq.add_header('Content-Type','application/x-www-form-urlencoded')
        qiuShiReq.add_header('User-Agent','Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11')
        with request.urlopen(qiuShiReq) as f:
            data = f.read()
            self.qiuShiData = data.decode('utf-8')
            self.data2QiuShiJson()

    def uploadQiuShi(self):
        yeelinkReq = request.Request(self.qiushiYeelinkAPI)
        yeelinkReq.add_header('U-ApiKey', self.yeelinkKey)
        yeelinkReq.add_header('content-type', 'application/json')
        with request.urlopen(yeelinkReq, data=bytes(self.qiuShiDic, 'utf8')) as f:
            self.uploadSuccess(f,' Qiushi')


    # def uploadPush(self):
    #     yeelinkReq = request.Request(self.pushYeelinkAPI)
    #     yeelinkReq.add_header('U-ApiKey', self.yeelinkKey)
    #     yeelinkReq.add_header('content-type', 'application/json')
    #     self.pushJson = UserJSON().LoadPush()
    #     self.pushJson['key'] = self.yeelinkKey
    #     self.pushJson = json.dumps(self.pushJson)
    #     with request.urlopen(yeelinkReq, data=bytes(self.pushJson, 'utf8')) as f:
    #         self.uploadSuccess(f, ' Push')

    def data2yeelikJson(self):
        self.heWeatherDic = self.jsonParse.parseHeWeather(self.heWeatherData)
        self.heWeatherDic['key'] = self.yeelinkKey

        self.userJson.LoadPush()

        self.heWeatherDic['value']['title'] = self.userJson.title
        str16 = ''
        for i, s in enumerate(self.userJson.detail):
            str16 += s
            if (i + 1) % 16 == 0:
                str16 += '*+'

        strArr = str16.split('*+')
        if len(strArr) < 5:
            for i in range(0,5-len(strArr)):
                strArr.append('')

        self.heWeatherDic['value']['detail'] = strArr
        self.heWeatherDic = json.dumps(self.heWeatherDic)

    def data2QiuShiJson(self):
        self.qiuShiDic = self.jsonParse.parseQiushi(self.qiuShiData)
        self.qiuShiDic['key'] = self.yeelinkKey
        self.qiuShiDic = json.dumps(self.qiuShiDic)
        # print(self.qiuShiDic)

    def uploadSuccess(self,data,message):
        if data.status == 200:
            nowTime = self.time.now().strftime('%Y-%m-%d %H:%M:%S')
            sys.stdout.write('******'+ data.reason + message + ' upload Successful! ' + nowTime)
            sys.stdout.flush()
            # print(data.reason + message + ' upload Successful!',nowTime)
        else:
            print('Fail! Status:',data.status)
