//
// Created by blenk on 20/02/24.
//


#include "Vectors.h"
#include <vector>
#include <algorithm>
#include <strings.h>

using std::vector;

namespace Engine {

    const float Vec2::nullValue = 0;
    const float Rect::nullValue = 0;

    Vec2::Vec2(const Rect &r): vec{r[0], r[1]},  SETREFCOUNT() {}
    Rect::Rect(const Vec2 &v): rect{v[0], v[1]}, SETREFCOUNT() {}

    const float& Vec2::operator[](size_t inde0) const {
        switch (inde0) {
            case 0:
                return vec.x;
            case 1:
                return vec.y;
            default:
                return nullValue;
        }
    }

    const float& Rect::operator[](size_t inde0) const {
        switch (inde0) {
            case 0:
                return rect.x;
            case 1:
                return rect.y;
            case 2:
                return rect.width;
            case 3:
                return rect.height;
            default:
                return nullValue;
        }
    }

    float& Rect::at(size_t inde0) {
        switch (inde0) {
            case 0:
                return rect.x;
            case 1:
                return rect.y;
            case 2:
                return rect.width;
            default:
                return rect.height;
        }
    }

    ostream& operator<<(ostream& stream, const Vec2& vec) {
        stream << vec[0] << ',' << vec[1];
        return stream;
    }

    ostream& operator<<(ostream& stream, const Rect& rect) {
        stream << rect[0] << ',' << rect[1] << ',' << rect[2] << ',' << rect[3];
        return stream;
    }

    Vec2 Vec2::operator+(const Vec2& v) const {
        Vec2 ret = *this;
        ret.vec.x += v.vec.x;
        ret.vec.y += v.vec.y;
        return ret;
    }

    Vec2 Vec2::operator-(const Vec2& v) const {
        Vec2 ret = *this;
        ret.vec.x -= v.vec.x;
        ret.vec.y -= v.vec.y;
        return ret;
    }

    Vec2 Vec2::operator*(const Vec2& v) const {
        Vec2 ret = *this;
        ret.vec.x *= v.vec.x;
        ret.vec.y *= v.vec.y;
        return ret;
    }

    Vec2 Vec2::operator/(const Vec2& v) const {
        Vec2 ret = *this;
        ret.vec.x /= v.vec.x;
        ret.vec.y /= v.vec.y;
        return ret;
    }

    Vec2& Vec2::operator+=(const Vec2& v) {
        vec.x += v.vec.x;
        vec.y += v.vec.y;
        return *this;
    }

    Vec2& Vec2::operator-=(const Vec2& v) {
        vec.x -= v.vec.x;
        vec.y -= v.vec.y;
        return *this;
    }

    Vec2& Vec2::operator*=(const Vec2& v) {
        vec.x *= v.vec.x;
        vec.y *= v.vec.y;
        return *this;
    }

    Vec2& Vec2::operator/=(const Vec2& v) {
        vec.x /= v.vec.x;
        vec.y /= v.vec.y;
        return *this;
    }

    Vec2 Vec2::operator+(float f) const {
        Vec2 ret = *this;
        ret.vec.x += f;
        ret.vec.y += f;
        return ret;
    }

    Vec2 Vec2::operator-(float f) const {
        Vec2 ret = *this;
        ret.vec.x -= f;
        ret.vec.y -= f;
        return ret;
    }

    Vec2 Vec2::operator*(float f) const {
        Vec2 ret = *this;
        ret.vec.x *= f;
        ret.vec.y *= f;
        return ret;
    }

    Vec2 Vec2::operator/(float f) const {
        Vec2 ret = *this;
        ret.vec.x /= f;
        ret.vec.y /= f;
        return ret;
    }

    Vec2& Vec2::operator+=(float f) {
        vec.x += f;
        vec.y += f;
        return *this;
    }

    Vec2& Vec2::operator-=(float f) {
        vec.x -= f;
        vec.y -= f;
        return *this;
    }

    Vec2& Vec2::operator*=(float f) {
        vec.x *= f;
        vec.y *= f;
        return *this;
    }

    Vec2& Vec2::operator/=(float f) {
        vec.x /= f;
        vec.y /= f;
        return *this;
    }

    bool Vec2::operator==(const Vec2& v) const {
        return vec.x == v.vec.x && vec.y == v.vec.y;
        return true;
    }

    Rect Rect::operator+(const Rect& v) const {
        Rect ret = *this;
        ret.rect.x += v.rect.x;
        ret.rect.y += v.rect.y;
        ret.rect.width += v.rect.width;
        ret.rect.height += v.rect.height;
        return ret;
    }

    Rect Rect::operator-(const Rect& v) const {
        Rect ret = *this;
        ret.rect.x -= v.rect.x;
        ret.rect.y -= v.rect.y;
        ret.rect.width -= v.rect.width;
        ret.rect.height -= v.rect.height;
        return ret;
    }

    Rect Rect::operator*(const Rect& v) const {
        Rect ret = *this;
        ret.rect.x *= v.rect.x;
        ret.rect.y *= v.rect.y;
        ret.rect.width *= v.rect.width;
        ret.rect.height *= v.rect.height;
        return ret;
    }

