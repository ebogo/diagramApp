//esther bogorov

#include <stdio.h>
#include "stats.h"

//----------------------
void Stats::defineNames(){
    //setting up array with names for easier file writing/legibility
    
    partNames[0] = "space";
    partNames[1] = "threshold";
    partNames[2] = "path";
    partNames[3] = "edge";
    partNames[4] = "focus";
    
    practiceNames[0] = "naming";
    practiceNames[1] = "sequencing";
    practiceNames[2] = "revealing/concealing";
    practiceNames[3] = "gathering";
    practiceNames[4] = "opening";
    
}
//----------------------
void Stats::setupFile(const string& gameName, int imgID, const ofDirectory& dir){
    //prepare file to write to for analysis
    
    //file naming with the game name - everything in one big file
    diagramsSummary.open("summary/" + gameName + ".txt", ofFile::WriteOnly);
    diagramsSummaryList.open("summary/" + gameName + "_list.txt", ofFile::WriteOnly);
    
    //local scene ID ("imgID")
    counter = imgID;
    
    clearAll();
    
}
//----------------------
int Stats::clearAll(){
    //clean details for new directory
    
    partLocations.clear();
    practiceLocations.clear();
    
    fill_n(countPartTotal, 5, 0);
    fill_n(countPracticeTotal, 5, 0);
    
    return 0; //for later checking, if relevant?
}
//----------------------


int Stats::printStats(int d, const vector<string>& vec, const vector<string>& vec2){
    //print details of each scene diagram to one file stored in /summary under gameName
    //called from ofApp
    //receiving vec 1- parts in scene, vec 2 - practices in scene
    //looking ONLY AT PRIMARY DATA [that which the user enters first]
    
    diagramsSummary <<  "scene ID: " <<counter <<endl;
    
    //breakdowns of relationship in diagram between morphological parts and narrative practices
    int *countPart;
    countPart = Stats::analysisPart(d, vec, vec2);
    
    int *countPractice;
    countPractice = Stats::analysisPractice(d, vec, vec2);
    
    //occurences and percentages (still looking only at primary values assigned)
    //parts summary
    
    float total;
    float percent = 0.0;
    for (int i = 0; i < 5; i++){
        total += countPart[i];
    }
    
    diagramsSummary<<endl;
    for (int i = 0; i < 5; i++){
        percent = float(countPart[i])/total;
        
        diagramsSummary << partNames[i] <<" count: " <<countPart[i] << " percent of total: " << percent * 100 << "% " <<endl;
    }
    
    //practices summary
    total = 0.0;
    percent = 0.0;
    for (int i = 0; i < 5; i++){
        total += countPractice[i];
    }
    
    diagramsSummary<<endl;
    for (int i = 0; i < 5; i++){
        percent = float(countPractice[i])/total;
        diagramsSummary<< practiceNames[i] << " count: "<< countPractice[i] << " percent of total: " << percent * 100 << "% " <<endl;
        
    }
    //here it prints the entire list, each point in diagram comma delimited but point not specified
    statBasics(vec, vec2);
    
    diagramsSummary << "\nend analysis\n" << endl;
    
    counter++; //no need to pull imgID from ofApp
    return 0; //catch errors later
}

//----------------------
int* Stats::analysisPart(int d, const vector<string>& vec, const vector<string>& vec2){
    //the purpose of this function is to extract and sort only the "primary" values, the first ones the users eneter
    //each data point preserves its location on the map until this point, so that further analysis will make sense (data preservation)
    
    int* countPart = new int[5]();
    float total = 0.0;
    partLocations.assign (5, "");
    
    //analyzing the first character, which is supposed to be the primary morphological part at the point
    //can be adjusted for string to get the whole story (e.g. if a game is stacking a lot of parts and/or practices
    for (int i = 0; i < d; i++){
        char c = vec.at(i).front();
        char e = static_cast<char>(i+'0');
        
        //s: space t: threshold p: path e: edge f: focus
        //operating with the chars being sent in the vec, requires a rewrite in ofApp and then the fix would be here
        
        switch (c) {
            case 's':
                partLocations.at(SPACE).push_back(e);
                break;
            case 't':
                partLocations.at(THRESHOLD).push_back(e);
                break;
            case 'p':
                partLocations.at(PATH).push_back(e);
                break;
            case 'e':
                partLocations.at(EDGE).push_back(e);
                break;
            case 'f':
                partLocations.at(FOCUS).push_back(e);
                break;
        }
    }
    
    diagramsSummary << "\nprimary part analysis" << endl;
    
    string strPractice;
    for (int i =0; i < partLocations.size(); i++){
        countPart[i] = partLocations.at(i).length(); //count how many times a part occured
        countPartTotal[i] += countPart[i]; //record for game-wide report
        diagramsSummary << partNames[i] << " @ " << partLocations.at(i) << endl;
        
        strPractice = analysisPartPractice(partLocations[i], vec2); //analyze the practices occuring at the points according to the morphological part
        diagramsSummary <<  "primary practices: " << strPractice << endl;
    }
    
    return countPart; //ptr to count array
}

