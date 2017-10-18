#!/usr/bin/env python
# -*- coding: utf_8 -*-
# 詮能科技 超倍能BMS電池管理系統讀表

"""
 Modbus TestKit: Implementation of Modbus protocol in python

 (C)2009 - Luc Jean - luc.jean@gmail.com
 (C)2009 - Apidev - http://www.apidev.fr

 This is distributed under GNU LGPL license, see license.txt
"""
import fcntl
import struct
import ConfigParser
import serial
import requests
import modbus_tk
import modbus_tk.defines as cst
from modbus_tk import modbus_rtu
import time

#PORT = 1
#PORT = '/dev/ttyAMA0'
#PORT = '/dev/ttyS0'

# your API key here
#API_KEY = "b66c94a03e6ab53d3f3ef4a09abee385"
#remote url
#CEMS_URL= "http://104.154.116.241/mactronic/input/post.json?node="
#NODE_NAME = "SDP_BMS_"
#DEVICE_ID = 1

def main():

        #logger = modbus_tk.utils.create_logger("console")

        try:
            while 1:

                time.sleep(5)
                #Connect to the slave
                master = modbus_rtu.RtuMaster(
                    serial.Serial(port=PORT, baudrate=9600, bytesize=8, parity='N', stopbits=1, xonxoff=0)
                )
                master.set_timeout(3.0)
                master.set_verbose(True)
                print "connected"

                print getMAC(interface='wlan0')
                MAC_ADD = getMAC(interface='wlan0')
#                print MAC_ADD

                time.sleep(5)

                #BCM2835 core temperature
                file = open("/sys/class/thermal/thermal_zone0/temp")
                temp = float(file.read())/1000
                file.close()
                print "CPU temperatre: %0.1f" %temp
                API_ENDPOINT = CEMS_URL + NODE_NAME + MAC_ADD+"&json={"\
                +'CPU_Temperature: '+str(temp)\
                +"}&apikey="+API_KEY
                r = requests.post(url = API_ENDPOINT)

                #BMS system information
                print(" ** main battery box info **")
                string_1 = master.execute(DEVICE_ID, cst.READ_INPUT_REGISTERS, 1, 11)
                print string_1
                API_ENDPOINT = CEMS_URL + NODE_NAME + MAC_ADD+"&json={"\
                +'BMS_total_voltage: '+str(string_1[0]) +','\
                +'BMS_SOC: '+str(string_1[1]) +','\
                +'BMS_total_Current: '+str(string_1[2]) +','\
                +'Single_Highest_Voltage: '+str(string_1[3]) +','\
                +'Single_Lowest_Voltage: '+str(string_1[4]) +','\
                +'Bty_Highest_Temp: '+str(string_1[5]) +','\
                +'Bty_total_Cap: '+str(string_1[6]) +','\
                +'Bty_Remain_Cap: '+str(string_1[7]) +','\
                +'Warrent: '+str(string_1[8]) +','\
                +'Bty_Lowest_Temp: '+str(string_1[9]) +','\
                +'Warrent2: '+str(string_1[10])\
                +"}&apikey="+API_KEY
                r = requests.post(url = API_ENDPOINT)
                time.sleep(5)

                #M1 Battery Single Cell Voltage information
                print(" ** M1 Battery Single Cell information **")
                M1_msg = master.execute(DEVICE_ID, cst.READ_INPUT_REGISTERS, 101, 18)
                print M1_msg
                API_ENDPOINT = CEMS_URL + NODE_NAME + MAC_ADD+"&json={"\
                +'M1_Reg1: '+str(M1_msg[0]) +','\
                +'M1_Reg2: '+str(M1_msg[1]) +','\
                +'M1_Reg3: '+str(M1_msg[2]) +','\
                +'M1_Reg4: '+str(M1_msg[3]) +','\
                +'M1_Reg5: '+str(M1_msg[4]) +','\
                +'M1_Reg6: '+str(M1_msg[5]) +','\
                +'M1_Reg7: '+str(M1_msg[6]) +','\
                +'M1_Reg8: '+str(M1_msg[7]) +','\
                +'M1_Reg9: '+str(M1_msg[8]) +','\
                +'M1_Reg10: '+str(M1_msg[9]) +','\
                +'M1_Reg11: '+str(M1_msg[10]) +','\
                +'M1_Reg12: '+str(M1_msg[11]) +','\
                +'M1_Reg13: '+str(M1_msg[12]) +','\
                +'M1_Reg14: '+str(M1_msg[13]) +','\
                +'M1_Reg15: '+str(M1_msg[14]) +','\
                +'M1_Reg16: '+str(M1_msg[15]) +','\
                +'M1_Reg17: '+str(M1_msg[16]) +','\
                +'M1_Reg18: '+str(M1_msg[17])\
                +"}&apikey="+API_KEY
                r = requests.post(url = API_ENDPOINT)
                time.sleep(5)

                #M2 Battery Single Cell information
                print(" ** M2 Battery Single Cell information **")
                M2_msg = master.execute(DEVICE_ID, cst.READ_INPUT_REGISTERS, 201, 18)
                print M2_msg
                API_ENDPOINT = CEMS_URL + NODE_NAME + MAC_ADD+"&json={"\
                +'M2_Reg1: '+str(M2_msg[0]) +','\
                +'M2_Reg2: '+str(M2_msg[1]) +','\
                +'M2_Reg3: '+str(M2_msg[2]) +','\
                +'M2_Reg4: '+str(M2_msg[3]) +','\
                +'M2_Reg5: '+str(M2_msg[4]) +','\
                +'M2_Reg6: '+str(M2_msg[5]) +','\
                +'M2_Reg7: '+str(M2_msg[6]) +','\
                +'M2_Reg8: '+str(M2_msg[7]) +','\
                +'M2_Reg9: '+str(M2_msg[8]) +','\
                +'M2_Reg10: '+str(M2_msg[9]) +','\
                +'M2_Reg11: '+str(M2_msg[10]) +','\
                +'M2_Reg12: '+str(M2_msg[11]) +','\
                +'M2_Reg13: '+str(M2_msg[12]) +','\
                +'M2_Reg14: '+str(M2_msg[13]) +','\
                +'M2_Reg15: '+str(M2_msg[14]) +','\
                +'M2_Reg16: '+str(M2_msg[15]) +','\
                +'M2_Reg17: '+str(M2_msg[16]) +','\
                +'M2_Reg18: '+str(M2_msg[17])\
                +"}&apikey="+API_KEY
                r = requests.post(url = API_ENDPOINT)
                time.sleep(5)

                #Charger information
                print(" ** charger output info **")
                String_6 = master.execute(DEVICE_ID, cst.READ_INPUT_REGISTERS, 5001, 2)
                print String_6
                API_ENDPOINT = CEMS_URL + NODE_NAME + MAC_ADD+"&json={"\
                +'Charger_Output_Voltage: '+str(String_6[0]*0.1) +','\
                +'Charger_Output_Current: '+str(String_6[1]*0.1)\
                +"}&apikey="+API_KEY
                r = requests.post(url = API_ENDPOINT)

        except modbus_tk.modbus.ModbusError, e:
            print "Modbus error", e.get_exception_code()
            #pass
        ##    except Exception, e2:
        ##        #print "Error", str(e2)
        ##        pass
        finally:
            main()

