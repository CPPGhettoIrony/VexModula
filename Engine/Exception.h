//
// Created by blenk on 13/08/24.
//

#ifndef NOWHEREFIGHTERS_EXCEPTION_H
#define NOWHEREFIGHTERS_EXCEPTION_H

#include <string.h>
using std::string;

namespace Engine {

    class Exception {
        const string _what;
    public:
        Exception(const string& reason): _what(reason) {}
        const string& what() {return _what;}
    };

} // Engine

#endif //NOWHEREFIGHTERS_EXCEPTION_H
