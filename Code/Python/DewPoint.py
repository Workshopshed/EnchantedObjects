# http://iridl.ldeo.columbia.edu/dochelp/QA/Basic/dewpoint.html

def calc_dew(T, RH):
    Td = T - ((100 - RH)/5.)
    return Td

#Demo
print calc_dew(20,80)
print calc_dew(10,80)
print calc_dew(0,80)
print calc_dew(-5,80)

print calc_dew(20,90)
print calc_dew(10,90)
print calc_dew(0,90)
print calc_dew(-5,90)

print calc_dew(20,95)
print calc_dew(10,95)
print calc_dew(0,95)
print calc_dew(-5,95)

print calc_dew(20,100)
print calc_dew(10,100)
print calc_dew(0,100)
print calc_dew(-5,100)
