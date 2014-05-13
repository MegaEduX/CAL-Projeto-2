//
//  Dictionary.cpp
//  cal_tp02
//
//  Created by Eduardo Almeida on 13/05/14.
//  Copyright (c) 2014 Bitten Apps. All rights reserved.
//

#include "Dictionary.h"

#include "Additions.h"

Dictionary::Dictionary(std::string path) {
    _dict = Additions::explode("\n", Additions::get_file_contents(path.c_str()));
}

std::vector<std::string> Dictionary::getWords(int length) {
    if (!length)
        return _dict;
    
    std::vector<std::string> returnVector;
    
    for (auto word : _dict)
        if (word.length() == length)
            returnVector.push_back(word);
    
    return returnVector;
}

bool Dictionary::containsWord(std::string word) {
    for (auto w : _dict)
        if (w == word)
            return true;
    
    return false;
}
