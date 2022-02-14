//esther bogorov

#include "ofApp.h"
//images must ALWAYS load in the same EXACT way for the sake of later reading from the text file and making new diagrams etc thus stay in fullscreen for operation

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofSetWindowTitle("diagramApp");
    ofSetFullscreen(1);

    d = 0;
    imgID = 0;
    gameID = 0;
    
    part.assign(5, string);
    practice.assign(5, string);
    displayString.assign(5, string);
    diagramPoints.assign(1, ofPoint());
    diagramPoints.reserve(10);
    diagramPointsGame.reserve(25);
    
    
    displayGameStats = 0;
    displayStillStats = 0;
    drawGameStill = 1;
    writeInstr = 1;
    drawPath = 0;
    blackFont = 0;
    last = 0;
    
    icon.load("icon.png");
    
    gameStillDiagram.allocate(ofGetScreenWidth(), ofGetScreenHeight(), OF_IMAGE_COLOR);
    
    statsFile.defineNames();
}
//--------------------------------------------------------------
void ofApp::setupDirectory(int dirID){
    dir.allowExt("png");
    
    if (dirID == MONUMENTVALLEY){
        gameID = MONUMENTVALLEY;
        dir.listDir("stills/monumentValley/");
        gameName.assign("monumentValley");
        
    } else if (dirID == GRIS){
        gameID = GRIS;
        dir.listDir("stills/gris/");
        gameName.assign("gris");
        
    } else if (dirID == JOURNEY){
        gameID = JOURNEY;
        dir.listDir("stills/journey/");
        gameName.assign("journey");
    }
    
    if (dir.size()){
        gameStills.assign(dir.size(), ofImage());
    }
    
    for (int i = 0; i < (int)dir.size(); i++){
        gameStills.at(i).load(dir.getPath(i));
    }
    
    displayGameStats = 0;
    imgID = 0;
    
    imgW = gameStills.at(0).getWidth();
    imgH = gameStills.at(0).getHeight();
    statsFile.setupFile(gameName, imgID, dir);
    //statsFile Clean all data
    diagramLabels.open("diagramLabels/" + gameName + "/" + dir.getFile(imgID).getBaseName()  + ".txt", ofFile::WriteOnly);
}

//--------------------------------------------------------------
void ofApp::update(){
    loadTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);
    ofBackground(0);
    ofSetColor(255);
    
    if (dir.size()){
        if (drawGameStill){
            gameStills.at(imgID).draw(0, 15);
        }
        for (int i = 0; i < d; i++){
            if(blackFont){
                ofSetColor(0,0,0,255);
            }
            ofDrawBitmapString(displayString.at(i), diagramPoints.at(i));
            ofSetColor(255);
        }
    }
    
    if (displayStillStats){
        ofDrawBitmapString("scene stats recorded", 20, ofGetScreenHeight() - 50);
    }
    
    if (drawCircle){
        int c = 255;
        if (blackFont) c = 0;
        ofSetColor(c, 100);
        ofDrawCircle(click.x, click.y, 10);
        ofSetColor(255, 255);
        
    }
    if (writeInstr){
        ofBackground(0);
        ofSetColor(0);
        ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
        ofSetColor(255);
        writeInstructions();
    }else{
        std::string str = (gameName + " | scene " + to_string(imgID) + " || space | threshold | path | edge | focus || naming | sequencing | revealing & concealing | gathering | opening ");
        ofDrawBitmapString(str, 10, 10);
    }
    if (last){
        drawGameDiagram();
        ofDrawBitmapString(gameName, 10, 10);
    }
    if (drawPath){
        drawStippledPath(diagramPoints);
    }
    
    if (loadTime < 3.0){
        ofSetColor(0);
        ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight()); //background
        ofSetColor(255);
        icon.setAnchorPoint(icon.getWidth()/2, icon.getHeight()/2);
        icon.draw(ofGetScreenWidth()/2, ofGetScreenHeight()/2);
    }
    
}
//--------------------------------------------------------------