def getMAC(interface='wlan0'):
  # Return the MAC address of the specified interface
    try:
        str = open('/sys/class/net/%s/address' %interface).read()
    except:
        str = "00:00:00:00:00:00"
    return str[0:17]
    MAC = str(getMAC('wlan0')) + "_DEMO"

    self.serial_connect()


if __name__ == "__main__":
    cfg = ConfigParser.ConfigParser()
    with open('/home/l412/SDP_SYSTEM.cfg', 'rb') as fp:
        cfg.readfp(fp, '/home/l412/SDP_SYSTEM.cfg')

    host = cfg.get('ModbusTCP','host')
    TCP_port = cfg.get('ModbusTCP','TCP_port')

    RTU_port = cfg.get('ModbusRTU','RTU_port')
    baudrate = cfg.get('ModbusRTU','baudrate')
    bytesize = cfg.get('ModbusRTU','bytesize')
    stopbits = cfg.get('ModbusRTU','stopbits')
    parity = cfg.get('ModbusRTU','parity')
    timeout = cfg.get('ModbusRTU','timeout')
    gpio = cfg.get('ModbusRTU','gpio')

    URL = cfg.get('CEMS_APIKEY','URL')
    API_KEY = cfg.get('CEMS_APIKEY','API_KEY')
    NODE_NAME = cfg.get("CEMS_APIKEY",'NODE_NAME')

    BMS_DEVICE_ID = cfg.get('DeviceID','BMS_DEVICE_ID')
    IVT_DEVICE_ID = cfg.get('DeviceID','IVT_DEVICE_ID')
    PLC_DEVICE_ID = cfg.get('DeviceID','PLC_DEVICE_ID')

    print "host:" + host
    print "TCP_Port:" + TCP_port
    print "RTU_port:" + RTU_port
    print "baudrate:" + baudrate
    print "bytesize:" + bytesize
    print "stopbits:" + stopbits
    print "parity:" + parity
    print "timeout:" + timeout
    print "gpio:" + gpio
    print "RTU_port:" + RTU_port
    print "URL:" + URL
    print "API_KEY:" + API_KEY
    print "NODE_NAME:" + NODE_NAME
    print "BMS_DEVICE_ID:" + BMS_DEVICE_ID
    print "IVT_DEVICE_ID:" + IVT_DEVICE_ID
    print "PLC_DEVICE_ID:" + PLC_DEVICE_ID

    main()
