#include<cstdlib>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<math.h>
#include "Queue.h"


#pragma

using namespace std;

vector<string> selectedWords;
vector<string> magicItems;
int linear_num_comparison = 0;
int binary_num_comparison = 0;
int binary_num_comparison_per_item = 0;
static int LINES_IN_FILE = 666;
static int HASH_TABLE_SIZE = 250;
Queue queue;

int partiton(Queue &item, int low, int high) {
    int pivot = item.Get(high);
    int i = (low - 1);

    for (int j = low; j < high; j++) {

        if (item.Get(j) < pivot) {
            i++;
            item.swap(item.Get(i), item.Get(j));
            //string temp = words[low];
            //words[low] = words[i];
            // words[i] = temp;
        }
    }
    item.swap(item.Get(i+1), item.Get(i));
    return i + 1;
}

int partitonString(vector<string> &item, int low, int high) {
    string pivot = item[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (item[j] < pivot) {
            i++;
            swap(item[i], item[j]);
            //string temp = words[low];
            //words[low] = words[i];
            // words[i] = temp;
        }
    }
    swap(item[i + 1], item[high]);
    return i + 1;
}


void Qsort(Queue &items, int low, int high) {
    if (low < high) {
        int sep = partiton(items, low, high);

        Qsort(items, low, sep - 1);
        Qsort(items, sep + 1, high);
    }
}

void QsortString(vector<string> &items, int low, int high) {
    if (low < high) {
        int sep = partitonString(items, low, high);

        QsortString(items, low, sep - 1);
        QsortString(items, sep + 1, high);
    }
}


void randomWord() {
    srand(time(0));
    for (int i = 0; i < 42; i++) {
        selectedWords.push_back(magicItems.at(rand() % 665));
        //int randIdx = rand() % 665;
        //string randWord = magicItems.at(randIdx);
        // Used these to Test
        // selectedWords.push_back(randWord);
        //cout << "Random word is "  << randWord << endl;
        // cout << "random index "  << randIdx << endl;
    }
}

int linearSearch(vector<string> selectedWords, string key) {
    for (int i = 0; i < selectedWords.size(); i++) {
        linear_num_comparison++;
        if (selectedWords[i] == key) {
            return i;
        }
    }
    return -1;
}

bool binarySearch(vector<string> selectedWords, string item) {
    binary_num_comparison++;
    binary_num_comparison_per_item++;
    if (selectedWords.size() == 0) {
        return false;
    } else {
        int mid = selectedWords.size() / 2;
        if (selectedWords[mid] == item) {
            return true;
        } else {
            if (item < selectedWords[mid]) {
                vector<string>left(selectedWords.begin(), selectedWords.begin() + mid);
                return binarySearch(left, item);
            } else {
                vector<string> right(selectedWords.begin() + mid + 1, selectedWords.end());
                return binarySearch(right, item);
            }
        }
    }
}


// printFile() is dealing with your selectedWords instead of the original list, as per the last projects
void printFile() {
    for (int i = 0; i < selectedWords.size() - 1; i++) {
        cout << selectedWords[i] << "\n";
    }
}

static int makeHashCode(string str) {
    string tmp = str;
    str = "";
    for (int i = 0; i < tmp.size(); i++) {
        str += toupper(tmp[i]);
    }

    int letterTotal = 0;

    // Iterate over all letters in the string, totalling their ASCII values.
    for (int i = 0; i < str.size(); i++) {
        char thisLetter = str[i];
        //cout << "asc" << toascii(thisLetter);
        int thisValue = (int) thisLetter;//fix this line maybe the probelm and use c++17 to comlie it
        letterTotal = letterTotal + thisValue;
    }

    // Scale letterTotal to fit in HASH_TABLE_SIZE.
    int hashCode = (letterTotal * 1) % HASH_TABLE_SIZE;  // % is the "mod" operator
    // TODO: Experiment with letterTotal * 2, 3, 5, 50, etc.
    return hashCode;
}

