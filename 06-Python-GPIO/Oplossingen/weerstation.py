##############################################################################
# Eenvoudig weerstation op basis van Raspberry Pico en temperatuur sensor    #
# Benodigheden:                                                              #
#   - Raspberry Pi Pico                                                      #
#   - USB kabeltje                                                           #
#   - Grove Shield                                                           #
#   - Temperatuur sensor                                                     #
#   - 16x02 LCD                                                              #
##############################################################################


from lcd1602 import LCD1602
from machine import I2C,Pin
from time import sleep
from dht11 import DHT


def setup():
    global dht,ic2, display
    
    # DHT11 temp sensor aansluiten op poort D18
    dht = DHT(16) 

    # LCD module aansluiten op D16
    i2c = I2C(1,scl=Pin(7), sda=Pin(6), freq=400000) # Connect I2C
    display = LCD1602(i2c, 2, 16) 


def main():
    # Herhaal alles hieronder tot het programma gestopt wordt
    while True:
        
        # Temperatuur uitlezen
        temp = dht.readTemperature()
        
        # LCD scherm leegmaken
        display.clear()
        
        # Toon tekst op eerste regel van LCD scherm
        display.print('*** MVI Emma ***')
        
        # Ga naar regel 2 van het LCD scherm
        display.setCursor(0,1)
        
        # Toon temperatuur op het LCD scherm
        display.print('Temp: {} C'.format(temp))

        # Wacht 5 seconden
        sleep(5)


setup()
main()
