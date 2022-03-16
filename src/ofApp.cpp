#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofDirectory dir;
    dir.listDir("scenesWindow");
    for (int i = 0; i < dir.size(); i++){
        ofImage img;
        images.push_back(img);
        images.back().load(dir.getPath(i));
        //start
        cout << "loaded " << i << " of " << dir.size() << endl;
        //end
        
        imageData data;
        data.headPoint.set(0,0);
        data.feetPoint.set(0,0);
        datas.push_back(data);

        //start
        ofRectangle targetDim(0, 0, 1280, 720);
        ofRectangle imageDim(0, 0, images.back().getWidth(),
            images.back().getHeight());

        targetDim.scaleTo(imageDim);

        images.back().crop(targetDim.x, targetDim.y, targetDim.width, targetDim.height);
        images.back().resize(1920, 1080);
        //end
    }
    whichImage = 0;
    

    datas[0].headPoint.set(661, 228);
    datas[0].feetPoint.set(661, 855);
    datas[1].headPoint.set(614, 226);
    datas[1].feetPoint.set(614, 757);
    datas[2].headPoint.set(774, 192);
    datas[2].feetPoint.set(774, 897);
    datas[3].headPoint.set(1187, 474);
    datas[3].feetPoint.set(1187, 715);
    datas[4].headPoint.set(976, 290);
    datas[4].feetPoint.set(976, 733);
    datas[5].headPoint.set(737, 197);
    datas[5].feetPoint.set(737, 722);
    datas[6].headPoint.set(1268, 145);
    datas[6].feetPoint.set(1268, 734);
    datas[7].headPoint.set(501, 252);
    datas[7].feetPoint.set(501, 707);
    datas[8].headPoint.set(1668, 642);
    datas[8].feetPoint.set(1668, 1136);
    datas[9].headPoint.set(1023, 292);
    datas[9].feetPoint.set(1023, 817);
    datas[10].headPoint.set(1329, 70);
    datas[10].feetPoint.set(1329, 776);
    
    // average



    average.allocate(1920, 1080, OF_IMAGE_COLOR);

    for (int i = 0; i < 1920; i++) {
        for (int j = 0; j < 1080; j++) {

            // average:
            // (1) add all values up
            float sumRed = 0;
            float sumBlue = 0;
            float sumGreen = 0;
            for (int k = 0; k < images.size(); k++) {
                ofColor color = images[k].getColor(i, j);
                sumRed += color.r;

                sumGreen += color.g;
                sumBlue += color.b;
            }
            // (2) divide
            sumRed /= (float)images.size();
            sumBlue /= (float)images.size();
            sumGreen /= (float)images.size();
            average.setColor(i, j, ofColor(sumRed, sumGreen, sumBlue));


        }
    }

    average.update();




}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    //ofScale(1, 1);
    //ofSetColor(255);
    //images[ whichImage ].draw(0,0);
    //ofSetColor(255,0,0);
    //ofDrawCircle(datas[ whichImage ].headPoint, 5);
    //ofSetColor(0,255,0);
    //ofDrawCircle(datas[ whichImage ].feetPoint, 5);
    
    
    // once we have data:
    
    
    ofPushMatrix();
    ofTranslate(500,500);
    images[ whichImage ].setAnchorPoint(datas[ whichImage ].headPoint.x, datas[ whichImage ].headPoint.y);
    
    ofPoint diff = datas[ whichImage ].feetPoint -
                    datas[ whichImage ].headPoint;
    float length = diff.length();
    float angle = 0;
    float scale = 700. / length;
    
    ofScale(scale, scale);
    ofRotateZRad(angle);
    //images[ whichImage ].draw(0,0);
    ofPopMatrix();

    average.draw(0, 0);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == OF_KEY_RIGHT){
        whichImage ++;
        whichImage %= images.size();
    } else if (key == OF_KEY_LEFT){
        whichImage--;
        if (whichImage < 0) whichImage += images.size();
    }
    
    if (key == ' '){
        
        for (int i = 0; i < datas.size(); i++){
            cout << "datas[" << i << "].headPoint.set(" <<
                datas[i].headPoint.x <<"," <<
            datas[i].headPoint.y <<");" << endl;
            cout << "datas[" << i << "].feetPoint.set(" <<
                datas[i].feetPoint.x <<"," <<
            datas[i].feetPoint.y <<");" << endl;
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    float newx = x;
    float newy = y;
    
    
    if (clickCount %2 == 0){
        datas[ whichImage ].headPoint.set(newx,newy);
    } else {
        datas[ whichImage ].feetPoint.set(newx, newy);
    }
    
    clickCount++;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