void analyzeHashValues(Queue hashValues) {
    cout << "Hash Table Usage:";

    // Sort the hash values.
    //Qsort(hashValues, 0, hashValues.size() - 1);  // This is a "dual-pivot" quicksort. was accidenlty sorting the has values
    int asteriskCount = 0;
    int bucketCount[HASH_TABLE_SIZE];
    int totalCount = 0;
    int arrayIndex = 0;

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        //printf("%03d ", i);
        // cout <<endl;
        asteriskCount = 0;
        while ((arrayIndex < LINES_IN_FILE)){ //&& (hashValues.Get(arrayIndex) == i)) {//use the get function  WAS casuing THE PROBELMS
            cout << "*";
            asteriskCount += 1;
            arrayIndex += 1;
        }

        if (asteriskCount != 0) {
            cout << "\n";
            cout << "asteriskCount = " << asteriskCount << endl;
        }
        bucketCount[i] = asteriskCount;
        totalCount = totalCount + asteriskCount;
    }

    cout << "Average load (count): ";
    float averageLoad = (float) totalCount / HASH_TABLE_SIZE;
    printf("%.2f%n", averageLoad);

    cout << "\nAverage load (calc) : ";
    averageLoad = (float) LINES_IN_FILE / HASH_TABLE_SIZE;
    printf("%.2f%n", averageLoad);

    cout << "\nStandard Deviation: ";
    // TODO: Refactor this into its own method.
    double sum = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        // For each value in the array...
        // ... subtract the mean from each one ...
        double result = bucketCount[i] - averageLoad;
        // ... and square the result.
        double square = result * result;
        // Sum all of those squares.
        sum = sum + square;
    }
    // Divide the sum by the number of values ...
    double temp = sum / HASH_TABLE_SIZE;
    // ... and take the square root of that.
    double stdDev = sqrt(temp);
    printf("%.2f%n", stdDev);
    cout << endl;
}

int main() {

    ifstream letterFile;
    string text;

    letterFile.open("magicitems.txt", ios::in);

    if (!letterFile) {
        cout << "\n Error opening file";
        exit(0);
    }

    if (letterFile.is_open()) {
        while (std::getline(letterFile, text)) {
            magicItems.push_back(text);
            // cout << text << "\n";
        }
        letterFile.close();
    }

    cout << "Hash code tests and analysis." << endl;
    cout << "-----------------------------" << endl;

    vector<int> hashValues;
    // Print the array and hash values.
    int hashCode = 0;
    for (int i = 0; i < LINES_IN_FILE; i++) {
        cout << i;
        cout << ". " << magicItems.at(i) << " - ";
        hashCode = makeHashCode(magicItems.at(i));
        printf("%03d%n", hashCode);//use cout instead figure out what wrong. Remeber to compile c++ 17
        cout << endl;
        hashValues.push_back(hashCode);
        queue.enqueue(hashCode);
    }

    // Analyze the distribution of hash values.
    analyzeHashValues(queue);


    randomWord();

    QsortString(magicItems, 0, magicItems.size() - 1);

    for (int i = 0; i < selectedWords.size(); i++) {
        cout << " linear  number of comparisons of item number : " << i + 1 << " is "
             << linearSearch(magicItems, selectedWords[i]) << endl;
        binary_num_comparison_per_item = 0;
        binarySearch(magicItems, selectedWords[i]);
        cout << " binary  number of comparisons of item number : " << i + 1 << " is " << binary_num_comparison_per_item
             << endl;
    }

    cout << " total number of comparisons for linear search is " << linear_num_comparison << endl;
    cout << " total number of comparisons for binary search is " << binary_num_comparison << endl;

    cout << " linear average is " << linear_num_comparison / 42 << endl;
    cout << " binary average is " << binary_num_comparison / 42 << endl;


    //printFile();
    selectedWords.clear();

    // create a random list variable
    // run a loop through the random list, push items selected into random list
    // maybe do a sort again just to be sure it's sorted
    // run your search functions
    // don't mergeSort() words, sort selectedWords
    // this is because once we randomly select our words, we're not touching the original list anymore, plus that one is already sorted
    // you might also need to printFile() in the loops, but we'll see when you test
}
