//
// Created by blenk on 20/02/24.
//

#ifndef NOWHEREFIGHTERS_VECTORS_H
#define NOWHEREFIGHTERS_VECTORS_H

#include <initializer_list>
#include <ostream>
#include <raylib.h>
#include <math.h>

using std::size_t, std::ostream;

typedef Vector2 rayVec2;

namespace Engine {

    inline bool inside(float a , float b, float c) {
        return (a>b && a<=b+c);
    }

    class Vector {

    protected:
        size_t size;
        float* floats;
        const static float nullvalue;
        template <typename func>
        void op(func);

    public:

        enum{X,Y,W,H};

        Vector(const std::initializer_list<float>&,size_t);
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
        Vec2(const std::initializer_list<float>& list = {}): Vector(list, 2) {}
        Vec2(const Vector& vec): Vector{{}, 2} {
            op([&](size_t i){return vec[i];});
        }
        [[nodiscard ]] rayVec2 toRaylibVector() const;
        Vec2& operator=(const Vec2& vec) {for(size_t i=0; i < 2; ++i) floats[i] = vec.floats[i]; return *this;}
        float getDegrees() {return atan2(floats[X], floats[Y]) * 180 / 3.141;}
    };

    class Rect : public Vector {
    public:
        Rect(const std::initializer_list<float>& list = {}): Vector(list,4) {}
        Rect(const Vector& vec): Vector{{},4} {
            op([&](size_t i){return vec[i];});
        }
        [[nodiscard]] Rectangle toRaylibRectangle() const;
        [[nodiscard]] Vec2 getPos() const {return {floats[0], floats[1]};}
        [[nodiscard]] Vec2 getDim() const {return {floats[2], floats[3]};}
        [[nodiscard]] Vec2 getMidPoint() const {return Vec2(getPos() + getDim() / 2);}
        Rect& operator=(const Rect& vec) {for(size_t i=0;i<4;++i) floats[i] = vec.floats[i]; return *this;}

        [[nodiscard]] bool isColliding(const Rect& R) const;
        [[nodiscard]] Vec2 Collide(const Rect&) const;
        [[nodiscard]] float getTriAngle() const {
            return -Vec2(Vec2{floats[X]+floats[W],floats[Y]+floats[H]}-getMidPoint()).getDegrees();
        }
    };

    ostream& operator<<(ostream&, const Vector&);

}


#endif //NOWHEREFIGHTERS_VECTORS_H
