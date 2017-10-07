///////////////////////////////////////////////////////////////////////
// File Name:      a2.cpp
//
// Author:         Kevin Mui
// CS email:       mui@cs.wisc.edu
// 
// Description:   Outputs information of two recipe lists as txt files
//                regarding which recipes have in common by taking
//                the union and intersection of the recipe lists.
//
// Sources:       N/A
//
// URL(s) of sources:  N/A         
///////////////////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

/**
 * @brief Reads a file given a name and return every line as a vector pointer
 *
 * @param param_1 The file name to read as a string
 * 
 * @return vector pointer of strings holding each recipe per element
 */
vector<string>* readFile(string filename) {

    // names of recipes
    vector<string>* names;

    // open file and append every recipe name (line) to names vector
    ifstream file(filename);
    if (file.is_open()) {
        names = new vector<string>();
        string line;
        int i = 1;
        while (file.good()) {
            getline(file, line);
            if (line != "")
                names->push_back(line);
        }
        return names;
    }
    else
        cout << "Input file "+filename+" is NOT found. Please try again." << endl;
    
    // return null if file cannot be opened
    return NULL;

}

/**
 * @brief Reads files and outputs out union and intersection information
 * 
 * @return 0 for success else fail
 */
int main() {
    
    // filenames of recipes
    string filename1;
    string filename2;
    // names of recipes
    vector<string>* names1 = NULL;
    vector<string>* names2 = NULL;


    // start by getting filename by input and reading the file
    while (!names1) {
        cout << "Enter the name of the first file: ";
        cin >> filename1;
        names1 = readFile(filename1);
    }

    while (!names2) {
        cout << "Enter the name of the second file: ";
        cin >> filename2;
        names2 = readFile(filename2);
    }

    // compute the union and intersection of the recipe files
    vector<string> union_vector;
    vector<string> intersection_vector;

    sort(names1->begin(), names1->end());
    sort(names2->begin(), names2->end());

    set_union (names1->begin(), names1->end(), names2->begin(), 
        names2->end(), back_inserter(union_vector));

    set_intersection (names1->begin(), names1->end(), names2->begin(), 
        names2->end(), back_inserter(intersection_vector));


    // print information based on union and intersection of recipe files
    cout << endl;
    cout << "Number of recipes in "+filename1+" = " << names1->size() << endl;
    cout << "Number of recipes in "+filename2+" = " << names2->size() << endl;
    cout << "Number of recipes that are present in BOTH "+filename1+" AND "+filename2+" = " << intersection_vector.size() << endl;
    cout << "Number of recipes that are in EITHER "+filename1+" OR "+filename2+" = " << union_vector.size() << endl;
    cout << endl;
    
    if (intersection_vector.size() > 0) {
        cout << "List of recipes that are present in BOTH "+filename1+" AND "+filename2+":" << endl;

        for (string& name : intersection_vector)
            cout << name << endl;
        cout << endl;
    }

    // output recipe names intersection and union to respective files
    ofstream intersectionFile("intersection.txt");
    if (intersectionFile.is_open()) {
        for (string& name : intersection_vector)
            intersectionFile << name << endl;
        cout << "The set intersection of the two files was written to a file named intersection.txt" << endl;
    }
    else
        cout << "Error: Cannot write to intersection.txt." << endl;
    
    ofstream unionFile("union.txt");
    if (unionFile.is_open()) {
        for (string& name : union_vector)
            unionFile << name << endl;
        cout << "The set union of the two files was written to a file named union.txt" << endl;
    }
    else
        cout << "Error: Cannot write to union.txt." << endl;
    
    return 0;
}


