# Get the Wifi Status into a dictionary
import subprocess
from parse import *

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

p = getWifiStatus()

print p['Mode']
print p['Interface name']
print p['SSID']
print p['Signal']
print p['Encryption method']
print p['Active for']
print p['IP address']
print p['MAC address']
print p['RX/TX']