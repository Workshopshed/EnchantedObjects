# For Curl version
from StringIO import StringIO
import pycurl
import json, sys, urllib, urlparse
import subprocess
from parse import *

def get_location():
    with open('/etc/WeatherAPI.conf', 'r') as f:
    #with open('WeatherAPI.conf', 'r') as f:
        location_name = f.readline()
    f.close()
    return location_name


def build_url(location):
    url = "https://query.yahooapis.com/v1/public/yql"
    q = "select item.condition from weather.forecast where woeid in (select woeid from geo.places(1) where text = '" + urllib.quote(
        location) + "') and u='c'"
    params = {'q': q, 'format': 'json', 'env': 'store://datatables.org/alltableswithkeys'}

    url_parts = list(urlparse.urlparse(url))
    query = dict(urlparse.parse_qsl(url_parts[4]))
    query.update(params)

    url_parts[4] = urllib.urlencode(query)

    return urlparse.urlunparse(url_parts)

def call_api(url):
    r = StringIO()
    c = pycurl.Curl()
    c.setopt(c.URL, url)
    c.setopt(c.CONNECTTIMEOUT, 10)
    c.setopt(c.TIMEOUT, 60)
    c.setopt(c.WRITEFUNCTION, r.write)
    c.perform()
    c.close()
    return r.getvalue()

def map_code(code):
    # Map condition codes to expected precipitation
    # https://developer.yahoo.com/weather/documentation.html
    # 1 = very sunny, 3 = changeable, 5 = very rainy
    codes = {'0': {'n': 'tornado', 'p': 3},
             '1': {'n': 'tropical storm', 'p': 5},
             '2': {'n': 'hurricane', 'p': 5},
             '3': {'n': 'severe thunderstorms', 'p': 5},
             '4': {'n': 'thunderstorms', 'p': 5},
             '5': {'n': 'mixed rain and snow', 'p': 5},
             '6': {'n': 'mixed rain and sleet', 'p': 5},
             '7': {'n': 'mixed snow and sleet', 'p': 5},
             '8': {'n': 'freezing drizzle', 'p': 5},
             '9': {'n': 'drizzle', 'p': 4},
             '10': {'n': 'freezing rain', 'p': 5},
             '11': {'n': 'showers', 'p': 4},
             '12': {'n': 'showers', 'p': 4},
             '13': {'n': 'snow flurries', 'p': 4},
             '14': {'n': 'light snow showers', 'p': 4},
             '15': {'n': 'blowing snow', 'p': 3},
             '16': {'n': 'snow', 'p': 4},
             '17': {'n': 'hail', 'p': 4},
             '18': {'n': 'sleet', 'p': 4},
             '19': {'n': 'dust', 'p': 3},
             '20': {'n': 'foggy', 'p': 4},
             '21': {'n': 'haze', 'p': 3},
             '22': {'n': 'smoky', 'p': 3},
             '23': {'n': 'blustery', 'p': 3},
             '24': {'n': 'windy', 'p': 3},
             '25': {'n': 'cold', 'p': 3},
             '26': {'n': 'cloudy', 'p': 3},
             '27': {'n': 'mostly cloudy (night)', 'p': 3},
             '28': {'n': 'mostly cloudy (day)', 'p': 3},
             '29': {'n': 'partly cloudy (night)', 'p': 3},
             '30': {'n': 'partly cloudy (day)', 'p': 3},
             '31': {'n': 'clear (night)', 'p': 1},
             '32': {'n': 'sunny', 'p': 1},
             '33': {'n': 'fair (night)', 'p': 2},
             '34': {'n': 'fair (day)', 'p': 2},
             '35': {'n': 'mixed rain and hail', 'p': 4},
             '36': {'n': 'hot', 'p': 1},
             '37': {'n': 'isolated thunderstorms', 'p': 4},
             '38': {'n': 'scattered thunderstorms', 'p': 4},
             '39': {'n': 'scattered thunderstorms', 'p': 4},
             '40': {'n': 'scattered showers', 'p': 4},
             '41': {'n': 'heavy snow', 'p': 5},
             '42': {'n': 'scattered snow showers', 'p': 4},
             '43': {'n': 'heavy snow', 'p': 5},
             '44': {'n': 'partly cloudy', 'p': 2},
             '45': {'n': 'thundershowers', 'p': 5},
             '46': {'n': 'snow showers', 'p': 5},
             '47': {'n': 'isolated thundershowers', 'p': 4}}
    state = codes.get(code)
    if not state:
        raise RuntimeError('Unknown weather code returned')
    return state['p']


def parse_weather(json):
    text = json['query']['results']['channel']['item']['condition']['text'].replace(",", " ")
    code = map_code(json['query']['results']['channel']['item']['condition']['code'])
    temp = json['query']['results']['channel']['item']['condition']['temp']
    return {'text': text, 'code': code, 'temp': float(temp)}

def guess_weather(rel_humidity, temp):
    # Temperature in Degrees C and Relative Humidity as a percentage
    # Based on an approximation of these graphs
    # ftp://www.star.nesdis.noaa.gov/pub/smcd/spb/lzhou/AMS86/PREPRINTS/PDFS/97921.pdf
    if rel_humidity < 0.66 * temp + 53:
        weather = 1  # Very likely dry
    elif rel_humidity < 0.66 * temp + 63:
        weather = 2
    elif rel_humidity < 0.66 * temp + 73:
        weather = 3  # Changeable
    elif rel_humidity < 0.66 * temp + 83:
        weather = 4
    elif rel_humidity >= 0.66 * temp + 83:
        weather = 5  # Probably rainy
    return {'text': "Local Estimate", 'code': weather, 'temp': float(temp)}

def parselines(s):
    lines = s.splitlines()
    d = {}
    for line in lines:
        p = parse("{}: {}",line)
        if p:
            d[p[0]] = p[1]
    return d

def getWifiStatus():
    #w = subprocess.check_output(["type", "WifiExample.txt"], shell=True)  # Shell needed for type command, should not be needed for running Prettyprint
    w = subprocess.check_output("/usr/bin/pretty-wifi-info.lua")
    p = parselines(w)

    for key in ('Mode','Interface name','SSID','Signal','Encryption method','Active for','IP address','MAC address','RX/TX'):
        p.setdefault(key,'Unknown')

    return p

def main():
    # Todo: Get these from serial port
    temp = 10
    humid = 70
    try:
        w = getWifiStatus()
        if w['Mode'] == "Client" :
            loc = get_location()
            weather_url = build_url(loc)
            r = call_api(weather_url)
            j = json.loads(r)
            weather = parse_weather(j)
        else:
            weather = guess_weather(humid,temp)

        print 'OK!,%s,%s,%4.2f' % (weather['text'], weather['code'], weather['temp'])

        return 0

    except Exception, err:
        weather = guess_weather(humid,temp)
        print 'Err,%s,%s,%4.2f' % (str(err).replace(",", " "),weather['code'], weather['temp'])
        return 1


if __name__ == '__main__':
    sys.exit(main())


