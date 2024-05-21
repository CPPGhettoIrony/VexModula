//#include <iostream>
//using std::cout, std::endl;
// Created by blenk on 25/02/24.
//

#ifndef NOWHEREFIGHTERS_ANIMATEDSET_H
#define NOWHEREFIGHTERS_ANIMATEDSET_H

#include <unordered_map>
#include <string>
#include <vector>

using std::unordered_map, std::vector, std::make_pair, std::string;

namespace Engine {

    template <class frameList,typename frameType>
    class AnimatedSet {
    public:
        typedef unordered_map<string, frameList> Map;
    protected:
        Map frameMap;
    public:
        AnimatedSet() = default;

        const   Map& getMap() const {return frameMap;}
                Map& getMap()       {return frameMap;}

        frameType operator()(const string& i, size_t duration, size_t& frame, size_t& counter) const;
        frameList operator[](const string& i) const {return frameMap.at(i);}
    };

    template <typename frameList, typename frameType>
    frameType AnimatedSet<frameList,frameType>::operator()(const string& i, size_t duration,size_t& frame, size_t& counter) const {
        auto set = frameMap.at(i);
        counter = (counter+1)%duration;
        frame = (counter==0) ? (frame+1)%set.size() : frame%set.size();

        return set[frame];
    }

} // Engine

#endif //NOWHEREFIGHTERS_ANIMATEDSET_H
