# Take the two command line arguments and generate a 1 to 5 rating of it it will rain
# See http://www.tutorialspoint.com/python/python_command_line_arguments.htm

import sys, getopt

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
    return weather


def main(argv):
    try:
        opts, args = getopt.getopt(argv, 't:r:', ['temperature', 'relativehumidity'])
        for opt, arg in opts:
            if opt in ('-r', '--relativehumidity'):
                rel_humidity = float(arg)
            elif opt in ('-t', '--temperature'):
                temp = float(arg)
    except getopt.GetoptError:
        print 'test.py -r <relativehumidity> -t <temperature>'
        sys.exit(2)

    print guess_weather(rel_humidity, temp)


if __name__ == "__main__":
    main(sys.argv[1:])
