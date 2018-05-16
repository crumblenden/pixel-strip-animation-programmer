//
//  Comm.cpp
//  emptyExample
//
//  Created by Chris Lynden on 08/03/2018.
//
//


#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::createMessage() {
    u_int8_t opener = '<';
    u_int8_t closer = '>';
    message.clear();
    message.push_back(opener);
    for(int j = 0; j < numStrips; j++) {
        for(int i  = 0; i < strips[j].numLeds*3; i++) {
            message.push_back(strips[j].ledData[i]);
        }
    }
    message.push_back(closer);
}

//--------------------------------------------------------------

void ofApp::transmitMessage() {
    
    serial.flush(false, true);
    if(serial.available() > 0) {
        unsigned char byteRecieved = 'x';
        byteRecieved = serial.readByte();
        if(byteRecieved == 'R'){
            serial.writeBytes( &message[0], 182);
        }
    }
}

//--------------------------------------------------------------

void ofApp::testSerial() {
    //    u_int8_t a = 'N';
    //    int ia = (int)a;
    //    cout<<"a: "<<ia<<endl;
    serial.flush(false, true);
    if(serial.available() > 0) {
        unsigned char byteRecieved = 'x';
        byteRecieved = serial.readByte();
        cout<<"byte recieved: "<<byteRecieved<<endl;
        if(byteRecieved == 'R'){
            unsigned char dataToSend[4] = {'d', 'a', 't', 'a'};
            for(int i = 0; i < sizeof(dataToSend); i++) {
                serial.writeByte(dataToSend[i]);
                //cout<<"sent: " <<dataToSend[i]<<endl;
            }
            //serial.writeBytes( &dataToSend[0], 4);
            cout<<"sent data"<<endl;
        }
        if(byteRecieved == 'K') {
            if(!started) {
                startUpTime = ofGetElapsedTimeMillis();
                started = true;
            }
            cout<<"//////////////////////////////////////////////////////////////////////"<<endl;
            successCount++;
            cout<<"Successful transmissions: " <<successCount<<endl;
            cout<<"Time since first successful transmission: "<<ofGetElapsedTimeMillis() - startUpTime<<endl;
            cout<<"Average transmissions per second: "<<(ofGetElapsedTimeMillis() - startUpTime)/successCount<<endl;
        }
    }
}