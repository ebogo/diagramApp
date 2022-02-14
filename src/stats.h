//esther bogorov

#ifndef stats_h
#define stats_h
#pragma once

#include <stdio.h>
#include "ofMain.h"

//for legibility in vector building
enum {SPACE, THRESHOLD, PATH, EDGE, FOCUS};
enum {NAMING, SEQUENCING, REVEALING, GATHERING, OPENING};


class Stats {
    
public:
    void setupFile(const string& gameName, int imgID, const ofDirectory& dir); //imgID not currently in use
    int printStats(int d, const vector<string>& vec, const vector<string>& vec2);
    int printGameList(const vector<ofPoint>& pts, const vector<string>& vec, const vector<string>& vec2);
    void defineNames();
    
    
private:
    int clearAll();
    int* analysisPart(int d, const vector<string>& vec, const vector<string>& vec2);
    int* analysisPractice(int d, const vector<string>& vec, const vector<string>& vec2);
    string analysisPartPractice(string& str, const vector<string>& vecCheck);
    int statBasics (const vector<string>& vec, const vector<string>& vec2);
    
    int counter;
    
    vector<string> partLocations;
    vector<string> practiceLocations;
    
    string partNames[5];
    string practiceNames[5];
    
    int countPartTotal[5];
    int countPracticeTotal[5];
    
    ofFile diagramsSummary;
    ofFile diagramsSummaryList;
    
};
//static void writeRowHeader(); ??

//notes
//concept : finding more substats, e.g. what percent of thresholds serve as place for gathering? place for sequencing?
//take in both vectors, then when its an s, make a subcount for each different member of practice
//stat: how many times does the part have an additional function? how many times does the part serve more than one narrative function? ie counting if og string > 1

//v2:
//the two analysis functions should abstracted as they write the exact same thing, but stuck with the format of writing strings with the five letters for now. should translate user entries to numbers instead of passing char, etc.
//just that... current strucure makes writing to screen simple



#endif /* stats_h */
