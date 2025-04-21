#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(string curr, int index, string floatingStr, const set<string>& myWords, set<string>& myFinds);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> myFinds;
    wordleHelper(in,0,floating,dict, myFinds);
    return myFinds;

}

// Define any helper functions here
void wordleHelper(string curr, int index, string floatingStr, const set<string>& myWords, set<string>& myFinds) {
    //unsigned int myInt = (unsigned int)index;
    // base case word is full
    if ((unsigned int)index == curr.size()) {
        string myTemp = curr;
        // check for all floating letters
        for (unsigned int i = 0; i < floatingStr.size(); i++) {
            size_t loco = myTemp.find(floatingStr[i]);
            if (loco==string::npos) {
                return; // reached end of str
            }
            // remove used character
            myTemp.erase(loco,1);
        }
        // add word to results if in dictionary
        if (myWords.find(curr) != myWords.end()) {
            myFinds.insert(curr); 
        }
        return;
    }

    //if known char
    if (!(curr[index]=='-')) {
        // recursive step
        wordleHelper(curr,index+1,floatingStr,myWords,myFinds);

    }
    else {
        // non base case
        int dash = 0;
        for (unsigned int i = (unsigned int )index; i<curr.size();++i) {
          if (curr[i]=='-') {
            dash++; // iterate the dashes 
          }
        }
        // not enough dashes, need to backtrack
        if ((int)floatingStr.size()>dash) {return;}
        // dashes=floating chars
        if ((int)floatingStr.size()==dash) {
          for (unsigned int i=0; i<floatingStr.size();++i) {
            char c=floatingStr[i];
            curr[index]=c; // use floating char
            string newF=floatingStr;
            newF.erase(i,1);  // remove used char 
            wordleHelper(curr,index+1,newF,myWords,myFinds);
          }
        }
        else {
          // loop thru the alphabet
          for (char c='a';c<='z';++c) {
            curr[index]=c;
            string newF=floatingStr;
            size_t loc=newF.find(c);
            // if in floating, remove letter
            if (loc!=string::npos) {
              newF.erase(loc,1);
            }
            // recursion
            wordleHelper(curr,index+1,newF,myWords,myFinds);
          }
        }
        
    }
}
