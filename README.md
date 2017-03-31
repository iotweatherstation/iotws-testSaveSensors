# iotws-testSaveSensors

* project: IoT Weather Station, EAFIT University, Systems Engineering, 20171
* Adaptation done by: Edwin Montoya Munera - emontoya@eafit.edu.co and David Velasquez - dvelas25@eafit.edu.co
* github: https://github.com/iotweatherstation/iotws-testSaveSensors.git

* Description: This program test the connection to the server "iotweatherstation" in order to SAVE: idhome, temp, humid and timestamp (YYYY-MM-DDTHH:MM:SS.0Z)
* the connection is done throught Wifi network and HTTP Connection. It uses GET Method.

* use this services from Backend IoT Server Weather Station

    1. http://<server>/weather/getTime

    2. http://<server>/weather/saveSensors?idhome=<username>&temp=<val>&humid=<val>&timestamp=<date>

    
