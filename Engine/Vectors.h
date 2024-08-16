//
// Created by blenk on 20/02/24.
//

#ifndef NOWHEREFIGHTERS_VECTORS_H
#define NOWHEREFIGHTERS_VECTORS_H

#include <initializer_list>
#include <ostream>
#include <raylib.h>
#include <cmath>

#include "ScriptObjects.h"

using std::size_t, std::ostream;

typedef Vector2 rayVec2;

namespace Engine {

    inline bool inside(float a , float b, float c) {
        return (a>b && a<=b+c);
    }

    class Vector: public CRef {

    protected:
        size_t size;
        float* floats;
        const static float nullvalue;
        template <typename func>
            void op(func);

    public:

        enum{X,Y,W,H};

        Vector(size_t size=0);
        Vector(const std::initializer_list<float>&,size_t);
        Vector(const std::initializer_list<float>&);
        Vector(const Vector&);

        Vector operator+(const Vector&) const;
        Vector operator-(const Vector&) const;
        Vector operator*(const Vector&) const;
        Vector operator/(const Vector&) const;

        Vector& operator+=(const Vector&);
        Vector& operator-=(const Vector&);

        Vector operator+(float) const;
        Vector operator-(float) const;
        Vector operator*(float) const;
        Vector operator/(float) const;

        Vector& operator+=(float);
        Vector& operator-=(float);

        bool operator==(const Vector&);
        bool operator!=(const Vector& vec) {return !(*this==vec);}

        const float& operator[](size_t i) const {return (i<size) ? floats[i] : nullvalue;}
        float& at(size_t i) {return floats[i];}

        [[nodiscard]] size_t Size() const {return size;}

        ~Vector() {delete[] floats;}
    };

    template <typename func>
    void Vector::op(func foo) {
        for(size_t i=0; i<size; ++i) floats[i] = foo(i);
    }

    class Vec2 : public Vector {
    public:
        Vec2(): Vector({}, 2) {}
        Vec2(const float& a, const float& b): Vector({a,b}, 2) {}
        explicit Vec2(const Vector& vec): Vector{{}, 2} {
            op([&](size_t i){return vec[i];});
        }
        [[nodiscard ]] rayVec2 toRaylibVector() const;
        Vec2& operator=(const Vec2& vec) {for(size_t i=0; i < 2; ++i) floats[i] = vec.floats[i]; return *this;}
        [[nodiscard]] float getDegrees() const {return atan2f(floats[X], floats[Y]) * 180 / 3.141;}

        // To make operators in Angelscript with reference types, this must be done in a special way
        [[nodiscard]] Vec2& opAdd(const Vec2& vec) const;
        [[nodiscard]] Vec2& opSub(const Vec2& vec) const;
        [[nodiscard]] Vec2& opMul(const Vec2& vec) const;
        [[nodiscard]] Vec2& opDiv(const Vec2& vec) const;

        [[nodiscard]] Vec2& opAddAssign(const Vec2& vec);
        [[nodiscard]] Vec2& opSubAssign(const Vec2& vec);
        [[nodiscard]] Vec2& opMulAssign(const Vec2& vec);
        [[nodiscard]] Vec2& opDivAssign(const Vec2& vec);

    };

    class Rect : public Vector {
    public:
        Rect(): Vector({}, 4) {}
        explicit Rect(const float& a, const float& b, const float& c, const float& d): Vector({a,b,c,d}) {}
        Rect(const Vector& vec): Vector{{vec[0], vec[1], 0, 0},4} {}
        [[nodiscard]] Rectangle toRaylibRectangle() const;
        [[nodiscard]] Vec2 getPos() const {return Vec2{floats[0], floats[1]};}
        [[nodiscard]] Vec2 getDim() const {return Vec2{floats[2], floats[3]};}
        [[nodiscard]] Vec2 getMidPoint() const {return Vec2(getPos() + getDim() / 2);}
        Rect& operator=(const Rect& vec) {for(size_t i=0;i<4;++i) floats[i] = vec.floats[i]; return *this;}

        [[nodiscard]] bool isColliding(const Rect& R) const;
        [[nodiscard]] Vec2 Collide(const Rect&) const;
        [[nodiscard]] float getTriAngle() const {
            return -Vec2(Vec2{floats[X]+floats[W],floats[Y]+floats[H]}-getMidPoint()).getDegrees();
        }

        // To make operators in Angelscript with reference types, this must be done in a special way
        [[nodiscard]] Rect& opAdd(const Rect& rect) const;
        [[nodiscard]] Rect& opSub(const Rect& rect) const;
        [[nodiscard]] Rect& opMul(const Rect& rect) const;
        [[nodiscard]] Rect& opDiv(const Rect& rect) const;

        [[nodiscard]] Rect& opAddAssign(const Rect& rect);
        [[nodiscard]] Rect& opSubAssign(const Rect& rect);
        [[nodiscard]] Rect& opMulAssign(const Rect& rect);
        [[nodiscard]] Rect& opDivAssign(const Rect& rect);
    };

    ostream& operator<<(ostream&, const Vector&);

    inline Vector* VectorFactory(size_t size) {return new Vector(size);}

    inline Vec2* Vec2Factory_Default() {return new Vec2;}
    inline Vec2* Vec2Factory_Init(float a, float b) {return new Vec2(a, b);}
    inline Vec2* Vec2Factory_Copy(const Vec2& vec) {return new Vec2(vec);}
    inline Vec2* Vec2Factory_CopyRect(const Rect& rect) {return new Vec2(rect);}

    inline Rect* RectFactory_Default() {return new Rect;}
    inline Rect* RectFactory_Init(float a, float b, float c, float d) {return new Rect(a, b, c, d);}
    inline Rect* RectFactory_Copy(const Rect& rect) {return new Rect(rect);}
    inline Rect* RectFactory_CopyVec2(const Vec2& vec) {return new Rect(vec);}

}


#endif //NOWHEREFIGHTERS_VECTORS_H