//----------------------
int* Stats::analysisPractice(int d, const vector<string>& vec, const vector<string>& vec2){
    int* countPractice = new int[5]();
    float total = 0.0;
    practiceLocations.assign (5, "");
    
    
    //n: naming, s: seQuencing, r: revealing & concealing, g: gathering, o: opening
    //analyzing the first character, which is supposed to be the primary narrative practice at the point
    
    
    for (int i = 0; i < d; i++){
        char c = vec2.at(i).front();
        char e = static_cast<char>(i+'0');
        
        
        switch (c) {
            case 'n':
                practiceLocations.at(NAMING).push_back(e);
                break;
            case 'q':
                practiceLocations.at(SEQUENCING).push_back(e);
                break;
            case 'r':
                practiceLocations.at(REVEALING).push_back(e);
                break;
            case 'g':
                practiceLocations.at(GATHERING).push_back(e);
                break;
            case 'o':
                practiceLocations.at(OPENING).push_back(e);
                break;
        }
    }
    
    diagramsSummary << "\nprimary practice analysis" << endl;
    
    string strPart;
    for (int i =0; i < practiceLocations.size(); i++){
        countPractice[i] = practiceLocations.at(i).length(); //count how many times a practice occured
        countPracticeTotal[i] += countPractice[i]; //record for game-wide report
        diagramsSummary << practiceNames[i] << " @ " << practiceLocations.at(i) << endl;
        
        strPart = analysisPartPractice(practiceLocations[i], vec); //analyze the parts where practices are found
        diagramsSummary <<  "primary part type: " << strPart << endl;
        
        
    }
    
    //use stringBig.find(stringYouWant) ??
    
    return countPractice; //ptr to count array
}

//----------------------
string Stats::analysisPartPractice(string& str, const vector<string>& vecCheck){
    //take string, separate into numbers
    string strCheck;
    
    for (int i = 0; i < str.length(); i++){
        int j = str[i] - '0';
        char c = vecCheck.at(j).front(); //only looking at the primary entry in this cross-check op
        strCheck.push_back(c);
    }
    
    return strCheck;
    
}
//----------------------

int Stats::statBasics (const vector<string>& vec, const vector<string>& vec2){
    //write simple list of all the parts and practices in the scene in the order that the user enters then
    //comma delimted without information about point location (see folder /diagramlabels and find according to image ID)
    
    string tempString;
    
    for (string s : vec){
        if (!s.empty()){
            tempString.append(s);
            tempString.push_back(',');
        }
    }
    diagramsSummary << "\ncomplete parts list for scene (in order, including secondary etc.): " << tempString << endl;
    
    tempString.clear();
    for (string s : vec2){
        if (!s.empty()){
            tempString.append(s);
            tempString.push_back(',');
        }
    }
    
    diagramsSummary << "complete practices list for scene (in order, including secondary etc.): " << tempString << endl;
    
    tempString.clear();
    
    return 0;
}
//----------------------

int Stats::printGameList(const vector<ofPoint>& pts, const vector<string>& vec, const vector<string>& vec2){
    //end of game reporting
    //write additional file with all the information about location, parts, and practices of each point
    diagramsSummary << "game count (primary parts and functions)" << endl;
    for (int i = 0; i < 5; i++){
        diagramsSummary << partNames[i] << " total count: " << countPartTotal[i] << endl;
    }
    diagramsSummary << "\n" <<endl;
    for (int i = 0; i < 5; i++){
        diagramsSummary << practiceNames[i] << " total count: " << countPracticeTotal[i] << endl;
    }
    
    //take the diagramGamePts vec and the totalPart & totalPractice vectors and print as long list
    for (int i = 0; i < pts.size(); i++){
        diagramsSummaryList << pts.at(i).x << ", " << pts.at(i).y << ", " << vec.at(i) << ", " << vec2.at(i) << endl;
    }
    return 0;
}

