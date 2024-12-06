#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <queue>
#include <iomanip>
#include <algorithm>



using namespace std;



using WORD = string;
using WORD_LIST = set<WORD>;
using CHAR_FREQ_LIST = map<char, int>;
using WORD_FREQ_LIST = multimap<int, WORD>;
using COUNTER = tuple<int, int, int>; // first = #letters, second = #words, third = #lines
using LONGEST = priority_queue<WORD>;


struct DICTIONARY {
    COUNTER stats {0,0,0};
    WORD_LIST words;
    CHAR_FREQ_LIST charFreq;
    WORD_FREQ_LIST wordFreq;
    LONGEST longWord;
};


WORD getNextWord(DICTIONARY &dic);
void printStats(DICTIONARY &dic);
void printWordFreq(DICTIONARY &d);
void printCharFreq(DICTIONARY &d);
void letterFreqHisto(DICTIONARY &d);
void wordFreqHisto(DICTIONARY &d);
void wordFreqTable(DICTIONARY &d);
string getLongWord(DICTIONARY d);



string getLongWord(DICTIONARY d) {

    string longest;
    while (!d.longWord.empty()) {
        string current = d.longWord.top();
        d.longWord.pop();
        if (current.size() > longest.size()) {
            longest = current;
        }
    }

    return longest;

}


void wordFreqTable(DICTIONARY &dic) {

    int longSize;

    if (!dic.longWord.empty()) {
        longSize = dic.longWord.top().size();
    } else {
        cout << "Queue is empty." << endl;
    }

    cout << "Word";

    for (int i = 0; i < longSize * 3 - 4; i++) {
        cout << " ";
    }

    cout << "Frequency" << endl;
    
    for (int i = 0; i < (longSize * 3) + 9; i++) {
        cout << "_";
    }

    auto it = dic.wordFreq.begin();
    cout << endl;
    for (int i = 0; i < dic.wordFreq.size(); i++) {
        cout << setw(24) << left << it->second;
        cout << setw(5) <<  left << it->first;
        cout << endl;
        it++;
    }

}



void wordFreqHisto(DICTIONARY &d) {

    cout << "/---------------------\\" << endl;
    cout << "    Word Frequency" << endl;
    cout << "\\---------------------/" << endl << endl;

    int length = d.wordFreq.size(); // gives filler length of space
    int longLength = getLongWord(d).size();  // length of longest word
    int startArrow = longLength + length;      // starting point of first point 


    for (int i = 10; i >= 1; i--) {
        auto it = d.wordFreq.begin();
        cout << setw(startArrow) << right;
        for (int k = 0; k < d.wordFreq.size(); k++) {
            if (it->first >= i) {
                cout << "* ";
            } else {
                cout << "  ";
            }
            it++;
        }
        cout << endl;
    }


    // prints the line of x-axis of histogram
    for (int i = 0; i < (startArrow + (2 * d.wordFreq.size())); i++) {
        cout << "_";
    }
    cout << endl;
    
    cout << setw(startArrow) << right;
    // prints the arrows corresponding to each bar on histogram
    for (int i = 0; i < d.wordFreq.size(); i++)
        cout << "^ " ;
    cout << endl;

    // display word names plus the lines that increase with each iteration
    // 
    string slash = "/ ";
    string vertical = "| ";
    string histoLine = "";
    // creates strings of lines for histogram visual
    // add "--" for each iteration of word display
    for (int i = 0; i < length - 2; i++) {
        histoLine += "-";
    }

    auto it = d.wordFreq.begin();
    for (int i = 0; i < d.wordFreq.size(); i++) {

        int remainingWords = d.wordFreq.size() - i - 1;

        int lenCurrentWord = it->second.size();
        int diffWhiteSpace = longLength - lenCurrentWord;

        // display word
        cout << it->second;
        // display remaining whitespace to add after word
        for (int i = 0; i < diffWhiteSpace; i++)
            cout << " ";

        cout << histoLine;

        // add extra hyphens depending on how far down list we are
        for (int k = 0; k < i; k++)
            cout << "--";
        
        cout << slash;

        for (int k = 0; k < remainingWords; k++) {
            cout << vertical;
        }

        cout << endl;
        it++;


    }


}


