// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;
const int ledPin = 7;


MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
    

START_INIT:

    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}
unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char stmp2[8] = {1, 0, 0, 0, 0, 0, 0, 0};
void loop()
{
    // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x00, 0, 8, stmp);
    delay(200);                       // send data per 100ms
    CAN.sendMsgBuf(0x00, 0, 8, stmp2);
    delay(200);
    digitalWrite(ledPin, HIGH);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