void ofApp::drawGameDiagram(){
    //draws all the points of interest in the game on one diagram
    
    ofBackground(0);
    ofSetColor(0);
    ofDrawRectangle(0, 0, ofGetScreenWidth(), ofGetScreenHeight()); //background
    ofSetColor(255);
    ofNoFill();
    ofDrawRectangle(1, 15, imgW, imgH); //border
    ofFill();
    for (const ofPoint p : diagramPointsGame){
        ofDrawCircle(p.x, p.y, 3);
    }
    
    gameStillDiagram.grabScreen(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    gameStillDiagram.save("diagrams/" + gameName + "/diagram_gamePoints.png");

}
//--------------------------------------------------------------

void ofApp::writeInstructions(){
    ofBuffer buffer = ofBufferFromFile("instructions.txt"); // reading into the buffer
    std::string str = buffer.getText();
    ofDrawBitmapString(str, 20, 20);
}

//--------------------------------------------------------------
void ofApp::drawStippledPath(vector<ofPoint>& vec){
    //nonspecific path drawing so it can later be adjusted for a lot of paths on one diagram if relevant
    
    ofSetColor(255);
    ofNoFill();
    ofDrawRectangle(1, 15, imgW, imgH); //border
    ofFill();
    
    
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(3, 0xAAAA);
    glBegin(GL_LINES);
    
    int x, x1;
    int y, y1;
    for (int i = 0; i < vec.size() - 2; i++){ //check this edge case sitch//seemsok
        x = (int)vec.at(i).x;
        y = (int)vec.at(i).y;
        
        x1 = (int)vec.at(i+1).x;
        y1 = (int)vec.at(i+1).y;
        
        glVertex2f (x, y);
        glVertex2f (x1, y1);
        
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glFlush();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (drawCircle){
        drawCircle = 0;
    }
    //keys as ID to switch between game directories
    switch (key){
        case '0':
            setupDirectory(0);
            writeInstr = 0;
            last = 0;
            break;
            
        case '1':
            setupDirectory(1);
            writeInstr = 0;
            last = 0;
            break;
            
        case '2':
            setupDirectory(2);
            writeInstr = 0;
            last = 0;
            break;
    }
    
    //keys as ID for morphological parts and narrative practices
    switch (key){
            //space, threshold, path, edge, focus
        case 's': string.push_back('s');
            break;
        case 't': string.push_back('t');
            break;
        case 'p': string.push_back('p');
            break;
        case 'e': string.push_back('e');
            break;
        case 'f': string.push_back('f');
            break;
            //naming, sequencing, revealing/concealing, gathering, opening
        case 'n': string.push_back('n');
            break;
        case 'q': string.push_back('q');
            break;
        case 'r': string.push_back('r');
            break;
        case 'g': string.push_back('g');
            break;
        case 'o': string.push_back('o');
            break;
    }
    
    //functional keys related to data writing and saving
    switch (key){
        case 'b':
            blackFont = !blackFont;
            break;
        case 'i':
            writeInstr = !writeInstr;
            break;
        case ' ':
            part.at(d) = string;
            partTotal.insert(partTotal.end(), part.at(d));
            string.push_back('|');
            displayString.at(d) = string;
            string.clear();
            break;
            
        case OF_KEY_RETURN:
            //for use with video - creating big stream of info
            //buff.set(string.c_str(), string.size());
            //diagramLabels.writeFromBuffer(buff);
            //buff.clear();
            
            displayString.at(d) += string;
            practice.at(d) = string;
            string.push_back('|');
            practiceTotal.insert(practiceTotal.end(), practice.at(d));
            
            //write csv: point number, x location, y location, part string, practice string on one line
            diagramLabels <<d <<"," <<click.x <<"," <<click.y <<"," <<part.at(d) <<"," <<practice.at(d) <<endl;
            
            diagramPoints.at(d) = click;
            string.clear();
            d++;
            break;
            
        case OF_KEY_SHIFT:
            //annotated game stills, note path drawn after this is run. documented as "raw" ie reference ie og
            gameStillDiagram.grabScreen(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
            gameStillDiagram.save("diagramsRaw/" + gameName + "/" + dir.getFile(imgID).getBaseName() + "_diagramRaw.png");
            
            statsFile.printStats(d, part, practice);
            
            drawPath = 1;
            displayStillStats = 1;
            drawGameStill = 0;
            blackFont = 0;
            
            diagramPointsGame.insert(diagramPointsGame.end(), diagramPoints.begin(), diagramPoints.end()-1);
            break;
            
        case OF_KEY_BACKSPACE:
            //clean gameTotalStats according to error
            clearAll();
            break;
            
        case OF_KEY_RIGHT:
            drawGameStill = 1;
            gameStillDiagram.grabScreen(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
            
            //gameStillDiagram.grabScreen(0, 0, imgW, imgH); //buggyaf,ytho
            
            gameStillDiagram.save("diagrams/" + gameName + "/" + dir.getFile(imgID).getBaseName() + "_diagram.png");
            
            diagramLabels.close();
            
            if (imgID == (int)dir.size() - 1) {
                finalize();
            } else if (imgID < (int)dir.size() - 1) {
                imgID++;
                imgW = gameStills.at(imgID).getWidth();
                imgH = gameStills.at(imgID).getHeight();
                diagramLabels.open("diagramLabels/" + gameName + "/" + dir.getFile(imgID).getBaseName()  + ".txt", ofFile::WriteOnly);
            }
            
            drawPath = 0;
            clearAll();
            break;
    }
}
//--------------------------------------------------------------
void ofApp::clearAll(){
    //clear all
    string.clear();
    part.clear();
    practice.clear();
    displayString.clear();
    diagramPoints.clear();
    
    part.resize(10);
    practice.resize(10);
    displayString.resize(10);
    diagramPoints.resize(1);
    
    d = 0;
    displayStillStats = 0;
    
    
}
//--------------------------------------------------------------
void ofApp::finalize(){
    
    displayGameStats = 1;
    statsFile.printGameList(diagramPointsGame, partTotal, practiceTotal);
    
    last = 1;
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (x!=0 && y!=0){
        drawCircle = 1;
        
        click.x = x;
        click.y = y;
        
        if (d == diagramPoints.size()-1){
            diagramPoints.resize(diagramPoints.size() + 1);
        }
    }
    
}
//--------------------------------------------------------------

