import xbee
import serial
from paho.mqtt import client as mqttClient

PORT = 'COM3'
BAUD_RATE = 9600
telemetry = {}
KEYLIST = ["<TEAM_ID>","<MISSION_TIME>","<PACKET_COUNT>","<PACKET_TYPE>","<MODE>","<SP1_RELEASED>","<SP2_RELEASED>","<ALTITUDE>","<TEMP>","<VOLTAGE>","<GPS_TIME>","<GPS_LATITUDE>","<GPS_LONGITUDE>","<GPS_ALTITUDE>","<GPS_SATS>","<SP1_PACKET_COUNT>","<SP1_TIME>","<SP1_PACKET_TYPE>","<SP1_ALTITUDE>","<SP1_TEMP>","<SP1_ROTATION_RATE>","<SP2_PACKET_COUNT>","<SP2_TIME>","<SP2_PACKET_TYPE>","<SP2_ALTITUDE>","<SP2_TEMP>","<SP2_ROTATION_RATE>"]

class XBEEComms:
    def __init__(self):
        self.ser = serial.Serial(PORT, BAUD_RATE)
        for i in range(len(KEYLIST)):
            telemetry[KEYLIST[i]] = []
    
    def receiveTelemetry(self):
    # while True:
        try:
            response = xbee.wait_read_frame()
            for i in range(len(KEYLIST)):
                telemetry[KEYLIST[i]].append(response[i])
            print (telemetry)
        except KeyboardInterrupt:
            self.ser.close()
            break       

    #TODO complete this function. should only send the command once, not an infinite loop.
    def sendCommand(self, command):
        return

#TODO complete the class.
class MQTTComms:
    def __init__(self):
        return

    def sendTelemetry(self):
        return