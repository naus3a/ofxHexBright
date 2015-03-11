//
//  ofxHexBright.h
//
//  Created by enrico<nausea>viola on 11/24/14.
//
//

#pragma once
#include "ofMain.h"

class ofxHexBright{
public:
    
    ofxHexBright();
    ~ofxHexBright();
    void setup(string port);
    bool isConnected();
    void disconnect();
    vector<ofSerialDeviceInfo> getAvailableDevices();
    
    void sendRaw(unsigned char byte);
    static unsigned char makeProtocolPacket(bool fla=false, float briPct=0.5, float fadeTm=1.0);
    
    float getClampedBrightness();
    
    void flash();
    void fadeIn();
    void fadeOut();
    void turnOn();
    void turnOff();
    
    ofSerial serial;
    string curPort;
    float brightness; // between 0 and 1
    float time;
};