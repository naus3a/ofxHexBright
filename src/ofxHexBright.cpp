//
//  ofxHexBright.h
//
//  Created by enrico<nausea>viola on 11/24/14.
//
//


#include "ofxHexBright.h"

//init stuff
ofxHexBright::ofxHexBright(){
    brightness = 0.5;
    time = 1;
    curPort = "";
}

ofxHexBright::~ofxHexBright(){
    disconnect();
}

void ofxHexBright::setup(string port){
    curPort = port;
    serial.setup(curPort, 9600);
}

bool ofxHexBright::isConnected(){
    return serial.isInitialized();
}

void ofxHexBright::disconnect(){
    curPort = "";
    serial.close();
}

vector<ofSerialDeviceInfo> ofxHexBright::getAvailableDevices(){
    return serial.getDeviceList();
}
//---

//protocol
void ofxHexBright::sendRaw(unsigned char byte){
    serial.writeByte(byte);
}

unsigned char ofxHexBright::makeProtocolPacket(bool fla, float briPct, float fadeTm){
    // [B][B][B][T][T][T][T][F]
    unsigned char pkt;
    pkt = 0;
    
    //3 bits for bightness
    // capacity: 0-7, using 0-5
    unsigned int bitBright = int(briPct*5.0);
    //if(!fla){
    //    bitBright=int(briPct*5.0);
    //}
    
    //4 bits for time
    //capacity: 0-15, using as seconds
    unsigned int bitTime = int(ofClamp(fadeTm,0,15));
    
    unsigned int bitFla = (int)fla;
    
    pkt = (bitBright << 5) | (bitTime << 1) | bitFla;
    
    //to unpack:
    /*cout<<"flash: "<<bitFla<<" time: "<<bitTime<<" bright: "<<bitBright<<endl;
    unsigned int bf = pkt & 1;
    unsigned int bb = (pkt >> 5);
    unsigned int bt = (pkt >> 1) - (bb << 4);
    cout<<"flash: "<<bf<<" time: "<<bt<<" bright: "<<bb<<endl;*/
    
    return pkt;
}
//---

//easy calls
void ofxHexBright::flash(){
    //sendRaw(1);
    sendRaw(makeProtocolPacket(true, getClampedBrightness(), time));
}
void ofxHexBright::fadeIn(){
    //unsigned char byte = (unsigned char)(brightness*255);
    //if(byte<2)byte=2;
    //sendRaw(byte);
    sendRaw(makeProtocolPacket(false, getClampedBrightness(), time));
}

void ofxHexBright::fadeOut(){
    //sendRaw(0);
    sendRaw(makeProtocolPacket(false, 0, time));
}

void ofxHexBright::turnOn(){
    time = 0;
    sendRaw(makeProtocolPacket(false, getClampedBrightness(), time));
}

void ofxHexBright::turnOff(){
    time = 0;
    sendRaw(makeProtocolPacket(false, 0, time));
}
//---

float ofxHexBright::getClampedBrightness(){
    return (brightness<0.2?0.2:brightness);
}