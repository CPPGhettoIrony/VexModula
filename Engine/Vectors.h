//
// Created by blenk on 20/02/24.
//

#ifndef NOWHEREFIGHTERS_VECTORS_H
#define NOWHEREFIGHTERS_VECTORS_H

#include <ostream>
#include <raylib.h>
#include <cmath>

#include "AngelMacros.h"

using std::size_t, std::ostream;

namespace Engine {

    inline bool inside(float a , float b, float c) {
        return (a>b && a<=b+c);
    }

    class ScriptWrapper;

    class Rect;

    class Vec2 {

        Vector2 vec;
        SETCREF()
        static const float nullValue;

    public:

        Vec2(): vec{0,0}, SETREFCOUNT() {}
        Vec2(const float& a, const float& b): vec{a,b}, SETREFCOUNT() {}
        Vec2(const Vec2& v): vec{v.vec.x,v.vec.y}, SETREFCOUNT() {}
        Vec2(const Rect& r);

        Vec2 operator+(const Vec2&) const;
        Vec2 operator-(const Vec2&) const;
        Vec2 operator*(const Vec2&) const;
        Vec2 operator/(const Vec2&) const;

        Vec2& operator+=(const Vec2&);
        Vec2& operator-=(const Vec2&);
        Vec2& operator*=(const Vec2&);
        Vec2& operator/=(const Vec2&);

        Vec2 operator+(float) const;
        Vec2 operator-(float) const;
        Vec2 operator*(float) const;
        Vec2 operator/(float) const;

        Vec2& operator+=(float);
        Vec2& operator-=(float);
        Vec2& operator*=(float);
        Vec2& operator/=(float);

        bool operator==(const Vec2&) const;

        const float& operator[](size_t index) const;
        float& at(size_t index)  {return index==0?vec.x:vec.y;}

        [[nodiscard ]] Vector2 toRaylibVector() const {return vec;}
        Vec2& operator=(const Vec2& v) {vec.x = v.vec.x; vec.y = v.vec.y; return *this;}
        [[nodiscard]] float getDegrees() const {return atan2f(vec.x, vec.y) * 180 / 3.141;}

    };

    class Rect {

        Rectangle rect;
        SETCREF()
        static const float nullValue;

    public:

        Rect(): rect{0,0,0,0}, SETREFCOUNT() {}
        explicit Rect(const float& a, const float& b, const float& c, const float& d): rect{a,b,c,d}, SETREFCOUNT() {}
        Rect(const Rect& r): rect{r.rect.x, r.rect.y, r.rect.width, r.rect.height}, SETREFCOUNT() {}
        Rect(const Vec2 &v);

        Rect operator+(const Rect&) const;
        Rect operator-(const Rect&) const;
        Rect operator*(const Rect&) const;
        Rect operator/(const Rect&) const;

        Rect& operator+=(const Rect&);
        Rect& operator-=(const Rect&);
        Rect& operator*=(const Rect&);
        Rect& operator/=(const Rect&);

        Rect operator+(float) const;
        Rect operator-(float) const;
        Rect operator*(float) const;
        Rect operator/(float) const;

        Rect& operator+=(float);
        Rect& operator-=(float);
        Rect& operator*=(float);
        Rect& operator/=(float);

        bool operator==(const Rect&) const;

        const float& operator[](size_t index) const;
        float& at(size_t index);

        [[nodiscard]] Rectangle toRaylibRectangle() const {return rect;}
        [[nodiscard]] Vec2 getPos() const {return Vec2{rect.x, rect.y};}
        [[nodiscard]] Vec2 getDim() const {return Vec2{rect.width, rect.height};}
        [[nodiscard]] Vec2 getMidPoint() const {return Vec2(getPos() + getDim() / 2);}
        Rect& operator=(const Rect& rect) {for(size_t i=0;i<4;++i) this->at(i) = rect[i]; return *this;}

        [[nodiscard]] bool isColliding(const Rect& R) const;
        [[nodiscard]] Vec2 Collide(const Rect&) const;
        [[nodiscard]] float getTriAngle() const {
            return -Vec2(Vec2{rect.x+rect.width,rect.y+rect.height}-getMidPoint()).getDegrees();
        }

    };

    ostream& operator<<(ostream&, const Vec2&);
    ostream& operator<<(ostream&, const Rect&);

    inline Vec2* Vec2Factory_Default()                                  RETURNFACTORY(Vec2)
    inline Vec2* Vec2Factory_Init(float a, float b)                     RETURNFACTORY(Vec2(a, b))
    inline Vec2* Vec2Factory_Copy(const Vec2& vec)                      RETURNFACTORY(Vec2(vec))
    inline Vec2* Vec2Factory_CopyRect(const Rect& rect)                 RETURNFACTORY(Vec2(rect))

    inline Rect* RectFactory_Default()                                  RETURNFACTORY(Rect)
    inline Rect* RectFactory_Init(float a, float b, float c, float d)   RETURNFACTORY(Rect(a, b, c, d))
    inline Rect* RectFactory_Copy(const Rect& rect)                     RETURNFACTORY(Rect(rect))
    inline Rect* RectFactory_CopyVec2(const Vec2& vec)                  RETURNFACTORY(Rect(vec))

}


#endif //NOWHEREFIGHTERS_VECTORS_H
