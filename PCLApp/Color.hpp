#pragma once

#include <iostream>

struct Color {
    int R;
    int G;
    int B;
    int A;

    Color(int r, int g, int b, int a){
        this->R = r;
        this->G = g;
        this->B = b;
        this->A = a;
    }

    Color(int r, int g, int b){
        this->R = r;
        this->G = g;
        this->B = b;
        this->A = 0;
    }

};
