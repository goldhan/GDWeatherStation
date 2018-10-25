import os,json
patch = os.getcwd()
class UserJSON():

    jsonPatch = patch + '/userData.json'
    # pushPatch = patch + '/pushMessage.json'
    city = ''
    heWeatherKey = ''
    yeelinkKey = ''
    heWeatherYeelinkAPI = ''
    qiushiYeelinkAPI = ''
    pushYeelinkAPI = ''
    qiuShiAPI = ''
    bitMapYeelinkAPI1 = ''
    bitMapYeelinkAPI2 = ''
    title = ''
    detail = ''

    def __init__(self):
        pass


    def Load(self):
        with open(self.jsonPatch, 'r') as f:
            self.userJson = json.load(f)
        self.city = self.userJson['city']
        self.heWeatherKey = self.userJson['heWeatherKey']
        self.yeelinkKey = self.userJson['yeelinkKey']
        self.heWeatherYeelinkAPI = self.userJson['heWeatherYeelinkAPI']
        self.qiushiYeelinkAPI = self.userJson['qiushiYeelinkAPI']
        self.pushYeelinkAPI = self.userJson['pushYeelinkAPI']
        self.qiuShiAPI = self.userJson['qiuShiAPI']
        self.bitMapYeelinkAPI1 = self.userJson['bitMapYeelinkAPI1']
        self.bitMapYeelinkAPI2 = self.userJson['bitMapYeelinkAPI2']
        self.title = self.userJson['title']
        self.detail = self.userJson['detail']


    def LoadPush(self):
        with open(self.jsonPatch, 'r') as f:
            self.userJson = json.load(f)
        self.title = self.userJson['title']
        self.detail = self.userJson['detail']
        # with open(self.pushPatch,'r') as f:
        #     return json.load(f)
