#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "cd437185-618c-438b-a81e-e24f788fc80a";

const char SSID[]               = "Inteli.Iot";    // Network SSID (name)
const char PASS[]               = "@Intelix10T#";    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = "AiiXi#iOIeic0gSnUqHvIogJI";    // Secret device password

void onSinalChange();

float sinal;

void initProperties(){
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(sinal, READWRITE, ON_CHANGE, onSinalChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
