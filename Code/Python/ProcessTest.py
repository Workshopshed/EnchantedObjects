# Simple Process test.
import subprocess

# check if parse works ok on Yún
from parse import *

def parselines(s):
    lines = s.splitlines()
    d = {}
    for line in lines:
        p = parse("{}: {}",line)
        if p:
            d[p[0]] = p[1]
    return d

# Need to swap with pretty print
# Need to see what happens when no wifi connected
w = subprocess.check_output(["type", "WifiExample.txt"],
                    shell=True)  # Shell needed for type command, should not be needed for running Prettyprint

p = parselines(w)

print p['Mode']
print p['Interface name']
print p['SSID']
print p['Signal']
print p['Encryption method']
print p['Active for']
print p['IP address']
print p['MAC address']
print p['RX/TX']

# Also see http://www.tutorialspoint.com/python/python_command_line_arguments.htm




