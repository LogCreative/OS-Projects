// Week 1 - Problem 2:
// Solving zero of the function

// By using Binary Division
// The polynomial interpretation

#include "../std_lib_facilities.h"
#include "polynomial.h"

#define ITER_THES 2000      // 迭代次数阈值
#define ACCURACY 1e-6       // 精确度

// 区间两端值相等
class SameSymbolException {
public:
    SameSymbolException(): 
        message("The symbol of the function values of each side should be different.\n") {}
    const char* what() const {return message;}
private:
    const char* message;
};

// 超出迭代次数上限
class OutOfIterationLimitException {
public:
    OutOfIterationLimitException(): 
        message("Out of iteration limit.\n") {}
    const char* what() const {return message;}
private:
    const char* message;
};

double BinaryZeroSolver(Polynomial* poly,double a, double b){
    double left = a, right = b, mid;
    double fleft = poly->getValue(left),
            fright = poly->getValue(right),
            fmid;
    try{
        if(fleft * fright>0)
            throw SameSymbolException();

        int iter = 0;
        do {
            mid = left + (right - left) / 2;
            
            fleft = poly->getValue(left); 
            fmid = poly->getValue(mid);
            fright = poly->getValue(right);

            if(fmid == 0) return mid;
            if(fleft * fmid < 0) right = mid;
            else left = mid;

            if(++iter>ITER_THES)
                throw OutOfIterationLimitException();
        } while(right-left>ACCURACY);
        return left + (right - left) / 2;
    }
    catch(SameSymbolException ex){
        cout << ex.what();
    }
    catch(OutOfIterationLimitException ex){
        cout << ex.what();
    }
}

// Newton's method:
// x[k+1] = x[k] - f(x[k]) / fprime(x[k])
double NewtonZeroSolver(Polynomial *poly, double initialValue){
    double xprev, xfwd  = initialValue;
    int iteration = 0;
    try{
        do{
            xprev = xfwd;
            xfwd = xprev - poly->getValue(xprev) / poly->getDerivValue(xprev);
            if (++iteration>ITER_THES)
                throw OutOfIterationLimitException();
        } while(abs(xfwd - xprev)>2e-5);
        return xfwd;
    }
    catch(OutOfIterationLimitException ex){
        cout << ex.what();
    }
}

int main(){
    Polynomial* poly = new Polynomial();

    double intStart, intEnd;
    cout << "Please input the solving interval:";
    cin >> intStart >> intEnd;
    cout << "The zero of function(Binary Method):";
    cout << BinaryZeroSolver(poly, intStart, intEnd) << endl;
    cout << "The zero of function(Newton's Method):";
    cout << NewtonZeroSolver(poly, intStart) << endl;
    return 0;
}