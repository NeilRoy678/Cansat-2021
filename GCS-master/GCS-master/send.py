from dataclasses import dataclass
import paho.mqtt.client as mqtt
import time

mqttc = mqtt.Client()
#topic = '1012'
topic = 'teams/1012' 
mqttc.username_pw_set("1012", "Koiwsity751")

# The callback for when the client receives a CONNACK response from the server.
mqttc.connect("cansat.info",1883)
fd = open("D:\\HASHCODE\\final\\practice\\alt.csv","r") # open csv file
dat = fd.read() # read in whole file
fd.close()
dat = dat.split('\n') # split lines

while 1:
    for i in dat: # go through all the lines in the file
        b = i.split(',') # split line to locate element 3
        time.sleep(1) # insert 1 second interval unless payload adata
        print(i)
        mqttc.publish(topic, i) # send the line of data