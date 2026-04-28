#ifndef EXPR_H
#define EXPR_H

#include <iostream>
#include <cmath>


class expr {
protected:
    long* numer;
    long* denum;
    size_t nl;
    size_t dl;
public:
    expr() : numer(new long[0]), denum(new long[0]), nl(0), dl(0) {}
    virtual ~expr() { delete [] this->numer; delete [] this->denum; }
    expr(expr const* other);
    expr& operator=(expr const&);

    long* getnumer() const { return numer; }
    long* getdenum() const { return denum; }
    size_t getnl() const { return nl; }
    size_t getdl() const { return dl; }

    void optimize() const;
    expr* simple_derivative();
    expr* derivative();
    double eval_at(double);
};


class int_literal : public expr {
public:
    int_literal(long);
};


class monomial : public expr {
public:
    monomial(long);
};


class addition : public expr {
public:
    addition(expr*, expr*);
};


class multiplication : public expr {
public:
    multiplication(expr*, expr*);
};


class division : public expr {
public:
    division(expr*, expr*);
};


void get_equation(long*, size_t);

#endif