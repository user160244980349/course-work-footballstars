#include "../include/Base.h"

Base::Base (Rect pos) {
    this -> ThisAttributes.pos = pos;
};
void Base::SetPos (Rect pos) {
    this -> ThisAttributes.pos = pos;
};
Rect Base::GetPos () {
    return this -> ThisAttributes.pos;
};
Base::~Base () {

};