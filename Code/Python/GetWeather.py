import requests, json

print 'Getting Weather'

#Chicago,Il = 2379574

shortweather_url = "https://query.yahooapis.com/v1/public/yql?q=select%20item.condition.text%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22Chicago%20IL%22)&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys"
weather_url = "https://query.yahooapis.com/v1/public/yql?q=select%20item.condition%20from%20weather.forecast%20where%20woeid%3D2379574%20and%20u%3D'c'%3B&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys&callback="
r = requests.get(weather_url)

print r.status_code
j = json.loads(r.content)
print j['query']['results']['channel']['item']['condition']['text']
print j['query']['results']['channel']['item']['condition']['code']
print j['query']['results']['channel']['item']['condition']['temp']

#Todo: Sort out the InsecurePlatformWarning
#      Map codes to precipitation
#      return formatted string
#      timeouts and errors etc
print j




