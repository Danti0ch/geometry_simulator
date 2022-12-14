#include "Color.h"
#include <iostream>

const uint32_t MAX_COMP_VAL = 255;

Color Color::WHITE(255, 255, 255, 255);
Color Color::BLACK(  0,   0,   0, 255);
Color Color::RED(  255,   0,   0, 255);
Color Color::GREEN(  0, 255,   0, 255);
Color Color::BLUE(   0,   0, 255, 255);

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a):
    r_(r), g_(g), b_(b), a_(a){}

//? right order
Color::Color(unsigned int val, uint8_t a){
    uint32_t mask = 0xFF;

    a_ = a;
    b_ = (val & mask);
    g_ = (val & (mask << 8)) >> 8;
    r_ = (val & (mask << 16)) >> 16;
}

void Color::operator +=(const Color& col2){

    r_ = (r_ > MAX_COMP_VAL - col2.r()) ? MAX_COMP_VAL : r_ + col2.r();
    g_ = (g_ > MAX_COMP_VAL - col2.g()) ? MAX_COMP_VAL : g_ + col2.g();
    b_ = (b_ > MAX_COMP_VAL - col2.b()) ? MAX_COMP_VAL : b_ + col2.b();
    a_ = (a_ > MAX_COMP_VAL - col2.a()) ? MAX_COMP_VAL : a_ + col2.a();
    
    return;
}

void Color::operator *=(const Color& col2){

    uint32_t r_new = ((uint32_t)r_ * (uint32_t)col2.r()) / MAX_COMP_VAL;
    uint32_t g_new = ((uint32_t)g_ * (uint32_t)col2.g()) / MAX_COMP_VAL;
    uint32_t b_new = ((uint32_t)b_ * (uint32_t)col2.b()) / MAX_COMP_VAL;
    uint32_t a_new = ((uint32_t)a_ * (uint32_t)col2.a()) / MAX_COMP_VAL;
    
    r_ = (r_new > MAX_COMP_VAL) ? MAX_COMP_VAL : r_new;
    g_ = (g_new > MAX_COMP_VAL) ? MAX_COMP_VAL : g_new;
    b_ = (b_new > MAX_COMP_VAL) ? MAX_COMP_VAL : b_new;
    a_ = (a_new > MAX_COMP_VAL) ? MAX_COMP_VAL : a_new;
    
    return;
}

void Color::operator *=(double ratio){

    uint32_t r_new = (double)r_ * ratio;
    uint32_t g_new = (double)g_ * ratio;
    uint32_t b_new = (double)b_ * ratio;
    uint32_t a_new = (double)a_ * ratio;
    
    r_ = (r_new > MAX_COMP_VAL) ? MAX_COMP_VAL : r_new;
    g_ = (g_new > MAX_COMP_VAL) ? MAX_COMP_VAL : g_new;
    b_ = (b_new > MAX_COMP_VAL) ? MAX_COMP_VAL : b_new;
    a_ = (a_new > MAX_COMP_VAL) ? MAX_COMP_VAL : a_new;

    return;
}

void Color::operator -=(const Color& col2){

    r_ = (r_ < col2.r()) ? 0 : r_ - col2.r();
    g_ = (g_ < col2.g()) ? 0 : g_ - col2.g();
    b_ = (b_ < col2.b()) ? 0 : b_ - col2.b();
    a_ = (a_ < col2.a()) ? 0 : a_ - col2.a();
    
    return;
}

Color Color::operator +(const Color& col2) const{

    Color new_obj = *this;
    new_obj.operator+=(col2);

    return new_obj;
}

Color Color::operator *(const Color& col2) const{

    Color new_obj = *this;
    new_obj.operator*=(col2);

    return new_obj;
}

Color Color::operator *(double ratio) const{

    Color new_obj = *this;
    new_obj.operator*=(ratio);

    return new_obj;
}

Color Color::operator -(const Color& col2) const{

    Color new_obj = *this;
    new_obj.operator-=(col2);

    return new_obj;
}

Color::operator unsigned int() const{
    uint32_t val = 0;

    uint32_t mask = 0xFF;

    val |= ((uint32_t)b_);
    val |= ((uint32_t)g_) << 8;
    val |= ((uint32_t)r_) << 16;
}

uint32_t convertTosColor(const Color& col){
    uint32_t val = 0;

    uint32_t mask = 0xFF;

    val |= ((uint32_t)col.a());
    val |= ((uint32_t)col.b()) << 8;
    val |= ((uint32_t)col.g()) << 16;
    val |= ((uint32_t)col.r()) << 24;

    return val;
}

Color convertFromsColor(uint32_t val){
    return Color(val >> 8, val & 0xFF);
}
