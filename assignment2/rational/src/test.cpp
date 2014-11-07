#include "rational.h"
#include <cassert>
#include <iostream>
#include <iomanip>
#include <exception>

int main() {
    auto a = Rational{ 1, 3 }; // the number 1/3
    auto b = Rational{ -6, 7 }; // the number -6/7
    auto c = Rational{ 12, -27 }; // the number -4/9
    auto d = Rational{ -5, - 9 }; // the number 5/9
    
    auto result = a * b;
    auto right = Rational { -2, 7 };
    assert ( result == right );
    
    
    
    result = a / ( a + b / a );
    right = Rational{ -7, 47 };
    assert ( result == right );
    
    result = ( c - d ) / (a + b + d);
    right = Rational{ -63, 2 };
    assert ( result == right );
    
    try {
        result = Rational{ 1, 0 };
    } catch ( std::exception& e ) {
        std::cout << e.what() << "\n";
    }
    
    result = d.inverse();
    right = Rational { 9, 5 };
    assert ( result == right );
    
    
    auto phi = Rational{ 1 };
    
    for( int i = 0; i < 40; ++i ) {
        phi = 1 / ( 1 + phi );
    }
    std::cout << std::setprecision( 15 );
    std::cout << "phi = " << ( 1 + phi ).to_double() << "\n";
    
    return 0;
}