void letterFreqHisto(DICTIONARY &d) {

    cout << "/---------------------\\" << endl;
    cout << "    Letter Frequency" << endl;
    cout << "\\---------------------/" << endl;
    auto it  = d.charFreq.begin();
    int size = d.charFreq.size();

    for (int i = 0; i < size; i++) {
        cout << it->first << " |";
        int charCount = it->second;
        if (charCount <= 10) {
            for (int k = 0; k < charCount; k++) {
                cout << "*";
            }
            cout << endl;
        } else {
            cout << "********** " << "(" << charCount << ")";
            cout << endl;
        } 
        it++;
    }

}




void printStats(DICTIONARY &dic) {
    cout << endl;
    cout << "# Letters   : " << get<0>(dic.stats) << endl;
    cout << "# Words     : " << get<1>(dic.stats) << endl;
    cout << "# Lines     : " << get<2>(dic.stats) << endl;
}



WORD getNextWord(DICTIONARY &dic, ifstream &file) {
    WORD w;  
    char ch;
    bool inWord = false;  

    while (file.get(ch)) {
        if (isalpha(ch)) {
            if (dic.charFreq.find(ch) != dic.charFreq.end())
                dic.charFreq[ch] += 1;
            else
                dic.charFreq.insert({ch, 1});
                
            get<0>(dic.stats) += 1;
            w.push_back(ch);  
            inWord = true;
        }
        else if (inWord) { 
            if (get<2>(dic.stats) == 0)
                get<2>(dic.stats) += 1;
            if (ch == '\n' || ch == '\r')
                get<2>(dic.stats) += 1;
            return w;  
        }
    }

    return w;  

}


void updateWordFrequency(DICTIONARY  &d, WORD w) {
    int num;
    int size = d.wordFreq.size();
    auto it = d.wordFreq.begin();
    for (int i = 0 ; i < size; i++ ) {
        if (it->second == w) {
            num = it->first;
            num++;
            d.wordFreq.erase(it);
            d.wordFreq.insert({num, w});
            return;
        }
        it++;
    }
    // insert new pair if no word found
    d.wordFreq.insert({1, w});
}


void printWordFreq(DICTIONARY &d) {
    cout << endl << "Word Frequency List:" << endl;
    auto it = d.wordFreq.begin();
    int size = d.wordFreq.size();
    for (int i = 0; i < size; i++) {
        cout<< setw(5) << left << it->first;
        cout << setw(20) << left << it->second << endl;
        it++;
    }
    cout << endl;
}


void printCharFreq(DICTIONARY &d) {
    cout << endl << "Char Frequency List: " << endl;
    auto it = d.charFreq.begin();
    int size = d.charFreq.size();
    for (int i = 0; i < size; i++) {
        cout << setw(5) << left << it->second;
        cout << setw(2) << left << it->first << endl;
        it++;
    }
    cout << endl;
}


int main(int argc, char* argv[]) {

    string fileName;

    if (argc < 2) {
        cout << "No arguments passed" << endl;
        return 1;
    }

    fileName = string(argv[1]);

    ifstream file (fileName);

    DICTIONARY dic;


    if (!file.is_open()) {
        cerr << "Unable to open file." << endl;
        return 1;
    } else
        cout << "File opened." << endl;

    get<2>(dic.stats) += 1;
    cout << endl;

    WORD w;
    while (true) {
        w = getNextWord(dic, file); 

        if (w.empty()) break;  

        updateWordFrequency(dic, w);
        dic.longWord.push(w);
        get<1>(dic.stats) += 1;
        dic.words.insert(w);
    }

    for (auto word : dic.words) {
        cout << word << ", ";
    }

    printStats(dic);

    cout << endl << "Longest Word: " << getLongWord(dic) << endl;

    printCharFreq(dic);

    printWordFreq(dic);

    cout << endl;

    letterFreqHisto(dic);

    cout << endl;

    wordFreqTable(dic);

    cout << endl;

    wordFreqHisto(dic);

    cout << endl;

    file.close();  // Close the file
    
    return 0;

}


