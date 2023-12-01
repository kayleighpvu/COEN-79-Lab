#include <iostream>
#include <cassert>
#include <cmath>
#include "poly.h"
#include <climits>
#include <iomanip>

//Monica Sommer
// Kayleigh Vu


using namespace std;
// The value semantics (copy constructor and assignment operator) are valid for
// the polynomial class.
namespace coen79_lab4 {

    // CONSTRUCTOR for the polynomial class
    //     PRECONDITION: exponent <= MAXIMUM_DEGREE
    //     POSTCONDITION: This polynomial has been created with all zero
    //     coefficients, except for coefficient c for the specified exponent.
    //     When used as a default constructor (using default values for
    //     both arguments), the result is a polynomial with all zero
    //     coefficients.
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        for (int i = 0; i < CAPACITY; i++) 
        {
            data[i] = 0;
        }
        data[exponent] = c;
    }

    //     PRECONDITION: exponent <= MAXIMUM_DEGREE.
    //     POSTCONDITION: Sets the coefficient for the specified exponent.
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE); //precondtion
        data[exponent] = coefficient;
    }

    //     PRECONDITION: exponent <= MAXIMUM_DEGREE.
    //     POSTCONDITION: Adds the given amount to the coefficient of the
    //     specified exponent.
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE); //precondtion
        data[exponent] += amount;
    }

    //     POSTCONDITION: All coefficients of this polynomial are set to zero.
    void polynomial::clear() {
        for (int i = 0; i < CAPACITY; i++) 
        {
            data[i] = 0;
        }
    }

    //     PRECONDITION: degree( ) < MAXIMUM_DEGREE
    //     POSTCONDITION: The return value is the antiderivative (indefinite integral)
    //     of this polynomial.
    //     NOTE: The return polynomial always has a constant term of zero.
    polynomial polynomial::antiderivative() const {
        assert(degree() < MAXIMUM_DEGREE); //precondtion
        polynomial newPoly(0, 0);
        newPoly.data[0] = 0;
        for (int i = 0; i < MAXIMUM_DEGREE; i++) 
        {
            newPoly.data[i + 1] = (data[i] / (i + 1));
        }
        return newPoly;
    }

    //     POSTCONDITION: Returns coefficient at specified exponent of this polynomial.
    double polynomial::coefficient(unsigned int exponent) const {
        if (exponent > MAXIMUM_DEGREE)
            return 0;
        else
            return data[exponent];
    }

    //     POSTCONDITION: Returns the value of the definite integral computed from
    //     x0 to x1.  The answer is computed analytically.
    double polynomial::definite_integral(double x0, double x1) const {
        double upper = 0; //in the case loop is skipped
        double lower = 0;

        polynomial temp;
        temp = antiderivative();
        for (int i = 0; i < MAXIMUM_DEGREE; i++) 
        {
            lower += (temp.data[i] * pow(x0, i));
            upper += (temp.data[i] * pow(x1, i));
        }
        return upper - lower;
    }

    //     POSTCONDITION: The function returns the value of the largest exponent
    //     with a non-zero coefficient.
    //     If all coefficients are zero, then the function returns zero (even
    //     though, technically, this polynomial does not have a degree).
    unsigned int polynomial::degree() const {
        for (int i = CAPACITY - 1; i >= 0; i--) 
        {
            if (data[i] != 0)
                return i;
        }
        return 0;
    }

    // Returns the poly of the first derivative of current poly
    //     POSTCONDITION: The return value is the first derivative of this polynomial.
    polynomial polynomial::derivative() const {
        polynomial temp;
        for (int i = 1; i < MAXIMUM_DEGREE; ++i) 
        {
            temp.data[i - 1] = (data[i] * i);
        }
        return temp;
    }

    // Returns the value of the poly for given x
    //     POSTCONDITION: The return value is the value of this polynomial with the
    //     given value for the variable x.
    double polynomial::eval(double x) const {
        double total = 0;
        for (int i = 0; i < CAPACITY; i++) 
        {
            total += (data[i] * pow(x, i));
        }
        return total;
    }

    // Returns true when poly is all zero
    //     POSTCONDITION: The return value is true iff the polynomial is the zero polynomial.
    bool polynomial::is_zero() const {
        for (int i = 0; i < MAXIMUM_DEGREE; i++) 
        {
            if (data[i] != 0) 
            {
                return false;
            }
        }
        return true;
    }

    // Returns the next exponent that is larger than e with nonzero coefficient
    //     POSTCONDITION: The return value is the next exponent n which is LARGER
    //     than e such that coefficient(n) != 0. If there is no such term, then the 
    //      return value is zero.
    unsigned int polynomial::next_term(unsigned int e) const {
        for (int i = e + 1; e < MAXIMUM_DEGREE; i++) 
        {
            if (data[i] != 0)
                return i;
        }
        return 0;
    }

    // Returns the next exponent that is smaller than e with nonzero coefficient
    //     POSTCONDITION: The return value is the next exponent n which is SMALLER
    //     than e such that coefficient(n) != 0.
    //     If there is no such term, then the return value is UINT_MAX
    //     from <climits>.
    unsigned int polynomial::previous_term(unsigned int e) const {
        for (int i = e - 1; i >= 0; i--) 
        {
            if (data[i] != 0)
                return i;
        }
        return UINT_MAX;
    }

    // Same functionality as eval member function
    double polynomial::operator()(double x) const {
        return eval(x);
    }


    // Returns sum of two polys
    //     POSTCONDITION: return-value is a polynomial with each coefficient
    //     equal to the sum of the coefficients of p1 & p2 for any given
    //     exponent.
    polynomial operator+(const polynomial &p1, const polynomial &p2) {
        polynomial newPoly;
        for (int i = 0; i < polynomial::CAPACITY; i++)
            newPoly.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
        return newPoly;
    }

    //     POSTCONDITION: return-value is a polynomial with each coefficient
    //     equal to the difference of the coefficients of p1 & p2 for any given
    //     exponent.
    polynomial operator-(const polynomial &p1, const polynomial &p2) {
        polynomial newPoly;
        for (int i = 0; i < polynomial::CAPACITY; i++)
            newPoly.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
        return newPoly;
    }

    //     PRECONDITION: p1.degree( ) + p2.degree( ) <= MAXIMUM_DEGREE.
    //     POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
    //     and the answer is the sum of all these term-by-term products.
    //     For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
    //     return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.
    polynomial operator*(const polynomial &p1, const polynomial &p2) {
        assert((p1.degree() + p2.degree()) <= polynomial::MAXIMUM_DEGREE);
        polynomial newPoly;
        for (int i = 0; i <= p1.degree(); i++)
            for (int j = 0; j <= p2.degree(); j++)
                newPoly.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
        return newPoly;
    }

    //     POSTCONDITION: The polynomial has been printed to ostream out, which,
    //     in turn, has been returned to the calling function.
    //     The format of the polynomial when printed should be as follows:
    //              -2.5x^2 - 4x + 5.9
    //     1) There should be exactly 1 space between the numbers and the operators.
    //     2) The constant coeficient should be printed by itself: 5.3, not 5.3x^0
    //     3) The first coeficient should be followed by a plain x: 4x, not 4x^1
    //     4) The highest degree's coeficient should have a sign: -2.5x^2, but the
    //          following values should all be separated by appropriate operators
    //          and then printed unsigned: -2.5x^2 - 4x...
    //     5) If you manipulate any settings of the outstream inside of this,
    //          such as the precision, they should be restored to what they were
    //          at the start of the function before returning.
    std::ostream &operator<<(ostream &out, const polynomial &p){
        long initial_flags = out.precision();
        out << fixed;
        out << setprecision(1);
        //Prints out the polynomial from highest to lowest degree

        //TODO IF ELSE POS NEG THEN CHECKING X.
        for (auto degree = (int) p.degree(); degree >= 0; degree--) {
            if (p.degree() == 0) 
            {
                out << p.coefficient(0);
            } else if (p.coefficient(degree) != 0) 
            {
                if (degree == p.degree()) 
                {
                    out << p.coefficient(degree) << "x^" << degree << ' ';
                } else if (degree < p.degree() && degree > 1) 
                {
                    if (p.coefficient(degree) < 0) 
                    {
                        out << "- ";
                    } else 
                    {
                        out << "+ ";
                    }
                    out << fabs(p.coefficient(degree)) << "x^" << degree << ' ';
                } else if (degree == 1) 
                {
                    if (p.coefficient(degree) < 0) 
                    {
                        out << "- ";
                    } else 
                    {
                        out << "+ ";
                    }

                    out << fabs(p.coefficient(degree)) << "x ";
                } else if (degree == 0) 
                {
                    if (p.coefficient(degree) < 0) 
                    {
                        out << "- ";
                    } else 
                    {
                        out << "+ ";
                    }
                    out << fabs(p.coefficient(degree));
                }
            }
        }
        out.unsetf(ios_base::floatfield);
        out << setprecision(initial_flags);

        return out;
    }
}

