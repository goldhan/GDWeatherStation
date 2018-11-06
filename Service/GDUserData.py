import os,json,sys

filePath = os.path.abspath(sys.argv[0])
filePathArr = filePath.split('/')
del filePathArr[len(filePathArr)-1]
filePath = '/'.join(filePathArr)

Path = filePath

class UserJSON(object):

    def __init__(self):
        self.Load()

    def Load(self):
        self.jsonPath = Path + '/userData.json'
        with open(self.jsonPath, 'r') as f:
            self.userJson = json.load(f)
        self.city = self.userJson['city']
        self.gitUrl = self.userJson['gitUrl']
        self.heWeatherKey = self.userJson['heWeatherKey']
        self.qiuShiAPI = self.userJson['qiuShiAPI']
        self.title = self.userJson['title']
        self.detail = self.userJson['detail']
