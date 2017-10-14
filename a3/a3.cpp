////////////////////////////////////////////////////////////////////////////////
// File Name:      a3.cpp
//
// Author:         Gerald, Isaac, Varun
// CS email:       gerald@cs.wisc.edu
//                 cisung@wisc.edu
//                 vnaik@cs.wisc.edu
//
// Description:    The source file for a3.
//
// IMPORTANT NOTE: THIS IS THE ONLY FILE THAT YOU SHOULD MODIFY FOR A3.
//                 You SHOULD NOT MODIFY any of the following:
//                   1. Name of the functions.
//                   2. The number and type of parameters of the functions.
//                   3. Return type of the functions.
//                   4. Import statements.
//
// Sources:        <Sources, if any>
//
// URL(s) of sources:
//                 <URLs of your sources, if any>
////////////////////////////////////////////////////////////////////////////////

#include "a3.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * @brief Cleans the review data by removing common words.
 *
 * @param inFile The input file with the raw review data.
 * @param outFile The output file where the clean review data is written.
 * @param commonwords A set of common words to be removed from the raw review data.
 */
void cleanData(std::istream &inFile, std::ostream &outFile,
               std::unordered_set<std::string> &commonWords) {
    std::vector<std::string> tokens;
    std::string line;
    while (inFile.good()) {
        getline(inFile, line);
        tokens.push_back(line);
    }
    removeCommonWords(tokens, commonWords);
    for (auto it = tokens.begin(); it != tokens.end(); ++it)
        if (!it->empty())
            outFile << *it << std::endl;
    
}

/**
 * @brief Reads the reviews and ratings from the file and creates a map from
 *        each word to a pair consisting of the total rating for this word and
 *        the total number of times this word has occurred in the reviews.
 *
 * @param file The file with the review data.
 * @param dict The map/dictionary that we are creating
 *             for each word in the review.
 */
void fillDictionary(std::istream &newInFile,
                    std::unordered_map<std::string, std::pair<long, long>> &dict) {
    std::string line;
    while (newInFile.good()) {
        getline(newInFile, line);
        std::vector<std::string> words;
        splitLine(line, words);
        
        for (auto it = words.begin(); it != words.end(); ++it) {
            if (!it->empty() && it->compare(*words.begin()) != 0) {
                if (dict.find(*it) == dict.end()) {
                    dict[*it] = std::make_pair(std::stol(*(words.begin())),1.0);
                }
                else {
                    long first = dict[*it].first+std::stol(*(words.begin())); // add current and rating
                    long second = dict[*it].second+1.0;   // increment number of this rating
                    dict[*it] = std::make_pair(first,second);
                }
            }
        }
    }
    for (auto it = dict.begin(); it != dict.end(); ++it) {
        std::cout <<  << std::fixed << std::setprecision(2) << it->first << " => " << it->second.first << " , " << it->second.second << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief Read the common words from a file and store them in a set.
 *
 * @param inFile The file with the common words.
 * @param commonwords The set to store the common words.
 */
void fillCommonWords(std::istream &inFile,
                   std::unordered_set<std::string> &commonWords) {
    std::string line;
    while (inFile.good()) {
        getline(inFile, line);
        commonWords.insert(line);
    }
}

/**
 * @brief Read the reviews from a file and give a rating for each review.
 *
 * @param testFile The input file that contains the reviews to be rated.
 * @param dict The map/dictionary that we use to rate the reviews.
 * @param ratingsFile The output file into which we write our ratings
 *                    for each review.
 */
void rateReviews(std::istream &testFile,
                 std::unordered_map<std::string, std::pair<long, long>> &dict,
                 std::ostream &ratingsFile) {
    // TODO: Implement this function.
    std::string line;
    std::vector <double> ratings;
    while (testFile.good()) {
        getline(testFile, line);
        std::vector<std::string> words;
        splitLine(line, words);
        if (!line.empty()) {
            double numWords = words.size();
            double totalRatings = 0.0;
            for (auto it = words.begin(); it != words.end(); ++it) {
                if (dict.find(*it) != dict.end()) {
                    double first = dict[*it].first;
                    double second = dict[*it].second;
                    totalRatings += first/second;
                    std::cout<< "total ratiings = " << totalRatings << std::endl;
                }
                else {                    
                    totalRatings += 2;
                }
            }
            
            double finalRating = totalRatings / numWords;
            
            ratings.push_back(finalRating);
        }

    }
    for (auto it = ratings.begin(); it != ratings.end(); ++it) {
        ratingsFile << std::fixed << std::setprecision(2) << *it << std::endl;
    }
}

/**
 * @brief Removes the common words from a vector of strings.
 *
 * @param tokens The vector of strings which may contain common words.
 * @param commonwords The set of common words that'll be removed from the vector.
 */
void removeCommonWords(std::vector<std::string> &tokens,
                     std::unordered_set<std::string> &commonWords) {
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        std::vector<std::string> words;
        splitLine(*it, words);
        std::string line = "";
        for (auto wit = words.begin(); wit != words.end(); ++wit) {
            if (commonWords.find(*wit) == commonWords.end()) {
                line += *wit + ' ';
            }
        }
        *it = line;
    }
}

/**
 * @brief Splits a line of text into a vector of strings
 *        using the whitespace as the delimiter.
 *
 * @param line The input line of text to be split into multiple words.
 * @param tokens The vector which holds the strings after the line is split.
 */
void splitLine(std::string &line, std::vector<std::string> &words) {
    // This code is provided for you and is correct.
    // You should NOT make any changes to this function!
    std::stringstream ss;
    ss.str(line);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        if (token.length() != 0) {
            words.push_back(token);
        }
    }
}