    Rect Rect::operator/(const Rect& v) const {
        Rect ret = *this;
        ret.rect.x /= v.rect.x;
        ret.rect.y /= v.rect.y;
        ret.rect.width /= v.rect.width;
        ret.rect.height /= v.rect.height;
        return ret;
    }

    Rect& Rect::operator+=(const Rect& v) {
        rect.x += v.rect.x;
        rect.y += v.rect.y;
        rect.width += v.rect.width;
        rect.height += v.rect.height;
        return *this;
    }

    Rect& Rect::operator-=(const Rect& v) {
        rect.x -= v.rect.x;
        rect.y -= v.rect.y;
        rect.width -= v.rect.width;
        rect.height -= v.rect.height;
        return *this;
    }

    Rect& Rect::operator*=(const Rect& v) {
        rect.x *= v.rect.x;
        rect.y *= v.rect.y;
        rect.width *= v.rect.width;
        rect.height *= v.rect.height;
        return *this;
    }

    Rect& Rect::operator/=(const Rect& v) {
        rect.x /= v.rect.x;
        rect.y /= v.rect.y;
        rect.width /= v.rect.width;
        rect.height /= v.rect.height;
        return *this;
    }

    Rect Rect::operator+(float f) const {
        Rect ret = *this;
        ret.rect.x += f;
        ret.rect.y += f;
        ret.rect.width += f;
        ret.rect.height += f;
        return ret;
    }

    Rect Rect::operator-(float f) const {
        Rect ret = *this;
        ret.rect.x -= f;
        ret.rect.y -= f;
        ret.rect.width -= f;
        ret.rect.height -= f;
        return ret;
    }

    Rect Rect::operator*(float f) const {
        Rect ret = *this;
        ret.rect.x *= f;
        ret.rect.y *= f;
        ret.rect.width *= f;
        ret.rect.height *= f;
        return ret;
    }

    Rect Rect::operator/(float f) const {
        Rect ret = *this;
        ret.rect.x /= f;
        ret.rect.y /= f;
        ret.rect.width /= f;
        ret.rect.height /= f;
        return ret;
    }

    Rect& Rect::operator+=(float f) {
        rect.x += f;
        rect.y += f;
        rect.width += f;
        rect.height += f;
        return *this;
    }

    Rect& Rect::operator-=(float f) {
        rect.x -= f;
        rect.y -= f;
        rect.width -= f;
        rect.height -= f;
        return *this;
    }

    Rect& Rect::operator*=(float f) {
        rect.x *= f;
        rect.y *= f;
        rect.width *= f;
        rect.height *= f;
        return *this;
    }

    Rect& Rect::operator/=(float f) {
        rect.x /= f;
        rect.y /= f;
        rect.width /= f;
        rect.height /= f;
        return *this;
    }

    bool Rect::operator==(const Rect& v) const {
        return rect.x == v.rect.x && rect.y == v.rect.y && rect.width == v.rect.width && rect.height == v.rect.height;
        return true;
    }

    bool Rect::isColliding(const Rect &R) const{

        bool selfpoints[] = {
                inside(rect.x,R[0],R[2]),
                inside(rect.x+rect.width,R[0],R[2]),
                inside(rect.y,R[1],R[3]),
                inside(rect.y+rect.height,R[1],R[3]),
        };

        bool self =  (selfpoints[0] || selfpoints[1]) && (selfpoints[2] || selfpoints[3]);

        bool otherpoints[] = {
                inside(R[0],rect.x,rect.width),
                inside(R[0]+R[2],rect.x,rect.width),
                inside(R[1],rect.y,rect.height),
                inside(R[1]+R[3],rect.y,rect.height),
        };

        bool other =  (otherpoints[0] || otherpoints[1]) && (otherpoints[2] || otherpoints[3]);

        return self || other;
    }

    Vec2 Rect::Collide(const Rect &R) const {

        constexpr size_t X=0, Y=1, W=2, H=3;
        Vec2 smp = getMidPoint(), rmp = R.getMidPoint(), ret;

        float   offsetXA = (rmp[X]>smp[X]) ? (rect.x + rect.width - R[X]) : (-rect.x - rect.width + R[X] + R[W]),
                offsetXB = (rmp[X]>smp[X]) ? (rect.x - R[X]) : (-rect.x + R[X] + R[W]),
                offsetYA = (rmp[Y]>smp[Y]) ? (rect.y + rect.height - R[Y]) : (-rect.y - rect.height + R[Y] + R[H]),
                offsetYB = (rmp[Y]>smp[Y]) ? (rect.y - R[Y]) : (-rect.y + R[Y] + R[H]);

        vector offset{offsetXA,offsetXB,offsetYA,offsetYB};
        float max = *std::max_element(offset.begin(),offset.end());

        if(max == offsetXA || max == offsetXB) {
            if (smp[Y] < rmp[Y]) ret.at(Y) = R[Y] - rect.y - rect.height;
            if (smp[Y] > rmp[Y]) ret.at(Y) = -rect.y + R[Y] + R[H];
        } else if(max == offsetYA || max == offsetYB) {
            if (smp[X] < rmp[X]) ret.at(X) = R[X] - rect.x - rect.width;
            if (smp[X] > rmp[X]) ret.at(X) = -rect.x + R[X] + R[W];
        }

        return ret;
    }

}