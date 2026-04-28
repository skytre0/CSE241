#include "expr.h"

using namespace std;

expr::expr(expr const* other) : numer(new long[other->getnl()]), denum(new long[other->getdl()]), nl(other->getnl()), dl(other->getdl()) {
    for (size_t i = 0; i < this->nl; i++)
        this->numer[i] = other->getnumer()[i];
    for (size_t i = 0; i < this->dl; i++)
        this->denum[i] = other->getdenum()[i];
}


expr& expr::operator=(expr const& other) {
    delete [] this->numer;
    delete [] this->denum;

    this->nl = other.nl;
    this->dl = other.dl;
    this->numer = new long[this->nl];
    this->denum = new long[this->dl];
    
    for (size_t i = 0; i < this->nl; i++)
        this->numer[i] = other.numer[i];
    for (size_t i = 0; i < this->dl; i++)
        this->denum[i] = other.denum[i];
    return *this;
}


int_literal::int_literal(long a) {
    long* new_numer = new long[1]();
    new_numer[0] = a;
    long* new_denum = new long[1]();
    new_denum[0] = 1;
    delete [] this->numer;
    delete [] this->denum;
    this->numer = new_numer;
    this->denum = new_denum;
    this->nl = 1;
    this->dl = 1;
}


monomial::monomial(long a) {
    long* new_numer = new long[a+1]();
    new_numer[a] = 1;
    long* new_denum = new long[1]();
    new_denum[0] = 1;
    delete [] this->numer;
    delete [] this->denum;
    this->numer = new_numer;
    this->denum = new_denum;
    this->nl = a+1;
    this->dl = 1;
}  


addition::addition(expr *first, expr *second) {
    size_t new_nl = std::max((first->getnl() + second->getdl() - 1), (second->getnl() + first->getdl() - 1));
    size_t new_dl = first->getdl() + second->getdl() - 1;
    long* new_numer = new long[new_nl]();
    long* new_denum = new long[new_dl]();
    for (size_t i = 0; i < second->getdl(); i++) {
        for (size_t j = 0; j < first->getnl(); j++) {
            new_numer[i+j] += second->getdenum()[i] * first->getnumer()[j];
        }
    }
    for (size_t i = 0; i < first->getdl(); i++) {
        for (size_t j = 0; j < second->getnl(); j++) {
            new_numer[i+j] += first->getdenum()[i] * second->getnumer()[j];
        }
    }
    for (size_t i = 0; i < first->getdl(); i++) {
        for (size_t j = 0; j < second->getdl(); j++) {
            new_denum[i+j] += first->getdenum()[i] * second->getdenum()[j];
        }
    }
    delete first;
    delete second;
    delete [] this->numer;
    delete [] this->denum;
    this->numer = new_numer;
    this->denum = new_denum;
    this->nl = new_nl;
    this->dl = new_dl;
}


multiplication::multiplication(expr* first, expr* second) {
    size_t new_nl = first->getnl() + second->getnl() - 1;
    size_t new_dl = first->getdl() + second->getdl() - 1;
    long* new_numer = new long[new_nl]();
    long* new_denum = new long[new_dl]();
    for (size_t i = 0; i < first->getnl(); i++) {
        for (size_t j = 0; j < second->getnl(); j++) {
            new_numer[i+j] += first->getnumer()[i] * second->getnumer()[j];
        }
    }
    for (size_t i = 0; i < first->getdl(); i++) {
        for (size_t j = 0; j < second->getdl(); j++) {
            new_denum[i+j] += first->getdenum()[i] * second->getdenum()[j];
        }
    }
    delete first;
    delete second;
    delete [] this->numer;
    delete [] this->denum;
    this->numer = new_numer;
    this->denum = new_denum;
    this->nl = new_nl;
    this->dl = new_dl;
}


division::division(expr* first, expr* second) {
    size_t new_nl = first->getnl() + second->getdl() - 1;
    size_t new_dl = first->getdl() + second->getnl() - 1;
    long* new_numer = new long[new_nl]();
    long* new_denum = new long[new_dl]();
    for (size_t i = 0; i < second->getdl(); i++) {
        for (size_t j = 0; j < first->getnl(); j++) {
            new_numer[i+j] += second->getdenum()[i] * first->getnumer()[j];
        }
    }
    for (size_t i = 0; i < first->getdl(); i++) {
        for (size_t j = 0; j < second->getnl(); j++) {
            new_denum[i+j] += first->getdenum()[i] * second->getnumer()[j];
        }
    }
    delete first;
    delete second;
    delete [] this->numer;
    delete [] this->denum;
    this->numer = new_numer;
    this->denum = new_denum;
    this->nl = new_nl;
    this->dl = new_dl;
}


