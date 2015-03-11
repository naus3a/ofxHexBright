#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(150);
    ofSetFrameRate(30);
    
    string port = "/dev/tty.SLAB_USBtoUART";
    ofxXmlSettings xml;
    if(xml.load("port.xml")){
        port = xml.getValue("port", "/dev/tty.SLAB_USBtoUART");
    }
    
    hb.setup(port);
    
    gui = new ofxUICanvas();
    gui->setWidth(400);
    gui->setHeight(400);
    gui->addWidgetDown(new ofxUILabel("HexBright Remote Control",OFX_UI_FONT_LARGE));
    gui->addSpacer();
    string lPort = hb.isConnected()?"port: "+port : "not connected";
    labConnect = new ofxUILabel(lPort,OFX_UI_FONT_MEDIUM);
    gui->addWidgetDown(labConnect);
    bPorts = false;
    togPorts = new ofxUILabelToggle("Select Port",&bPorts);
    gui->addWidgetRight(togPorts);
    
    sliBright = new ofxUISlider("brightness", 0, 1, &hb.brightness, 100,10);
    gui->addWidgetDown(sliBright);
    
    nuTime = new ofxUINumberDialer(1,10,&hb.time,0,"seconds",OFX_UI_FONT_MEDIUM);
    gui->addWidgetRight(nuTime);
    
    butFadeIn = new ofxUILabelButton("Fade IN",false);
    butFadeOut= new ofxUILabelButton("Fade OUT",false);
    gui->addWidgetDown(butFadeIn);
    gui->addWidgetRight(butFadeOut);
    
    butFlash = new ofxUILabelButton("FLASH",false);
    gui->addWidgetDown(butFlash);
    
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    
    guiPorts = new ofxUICanvas();
    guiPorts->setWidth(400);
    guiPorts->setHeight(400);
    guiPorts->setPosition(gui->getRect()->x + gui->getRect()->width, 0);
    guiPorts->setVisible(false);
    ofAddListener(guiPorts->newGUIEvent, this, &testApp::guiEventPorts);
}

void testApp::guiEvent(ofxUIEventArgs &e){
    if(e.widget==butFlash){
        if(butFlash->getValue()){
            hb.flash();
        }
    }else if(e.widget==butFadeIn){
        if(butFadeIn->getValue()){
            hb.fadeIn();
        }
    }else if(e.widget==butFadeOut){
        if(butFadeOut->getValue()){
            hb.fadeOut();
        }
    }else if(e.widget==togPorts){
        setPortsGUI(togPorts->getValue());
    }
}

void testApp::guiEventPorts(ofxUIEventArgs &e){
    if(e.getKind()==OFX_UI_WIDGET_LABELBUTTON){
        ofxUILabelButton * but = (ofxUILabelButton *)e.widget;
        hb.disconnect();
        hb.setup(but->getName());
        string lPort = hb.isConnected()?"port: "+but->getName() : "not connected";
        labConnect->setLabel(lPort);
        bPorts =false;
        setPortsGUI(bPorts);
    }
}

void testApp::setPortsGUI(bool b){
    if(b){
        ofSetWindowShape(800, 400);
        guiPorts->removeWidgets();
        guiPorts->addWidgetDown(new ofxUILabel("Available ports:",OFX_UI_FONT_MEDIUM));
        vector<ofSerialDeviceInfo> devs = hb.getAvailableDevices();
        for(int i=0;i<devs.size();i++){
            guiPorts->addWidgetDown(new ofxUILabelButton(devs[i].getDevicePath(),false));
        }
        guiPorts->setVisible(true);
    }else{
        ofSetWindowShape(400, 400);
        //guiPorts->removeWidgets();
        guiPorts->setVisible(false);
    }
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
