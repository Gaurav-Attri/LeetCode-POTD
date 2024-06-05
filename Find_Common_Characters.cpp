#include<bits/stdc++.h>
using namespace std;
/*
Appraoch 1 : My Approach
*/

vector<string> commonChars1(vector<string>& words) {
    vector<string> answer;
    unordered_map<string, int> commonCharMap;

    // Putting the frequency of the characters of the first word in the commonCharMap map.
    for(int i = 0; i < words[0].length(); i++){
        string s(1, words[0][i]);
        commonCharMap[s]++;
    }

    for(int i = 1; i < words.size(); i++){
        // Creating a temporary map which will contain the frequency of the characters of the ith word
        unordered_map<string, int> tempMap;
        for(int j = 0; j < words[i].length(); j++){
            string s(1, words[i][j]);
            tempMap[s]++;
        }

        // Finding the common characters and updating the frequency to be least
        for(auto tempIt : tempMap){
            auto commonIt = commonCharMap.find(tempIt.first);
            if(commonIt != commonCharMap.end()){
                commonIt->second = commonIt->second < tempIt.second ? commonIt->second : tempIt.second;
            } 
        }

        // Removing all the characters from commonCharMap which are not present in the tempMap;
        vector<string> keysToRemove;
        for(auto commonIt : commonCharMap){
            auto tempIt = tempMap.find(commonIt.first);
            if(tempIt == tempMap.end()) keysToRemove.push_back(commonIt.first);
        }

        for(string s : keysToRemove) commonCharMap.erase(s);
    }

    // Now the commonCharMap contains all the characters which are common including their frequency.
    for(auto it : commonCharMap){
        // Putting a character in the answer array the number of times it's common in all the words.
        for(int i = 0; i < it.second; i++){
            answer.push_back(it.first);
        }
    }

    return answer;
}

/*
Approach 2 : Learned from the Editorial
*/

vector<string> commonChars2(vector<string>& words) {
    vector<string> answer;
    int commonCharCount[26];
    int currentCharCount[26];

    // Keeping the track of the frequency of each character of the first word.
    for(char c : words[0]){
        commonCharCount[c-'a']++;
    }

    for(int i = 1; i < words.size(); i++){
        fill(currentCharCount, currentCharCount+26, 0);

        // Keeping track of the frequency of each character of the ith word.
        for(char c : words[i]){
            currentCharCount[c-'a']++;
        }

        // Updating the frequency of each character in the commonCharCount array to be the least.
        for(int i = 0; i < 26; i++){
            commonCharCount[i] = min(commonCharCount[i], currentCharCount[i]);
        }
    }

    for(int i = 0; i < 26; i++){
        for(int j = 0; j < commonCharCount[i]; j++){
            string s(1, ('a' + i));
            answer.push_back(s);
        }
    }

    return answer;
}

int main(){
    vector<string> test = {"bella", "label", "roller"};
    vector<string > commonChars1Ans = commonChars1(test);
    vector<string> commonChars2Ans = commonChars2(test);

    cout << "commonChars1Ans: ";
    for(int i = 0; i < commonChars1Ans.size(); i++) cout << commonChars1Ans[i] << " ";
    cout << "\ncommonChars2Ans: ";
    for(int i = 0; i < commonChars2Ans.size(); i++) cout << commonChars2Ans[i] << " "; 
}
