//
// Created by blenk on 20/02/24.
//


#include "Vectors.h"
#include <vector>
#include <algorithm>

using std::vector;

#include <iostream>
using std::cout;

namespace Engine {

    const float Vector::nullvalue(0);

    Vector::Vector(const std::initializer_list<float>& list, size_t s): size(s), floats(new float[size]) {
        size_t i = 0;
        for(const auto f : list) {
            floats[i] = f;
            ++i;
        }
        for(;i<size;++i) floats[i] = 0;
    }

    Vector::Vector(const std::initializer_list<float>& list): size(list.size()), floats(new float[list.size()]) {
        size_t i = 0;
        for(const auto f : list) {
            floats[i] = f;
            ++i;
        }
        for(;i<size;++i) floats[i] = 0;
    }

    Vector::Vector(const Vector& vec): floats(new float[vec.size]), size(vec.size) {
        for(size_t i=0; i<size; ++i) {
            if(vec[i] != nullvalue) floats[i] = vec[i];
            else floats[i] = 0;
        }
    }

    Vector Vector::operator+(const Vector& vec) const {
        Vector ret = *this;
        ret.op([&](size_t i){return vec[i]+ret.floats[i];});
        return ret;
    }

    Vector Vector::operator-(const Vector& vec) const {
        Vector ret = *this;
        ret.op([&](size_t i){return ret.floats[i]-vec[i];});
        return ret;
    }

    Vector Vector::operator*(const Vector& vec) const {
        Vector ret = *this;
        ret.op([&](size_t i){return vec[i]*ret.floats[i];});
        return ret;
    }

    Vector Vector::operator/(const Vector& vec) const {
        Vector ret = *this;
        ret.op([&](size_t i){return ret.floats[i]/vec[i];});
        return ret;
    }

    Vector& Vector::operator+=(const Vector& vec) {
        op([&](size_t i){return vec[i]+floats[i];});
        return *this;
    }

    Vector& Vector::operator-=(const Vector& vec) {
        op([&](size_t i){return floats[i]-vec[i];});
        return *this;
    }

    Vector Vector::operator+(float f) const {
        Vector ret = *this;
        ret.op([&](size_t i){return f+ret.floats[i];});
        return ret;
    }

    Vector Vector::operator-(float f) const {
        Vector ret = *this;
        ret.op([&](size_t i){return ret.floats[i]-f;});
        return ret;
    }

    Vector Vector::operator*(float f) const {
        Vector ret = *this;
        ret.op([&](size_t i){return f*ret.floats[i];});
        return ret;
    }

    Vector Vector::operator/(float f) const {
        Vector ret = *this;
        ret.op([&](size_t i){return ret.floats[i]/f;});
        return ret;
    }

    Vector& Vector::operator+=(float f) {
        op([&](size_t i){return f+floats[i];});
        return *this;
    }

    Vector& Vector::operator-=(float f) {
        op([&](size_t i){return floats[i]-f;});
        return *this;
    }

    bool Vector::operator==(const Vector& vec) {
        for(size_t i=0; i<size; ++i) if(floats[i]!=vec.floats[i]) return false;
        return true;
    }

    ostream& operator<<(ostream& stream, const Vector& vec) {
        size_t size = vec.Size();
        for(size_t i=0; i<size; ++i) stream << vec[i] << ',';
        return stream;
    }

    rayVec2 Vec2::toRaylibVector() const {
        rayVec2 ret;
        ret.x = (*this)[0];
        ret.y = (*this)[1];
        return ret;
    }

    Rectangle Rect::toRaylibRectangle() const {
        Rectangle ret;
        ret.x = (*this)[0];
        ret.y = (*this)[1];
        ret.width = (*this)[2];
        ret.height = (*this)[3];
        return ret;
    }

    bool Rect::isColliding(const Rect &R) const{

        bool selfpoints[] = {
                inside(floats[0],R[0],R[2]),
                inside(floats[0]+floats[2],R[0],R[2]),
                inside(floats[1],R[1],R[3]),
                inside(floats[1]+floats[3],R[1],R[3]),
        };

        bool self =  (selfpoints[0] || selfpoints[1]) && (selfpoints[2] || selfpoints[3]);

        bool otherpoints[] = {
                inside(R[0],floats[0],floats[2]),
                inside(R[0]+R[2],floats[0],floats[2]),
                inside(R[1],floats[1],floats[3]),
                inside(R[1]+R[3],floats[1],floats[3]),
        };

        bool other =  (otherpoints[0] || otherpoints[1]) && (otherpoints[2] || otherpoints[3]);

        return self || other;
    }

    Vec2 Rect::Collide(const Rect &R) const {

        Vec2 smp = getMidPoint(), rmp = R.getMidPoint(), ret;

        float   offsetXA = (rmp[X]>smp[X]) ? (floats[X] + floats[W] - R[X]) : (-floats[X] - floats[W] + R[X] + R[W]),
                offsetXB = (rmp[X]>smp[X]) ? (floats[X] - R[X]) : (-floats[X] + R[X] + R[W]),
                offsetYA = (rmp[Y]>smp[Y]) ? (floats[Y] + floats[H] - R[Y]) : (-floats[Y] - floats[H] + R[Y] + R[H]),
                offsetYB = (rmp[Y]>smp[Y]) ? (floats[Y] - R[Y]) : (-floats[Y] + R[Y] + R[H]);

        vector offset{offsetXA,offsetXB,offsetYA,offsetYB};
        float max = *std::max_element(offset.begin(),offset.end());

        if(max == offsetXA || max == offsetXB) {
            if (smp[Y] < rmp[Y]) ret.at(Y) = R[Y] - floats[Y] - floats[H];
            if (smp[Y] > rmp[Y]) ret.at(Y) = -floats[Y] + R[Y] + R[H];
        } else if(max == offsetYA || max == offsetYB) {
            if (smp[X] < rmp[X]) ret.at(X) = R[X] - floats[X] - floats[W];
            if (smp[X] > rmp[X]) ret.at(X) = -floats[X] + R[X] + R[W];
        }

        return ret;
    }


}