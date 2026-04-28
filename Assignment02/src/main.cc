#include "expr.h"
#include "parse.h"

using namespace std;


int main() {
    cout << "Enter expression: " << flush;
    expr *e = parse(cin);
    cout << "f(x) = ";
    e->optimize();

    double x;
    cout << "Enter x to evaluate at: " << flush;
    cin >> x;
    cout << "f(" << x << ") = " << e->eval_at(x) << endl;

    expr *e2 = e->derivative();
    cout << "f'(x) = ";
    e2->optimize();
    cout << "f'(" << x << ") = " << e2->eval_at(x) << endl;
    delete e2;
    return 0;
}