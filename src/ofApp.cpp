#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofRegisterURLNotification(this);
    
    zoom = 2.0f;
    
    int w = pow(2, zoom);
    
    float h = pow(2, zoom - 1);
    
    imagecounter = 0;
    
    totalimages = w*h;
    
    for (int y = 0; y < h; y++) {
        
        for (int x = 0; x < w; x++) {
            
            string url = "http://maps.google.com/cbk?output=tile&panoid=03s2pUakx4X6Whp_NUDo0Q&zoom=" + ofToString(zoom) + "&x=" + ofToString(x) + "&y=" + ofToString(y);
            ofLoadURLAsync(url, "TILE_" + ofToString(x) + "_" + ofToString(y));
        }
    }
}

void ofApp::urlResponse(ofHttpResponse & response) {
    
    if (response.status == 200) {
        if (ofIsStringInString(response.request.name, "TILE")) {
            vector<string> split = ofSplitString(response.request.name, "_");
            ofImage im;
            im.load(response.data);
            PanoTile tile;
            tile.x = ofToInt(split[1]);
            tile.y = ofToInt(split[2]);
            tile.image = im;
            panoTiles.push_back(tile);
        }
    }
   
    imagecounter++;
    
    if(imagecounter==totalimages) {
        createPanoImage();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    image.draw(0,0,512,256);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

void ofApp::createPanoImage() {
    float w = 416 * pow(2, zoom);
    float h = (416 * pow(2, zoom - 1));
    
    image.allocate(w, h);
    image.begin();
    
    ofPushMatrix();
    //in order for the image to be compliant with the depthmap we need to flip it
    ofTranslate(w, 0, 0);
    ofScale(-1, 1, 0);
    ofClear(255,0,0,255);
    
    for (int i = 0; i < panoTiles.size(); i++) {
        panoTiles[i].image.draw(panoTiles[i].x * 512, panoTiles[i].y * 512);
    }
    
    ofPopMatrix();
    image.end();

}
