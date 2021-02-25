#ifndef POLY
#define POLY

// 多项式类
class Polynomial {
private:
    int         n;          //次数
    double*     coeff;      //系数
public:
    // constructor
    Polynomial(){
        std::cout << "Please input the power of polynomial:";
        std::cin >> n;
        coeff = new double[n + 1];
        std::cout << "Please input the coefficients of polynomial(start from the constant):";
        for(int i = 0; i <= n; ++i)
            std::cin >> coeff[i];
    }

    // 得到函数值
    double getValue(double x){
        double value = 0;
        double item = 1;
        for (int i = 0; i<= n; ++i){
            value += coeff[i] * item;
            item *= x;
        }
        return value;
    }

    // 得到导数值
    double getDerivValue(double x){
        double derivValue = 0;
        double item = 1;
        for (int i = 1; i<= n; ++i){
            derivValue += i * coeff[i] * item;
            item *= x;
        }
        return derivValue;
    }

    // distructor
    ~Polynomial(){
        delete[] coeff;
    }
};


#endif