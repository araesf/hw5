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
void wordle_helper(std::string& inlol, std::string floating, const std::set<std::string>& dict, int i, set<string>& valid_set);
// bool floating_included(std::string& inlol, const std::string& floating);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
		std::set<string> valid_set;
		std::string inlol = in;
        std::string floatin = floating;

    // Add your code here
    wordle_helper(inlol, floatin, dict, 0, valid_set);
    return valid_set;

}

// Define any helper functions here
void wordle_helper(std::string& inlol, std::string floating, const std::set<std::string>& dict, int i, std::set<string>& valid_set) {
    // base case. if correct size, valid english word, and all floating chars are included
    if (inlol.size() == i && dict.find(inlol) != dict.end() && floating.empty()) {
        valid_set.insert(inlol);
		return;
    }

    // to prune, you have to shrink the floating string when the character is used
    int rem_hyphens = 0;
    for (int h = i; h < inlol.size(); h++) {
        if (inlol[h] == '-') {
            rem_hyphens += 1;
        }
    }

	if (i >= inlol.size()) {
		return;
	}

    // if there are not enough spaces for the floating characters, it is invalid
    if (rem_hyphens < floating.size()) {
        return;
    }

    // if inlol is a given character, we must still shrink the floating string to account for this character if it is in the string
    // do not need to make copy as this is part of the inital in string and will apply to all recursive calls
	if (inlol[i] != '-') {
        if (floating.find(inlol[i]) != std::string::npos) {
            floating.erase(floating.find(inlol[i]), 1);
        }

		wordle_helper(inlol, floating, dict, i + 1, valid_set);
		return;
	} 

    // test every character at the position
    for (char c = 'a'; c <= 'z'; c++) {
        inlol[i] = c;

        std::string floating_copy = floating;
        
        if (floating_copy.find(c) != std::string::npos) {
            floating_copy.erase(floating_copy.find(c), 1);
        }

    	// recurse onwords (skip character)
		wordle_helper(inlol, floating_copy, dict, i + 1, valid_set);

        // reverse the change
	    inlol[i] = '-';
	}
}

// discarding due to runtime constraints:
// bool floating_included(std::string& inlol, const std::string& floating) {
//     std::map<char, int> f_count;
//     std::map<char, int> in_count;

//     // check for same frequency of characters in both in and the floating 
//     // (if floating is aa, then we need 2 a's. inlol must have a count have 2 a's at the key 'a')

//     for (char c : floating) {
//         f_count[c] += 1;
//     }

//     for (char i : inlol) {
//         in_count[i] += 1;
//     }

//     // now iterate over the f_count and if key in in_count has a count that is less that f_count, then return false
//     for (const std::pair<char, int>& m : f_count) {
//         if (in_count[m.first] < m.second) {
//             return false;
//         }
//     }

//     return true;
// }
