#include<cstdlib>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#pragma

using namespace std;

vector<string> words;
int num_comparison = 0; // increment comparsion


int compare_String(string a,string b){
  int i = 0;

    while(true){
        if(a.length() <= i && b.length() <= i )
            return 0;
        if(a.length() <= i ){
            return -1;
        }
        if(b.length() <= i ){
            return 1;
        }
       if(toupper(a[i]) < toupper(b[i]) ){
           return -1;
       }
      else if (toupper(a[i]) >  toupper(b[i])){
          return 1;
      }
      i++;
    }
}
void sSort() {
    int i, j, imin;

    for (i = 0; i < words.size() - 1; i++) {
        imin = i; //index of minium data
        for (j = i + 1; j < words.size(); j++) {
            if (j >= 0 && compare_String(words[imin],words[j]) > 0) {
                imin = j;
            }
            num_comparison++;
        }
        swap(words[i], words[imin]);
    }
    cout<<"-----------------------------"<<"\n"<< "Selection sort number of comparisons is " <<num_comparison<<"\n";
}

void InSort(){
    //i selected element
    //j insert element
    int i,j;
    string key;
    for(i = 0; i < words.size(); i++){
         key = words[i];
            j = i -1;
        while(j >= 0 && compare_String(words[j],key) > 0){
            words[j+1] = words[j];
            --j;
            num_comparison++;
        }
        words[j+1] = key;
        num_comparison++;
    }
   cout <<"-----------------------------"<<"\n"<< "Insertion sort number of comparisons is " <<num_comparison<<"\n";
}
void Merge(vector<string>&mitems, int p,int q,int r){
  int n1 = q - p + 1;
  int n2 = r - q;

  vector<string> leftVector;
  vector<string> rightVector;

  leftVector.resize(n1 + 1);
  rightVector.resize(n2 + 1);

  for(int i = 0; i < n1; i++){
      leftVector.at(i) = mitems.at(p + i);
      //try just p + i if it doesnt work
    }
  for(int j = 0; j < n2; j++){
       rightVector.at(j) = mitems.at(q+j+1);
       //q + 1 + j
    }
  int i,j,k;
  i = 0;
  j = 0;
  k = p;

  while(i < n1 && j < n2){
      if(compare_String(leftVector.at(i),rightVector.at(j)) < 0) {
          words[k] = leftVector.at(i);
          i++;
      }else{
          words[k] = rightVector.at(j);
          j++;
      }
      k++;
      num_comparison++;
  }

  while(i < n1){
      words[k] = leftVector[i];
      i++;
      k++;
  }
    while(j < n2){
        words[k] = rightVector[j];
        j++;
        k++;
    }
}

void Msort(vector<string>&mitems, int leftVect, int rightVect){
    if(leftVect < rightVect){
        int m = leftVect + (rightVect - leftVect) / 2;
        Msort(words,leftVect,m);
        Msort(words,m + 1, rightVect);
        Merge(words,leftVect,m,rightVect);
    }
}

int partiton(vector<string>&item, int low,int high){
    string pivot = words[high];
    int i = (low - 1);

    for(int j = low; j < high; j++){
        if(compare_String(words[j],pivot) < 0){
            i++;
           swap(words[i],words[j]);
            //string temp = words[low];
           //words[low] = words[i];
          // words[i] = temp;
        }
        num_comparison++;
    }
    swap(words[i + 1], words[high]);
    return i + 1;
}

void Qsort(vector<string>&items,int low, int high){
    if(low < high){
        int sep = partiton(words,low,high);

        Qsort(words,low,sep -  1);
        Qsort(words,sep + 1, high);
    }
}

void openFile(){
    ifstream letterFile;
    string text;

    letterFile.open("magicitems.txt", ios::in);

    if (!letterFile) {
        cout << "\n Error opening file";
        exit(0);
    }

    if (letterFile.is_open()) {
        while (std::getline(letterFile, text)) {
            words.push_back(text);
            // cout << text << "\n";
        }
        letterFile.close();
    }
}

void printFile(){
    for (int i = 0; i < words.size()-1; i++) {
        cout<<words[i]<<"\n";
    }
}

    int main(int argc, char **argv) {

    openFile();
    sSort();
  printFile();
   words.clear();
   num_comparison = 0;

    openFile();
    InSort();
   printFile();
    words.clear();
    num_comparison = 0;

    openFile();
    Qsort(words,0,words.size());
    cout <<"-----------------------------"<<"\n"<< "Quick sort number of comparisons is " <<num_comparison<<"\n";
    printFile();
    words.clear();
    num_comparison = 0;

    openFile();
    Msort(words, 0, words.size() - 1);
    cout <<"-----------------------------"<<"\n"<< "Merge sort number of comparisons is " << num_comparison << "\n";
    printFile();
    words.clear();
    num_comparison = 0;





    }
