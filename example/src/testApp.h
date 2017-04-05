#pragma once

#include "ofMain.h"
#include "ofxHexBright.h"
#include "ofxXmlSettings.h"
#include "ofxUI.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void guiEvent(ofxUIEventArgs & e);
    void guiEventPorts(ofxUIEventArgs & e);
    
    void setPortsGUI(bool b);
		
    ofxHexBright hb;
    
    ofxUICanvas * gui;
    ofxUISlider * sliBright;
    ofxUINumberDialer * nuTime;
    ofxUILabelButton * butFadeIn;
    ofxUILabelButton * butFadeOut;
    ofxUILabelButton * butFlash;
    ofxUILabelToggle * togPorts;
    ofxUILabel * labConnect;
    ofxUILabelButton * butOn;
    ofxUILabelButton * butOff;
    
    ofxUICanvas * guiPorts;
    
    bool bPorts;
};
