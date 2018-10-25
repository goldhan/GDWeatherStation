import json

class GDJson():

    def __init__(self):

        pass

    def jsonParse(self,data):

        return json.loads(data)

    def parseHeWeather(self,data):
        jsonData = self.jsonParse(data)
        base = jsonData['HeWeather5'][0]
        daily_forecast = base['daily_forecast']
        now = base['now']
        suggestion = base['suggestion']


        return {
            "value": {
                'tody':{
                    'status':int(daily_forecast[0]['cond']['code_d']),
                    'date':daily_forecast[0]['date'],
                    'now':now['tmp'] + 'C',
                    'range': self.range(daily_forecast[0]['tmp']['max'],daily_forecast[0]['tmp']['min']),
                    's':daily_forecast[0]['cond']['txt_d']
                },
                'tom': {
                    'status':int(daily_forecast[1]['cond']['code_d']),
                    'date': daily_forecast[1]['date'],
                    'range': self.range(daily_forecast[1]['tmp']['max'],daily_forecast[1]['tmp']['min']),
                    's': daily_forecast[1]['cond']['txt_d']
                },
                'afterTom': {
                    'status': int(daily_forecast[1]['cond']['code_d']),
                    'date': daily_forecast[2]['date'],
                    'range':self.range(daily_forecast[2]['tmp']['max'],daily_forecast[2]['tmp']['min']),
                    's': daily_forecast[2]['cond']['txt_d']
                },
                'pm25':'PM25: ' + base['aqi']['city']['pm25'],
                'qlty': base['aqi']['city']['qlty'], # 污染评价
                'city': base['basic']['city']
                # 'mes': suggestion['comf']['brf'] + '，' + suggestion['comf']['txt']
            }
        }

    def range(self,max,min):
        if int(max) > 0:
            max = max + ' '

        if int(min) > 0:
            min = ' ' + min

        return  max + '|' + min + 'C'


    def parseQiushi(self,data):
        jsonData = self.jsonParse(data)
        items = jsonData['items']
        m = 0
        num = 0
        # print (len(items))
        for index in range(len(items)):
            x = items[index]['votes']['up']
            if x > m:
                if len(items[num]['content']) < 100:
                    print (len(items[num]['content']))
                    m = x
                    num = index



        # print (items[num]['content'])
        return {
            "value": [items[num]['content']]
        }








