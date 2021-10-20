#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>



using namespace std;

// Count how many people are infected in a group
int groupInfected(vector<bool>&groupSize){
    int infected = 0;
    for (int i = 0; i < groupSize.size(); i++){
        if(groupSize[i] == true){
            infected++;
        }
    }
    return infected;
}

// Simulate number of tests required per groups of people
void simulation(vector<bool>&groupSize, int size){
    vector<vector<bool>> groups;
    int numGroups = groupSize.size() / size;

    // create the groups from our size
    for(int i = 0; i < groupSize.size(); i += size) {
        vector<bool>::const_iterator begin = groupSize.begin() + i;
        vector<bool>::const_iterator end = groupSize.begin() + i + size - 1;
        groups.push_back(vector<bool>(begin, end));
    }

    int numTests[3] = {0};
    float cases[3] = {0};

    // Do the simulation
    for(int i = 0; i < numGroups; i++) {
        vector<bool> group = groups[i];
        int numGroupInfected = groupInfected(group);
        if(numGroupInfected > 0)  {

            int caseNum = 2;
            if(numGroupInfected == 1) {
                caseNum = 1;
            }

            cases[caseNum]++;
            numTests[caseNum]++;

            // Separate in two groups
            // group 1
            vector<bool>::const_iterator begin = group.begin();
            vector<bool>::const_iterator end = group.begin() +  size / 2 - 1; // thisread the begging and end of the vectors
            vector<bool> group1 = vector<bool>(begin, end);

            // group 2
            begin = group.begin() + size / 2;
            end = group.end();
            vector<bool> group2 = vector<bool>(begin, end);

            // Check if any of the groups is infected
            bool isGroup1Infected = groupInfected(group1);
            bool isGroup2Infected = groupInfected(group2);
            numTests[caseNum] += 2;// one test for each group

            // calulate the number of tests based on infection results by group
            if((isGroup1Infected && !isGroup2Infected) || (!isGroup1Infected && isGroup2Infected)) {
                numTests[caseNum] += size / 2;
            }
            else {
                numTests[caseNum] += size;
            }
        }
        else {
            cases[0]++;
            numTests[0]++;
        }
    }

    // Print results
    for(int i = 0; i < 3; i++) {
        float caseProb = cases[i] / numGroups;
        cout << "Case (" << (i + 1) << "): " << numGroups << " x " << caseProb << " = " << (numGroups * caseProb) << " instances requiring " << numTests[i] << " tests" << endl;
    }
    cout << numTests[0] + numTests[1] + numTests[2] << " " << "of Test Required" << " "  << " " << "to screen a population of" << " " << groupSize.size();
};



int main() {
    float infectionRate = 0.02;
    double testAccuracy = 100;
    int input;
    //vector<int> groupSize = {4,8,16,32,64};
    cout << "Enter Number For Sim ";
    for(int i = 0; i < 1; i++){
        cin >> input;
    }


    /*for (int i = 0; i < infectedG; i++){
        cout << groupSize[i]; //Shows that some have been infected and such
    }*/

    vector<bool>groupSize (input,false);
    int infectedG = groupSize.size();

    cout << "Tested Group "<<endl;
    srand(time(0));

    for (int i = 0; i < infectedG * infectionRate; i++){
        groupSize[rand() % input] = true;
        //cout << groupSize[i];
    }


    simulation(groupSize, 8);

    return 0;
}
