//
//  main.cpp
//  cal_tp02
//
//  Created by Eduardo Almeida on 11/05/14.
//  Copyright (c) 2014 Bitten Apps. All rights reserved.
//

#include <iostream>
#include <locale>
#include <algorithm>
#include <string>

#include "Dictionary.h"
#include "WordMind.h"
#include "Additions.h"

int main(int argc, const char * argv[]) {
    std::cout << "Welcome to WordMind!" << std::endl << std::endl;
    
    //  auto state = WordMind::generateState("AABERCROMBIE", "ABAARCROBMXX");
    
    Dictionary *dict = nullptr;
    
    try {
        dict = new Dictionary("default.wmdict");
        
        std::cout << "A dictionary with " << dict->getWords().size() << " words was found. Use it? (Y)es/(N)o: ";
        
        while (true) {
            std::string answer;
            
            std::cin >> answer;
            
            std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
            
            if (answer == "y")
                break;
            else if (answer == "n")
                throw answer;
            else
                std::cout << "Invalid choice. Please retry. (Y)es/(N)o: ";
        }
        
    } catch (...) {
        while (true) {
            std::cout << "A dictionary was not found. Path to dictionary: ";
            
            std::string path;
            
            std::cin >> path;
            
            try {
                dict = new Dictionary(path);
                
                break;
            } catch (...) {
                
            }
        }
    }
    
    std::string word;
    
    while (true) {
        std::cout << "Please insert a word for me to guess: ";
        
        std::cin >> word;
        
        if (dict -> containsWord(word))
            break;
        
        std::cout << "I don't know that word! ";
        
        word = "";
    }
    
    WordMind *gameController = new WordMind(dict, word.length());
    
    gameController -> guess();
    
    unsigned int tries = 0;
    
    while (tries++, gameController -> getCurrentWord() != word) {
        std::cout << "Guess Certainty: " << gameController -> getCertainity() * 100.00f << "%." << std::endl;
        
        auto state = WordMind::generateState(word, gameController -> getCurrentWord());
        
        gameController -> setState(state);
        
        try {
            gameController -> guess();
        } catch (WordMindRuntimeFailureException exc) {
            std::cout << "Well, this is embarassing. I wasn't able to guess the word for some reason..." << std::endl;
            
            exit(1);
        } catch (...) {
            std::cout << "An unknown error has occoured..." << std::endl;
            
            exit(2);
        }
        
    }
    
    std::cout << "Found in " << tries << " tries.";
    
    return 0;
}

