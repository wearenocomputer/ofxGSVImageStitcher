#pragma once

#include "ofMain.h"

struct PanoTile {
    int x;
    int y;
    ofImage image;
};




class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    void urlResponse(ofHttpResponse & response);
    
    float zoom;
    
    vector<PanoTile> panoTiles;
   
    ofFbo image;
    int imagecounter;
    int totalimages;
    
    void createPanoImage();
    
};
