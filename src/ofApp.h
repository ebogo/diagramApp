//esther bogorov

#pragma once
#include "ofMain.h"
#include "stats.h"
#include "ofxGui.h"

//for legibility in directory setup fxn
enum {MONUMENTVALLEY, GRIS, JOURNEY};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    //ofApp functions not in use
    //void keyReleased(int key);
    //void mouseMoved(int x, int y );
    //void mouseDragged(int x, int y, int button);
    //void mouseReleased(int x, int y, int button);
    //void mouseEntered(int x, int y);
    //void mouseExited(int x, int y);
    //void windowResized(int w, int h);
    //void dragEvent(ofDragInfo dragInfo);
    //void gotMessage(ofMessage msg);
    
   //drawing & indexing
    float loadTime;
    ofImage icon;

    void writeInstructions();
    void drawStippledPath(vector<ofPoint>& vec);
    void setupDirectory(int dirID);

    vector<ofImage> gameStills;
    int imgW, imgH;

    bool writeInstr;
    bool blackFont;
    bool drawPath;
    bool drawGameStill;
    bool displayGameStats; //being turned on/off but not currently controlling anything. in case stats should be reported onscreen w/the diagram
    bool displayStillStats; //doesnt display just reports that thing were recorded. ie, as above.
    
    int imgID;
    int gameID;
    std::string gameName;
    
    ofDirectory dir;
    
    //processing
    void drawGameDiagram();
    void clearAll();
    void finalize();
    
    vector<std::string> part;
    vector<std::string> practice;
    vector<std::string> partTotal;
    vector<std::string> practiceTotal;
    vector<std::string> displayString;
    vector<ofPoint> diagramPoints;
    vector<ofPoint> diagramPointsGame;

    ofPoint click;
    std::string string; //sry :/
    
    int d;
    
    bool drawCircle; //marks clicks
    bool last;

    //writing to files
    ofFile diagramLabels;
    ofImage gameStillDiagram;
    Stats statsFile;
    
};
