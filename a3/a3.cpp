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
    // TODO: Implement this function.
    // Remember to call the helper functions below!
    std::vector<std::string> tokens;
    std::string line;
    while (inFile.good()) {
        getline(inFile, line);
        tokens.push_back(line);
    }
    removeCommonWords(tokens, commonWords);
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        // std::cout << "checking if empty: " << *it << std::endl;
        if (!it->empty()) {
            // std::cout << "not empty: " << *it << std::endl;
            // std::cout << "sent to clean file:" << *it << std::endl;
            outFile << *it << std::endl;
        }
    }
    
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
    // TODO: Implement this function.
    // std::cout << "entered filldictionary" << std::endl;
    std::string line;
    while (newInFile.good()) {
        // std::cout<<"next line in file" <<std::endl;
        getline(newInFile, line);
        // std::cout<<"geline in file"<<std::endl;
        std::vector<std::string> words;
        splitLine(line, words);
        // std::cout<<"splitline success"<<std::endl;
        
        for (auto it = words.begin(); it != words.end(); ++it) {
            // std::cout << "word: " << *it << std::endl;
            if (!it->empty()) {
                if (dict.find(*it) != dict.end()) {
                    // std::cout << "make pair" << std::endl;
                    dict[*it] = std::make_pair(std::stol(*(words.begin())),1.0);
                }
                else {
                    // std::cout << "first = " << *(words.begin()) << std::endl;
                    long first = dict[*it].first+std::stol(*(words.begin())); // add current and rating
                    long second = dict[*it].second+1.0;   // increment number of this rating
                    // std::cout << "first = " << first << " second = " << second << std::endl;
                    dict[*it] = std::make_pair(first,second);
                }
            }
            else {
                // std::cout<<"this is empyt"<<std::endl;
            }
        }
        // std::cout <<"pass" <<std::endl;
    }
    for (auto it = dict.begin(); it != dict.end(); ++it) {
        std::cout << it->first << " => " << it->second.first << " , " << it->second.second << std::endl;
    }
    std::cout << std::endl;
    // std::cout<<"exit filldict" << std::endl;
}

/**
 * @brief Read the common words from a file and store them in a set.
 *
 * @param inFile The file with the common words.
 * @param commonwords The set to store the common words.
 */
void fillCommonWords(std::istream &inFile,
                   std::unordered_set<std::string> &commonWords) {
    // TODO: Implement this function.
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
    std::vector <long> ratings;
    while (testFile.good()) {
        getline(testFile, line);
        std::vector<std::string> words;
        splitLine(line, words);
        // std::cout << "checking if empty: " << line << std::endl;
        if (!line.empty()) {
            // std::cout << "not empty: " << line << std::endl;
            // std::cout << "from line" << std::endl;
            long numWords = words.size();
            long totalRatings = 0;
            for (auto it = words.begin(); it != words.end(); ++it) {
                // std::cout<<"loop start"<<std::endl;
                if (dict.find(*it) != dict.end()) {
                    // std::cout<<"loop check"<<std::endl;
                    // std::cout <<"first = " << dict[*it].first << " second = " << dict[*it].second << std::endl;
                    totalRatings += dict[*it].first/dict[*it].second;
                    // std::cout<< "total ratiings = " << totalRatings << std::endl;
                }
                // std::cout<<"loop end"<<std::endl;
            }
            // std::cout<<"calculate attempt" <<std::endl;
            // std::cout << "totalRatings = " << totalRatings << " numWords = " << numWords << std::endl;
            
            long finalRating = totalRatings / numWords;
            // std::cout<<"calculate success" <<std::endl;
            
            ratings.push_back(finalRating);
        }

    }
    for (auto it = ratings.begin(); it != ratings.end(); ++it) {
        ratingsFile << *it << std::endl;
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
    // TODO: Implement this function.
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        std::vector<std::string> words;
        splitLine(*it, words);
        std::string line = "";
        // std::cout << "line: " << *it << std::endl;
        for (auto wit = words.begin(); wit != words.end(); ++wit) {
            if (commonWords.find(*wit) == commonWords.end()) {
                // std::cout << *wit << std::endl;
                // words.erase(std::remove(tokens.begin(), tokens.end(), *wit), tokens.end());
                line += *wit + ' ';
            }
        }

        // std::cout << "cleaned line: " << line << std::endl;
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