expr* expr::derivative() {
    if (this->dl == 1) {
        return this->simple_derivative();
    }

    else {
        expr* ee = new int_literal(1);
        ee->nl = this->dl;
        long* new_numer = new long[this->dl];
        for (size_t i = 0; i < this->dl; i++)
            new_numer[i] = this->denum[i];

        delete [] ee->numer;
        ee->numer = new_numer;
        this->dl = 1;
        long* new_denum2 = new long[1];
        delete [] this->denum;
        this->denum = new_denum2;
        this->denum[0] = 1;

        expr* e1 = new int_literal(1);
        *e1 = *this;
        expr* e2 = new int_literal(1);
        *e2 = *ee;
        expr* e3 = new int_literal(1);
        *e3 = *ee;
        expr* e4 = new int_literal(1);
        *e4 = *ee;
        expr* e5 = new int_literal(1);
        *e5 = *ee;
        expr* e6 = new int_literal(1);
        *e6 = *this;

        expr* sol1 = new multiplication(e1->simple_derivative(), e2);   //f'*g
        expr* sol2 = new multiplication(e6, e3->simple_derivative());   //f*g'
        expr* sol3 = new multiplication(e4, e5);    //g*g
        expr* sol4 = new addition(sol1, new multiplication(new int_literal(-1), sol2));
        expr* sol = new division(sol4, sol3);
        *this = *sol;
        delete sol;
        delete ee;
        return this;
    }
}


expr* expr::simple_derivative() {
    size_t new_nl = this->nl - 1;
    long* new_numer = new long[new_nl]();
    for (size_t i = 0; i < new_nl; i++) {
        new_numer[i] = (this->numer[i+1]) * (i+1);
    }
    delete [] this->numer;
    this->numer = new_numer;
    this->nl = new_nl;
    return this;
}


void expr::optimize() const {
    if (dl == 1 && denum[0] == 1) {
        get_equation(numer, nl);
    }
    else {
        int a = 0;
        for (size_t i = 0; i < nl; i++) {
            if (numer[i] != 0)
                a += 1;
        }
        if (a == 1) {
            get_equation(numer, nl);
        }
        else {
            cout << "(";
            get_equation(numer, nl);
            cout << ")";
        }

        cout << " / ";
        a = 0;
        for (size_t i = 0; i < dl; i++) {
            if (denum[i] != 0)
                a += 1;
        }
        if (a == 1) {
            get_equation(denum, dl);
        }
        else {
            cout << "(";
            get_equation(denum, dl);
            cout << ")";
        }
    }
    cout << endl;
}


double expr::eval_at(double x) {
    double upper_sum = 0;
    double lower_sum = 0;
    double total = 0;
    for (size_t i = 0; i < this->nl; i++) {
        upper_sum += (this->numer[i] * pow(x, i));
    }
    for (size_t i = 0; i < this->dl; i++) {
        lower_sum += (this->denum[i] * pow(x, i));
    }
    total = upper_sum / lower_sum;
    return total;
}


void get_equation(long* numer, size_t nl) {
    size_t zero = 0;
    for (size_t i = 0; i < nl; i++) {
        if (numer[nl - i - 1] != 0) {
            zero = 1;
            break;
        }
    }
    if (zero == 0) {
        cout << 0;
        return;
    }
    size_t check = 0;
    for (size_t i = 0; i < nl; i++) {
        long a = numer[nl - i - 1];
        if (a != 0) {
            if (i == 0) {
                if (a != 1) {
                    if (nl - i - 1 == 0)
                        cout << a;
                    else{
                        if (nl - i - 1 != 1)
                            cout << a << " * " << "x" << (nl - i - 1);
                        else
                            cout << a << " * " << "x";
                    }
                }
                else {
                    if (nl - i - 1 == 0)
                        cout << a;
                    else{
                        if (nl - i - 1 != 1)
                            cout << "x" << (nl - i - 1);
                        else
                            cout << "x";
                    }
                }
            }

            else {
                if (a < 0) {
                    if (nl - i - 1 == 0) {
                        cout << " " << a;
                    }
                    else {
                        if (nl - i - 1 != 1)
                            cout << " " << a << " * " << "x" << (nl - i - 1);
                        else
                            cout << " " << a << " * " << "x";
                    }
                }
                else if (a > 0) {
                    if (check != 0) {
                        if (nl - i - 1 == 0) {
                            cout << " + " << a;
                        }
                        else {
                            if (a == 1) {
                                if (nl - i - 1 != 1)
                                    cout << " + " << "x" << (nl - i - 1);
                                else
                                    cout << " + " << "x";
                            }
                            else {
                                if (nl - i - 1 != 1)
                                    cout << " + " << a << " * " << "x" << (nl - i - 1);
                                else
                                    cout << " + " << a << " * " << "x";
                            }
                        }
                    }
                    else {
                        if (nl - i - 1 == 0) {
                            cout << a;
                        }
                        else {
                            if (a == 1) {
                                if (nl - i - 1 != 1)
                                    cout << "x" << (nl - i - 1);
                                else
                                    cout << "x";
                            }
                            else {
                                if (nl - i - 1 != 1)
                                    cout << a << " * " << "x" << (nl - i - 1);
                                else
                                    cout << a << " * " << "x";
                            }
                        }
                    }
                }
            }
            check += 1;
        }
    }
}