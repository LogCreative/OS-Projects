// Week 1 - Problem 1:
// Romberg's Integral Method

#include "../std_lib_facilities.h"
#include "polynomial.h"

// 显示计算进度
void showProcess(double process){
    cout << "\rCalculating Process:" << setw(4) << process << "%";
    fflush(stdout);
}

/// Romberg 积分类
class Romberg{
private:
    int         n;                          //最大细分数
    double*     h;                          //细分间距矩阵
    double      a;                          //区间起始
    double      b;                          //区间终止
    double**    R;                          //积分矩阵
    int*        BIN_P;                      //2次幂表
    int*        QUA_P;                      //4次幂表
    Polynomial* poly;                       //多项式

    // calculate parameter list h
    void calcList_h(){
        h[0] = b - a;
        for (int i = 1; i <= n; ++i)
            h[i] = h[i-1] / 2;
    }

    void calcListBIN_P(){
        BIN_P[0] = 1;
        for (int i = 1; i < n; ++i)
            BIN_P[i] = BIN_P[i-1] * 2;
    }

    void calcListQUA_P(){
        QUA_P[0] = 1;
        for (int i = 1; i <= n; ++i)
            QUA_P[i] = QUA_P[i-1] * 4;
    }

    double integral(){
        float process;
        // First, calculate R(n,0)
        R[0][0] = h[1] * (poly->getValue(a) + poly->getValue(b));
        for(int i = 1; i <= n; ++i){
            double sum = 0;
            for(int k = 1; k<= BIN_P[i-1]; ++k)
                sum += poly->getValue(a + (2*k - 1)*h[i]);
            R[i][0] = 0.5 * R[i-1][0] + h[i] * sum;
            showProcess(50.0 * i / n);
        }

        // Then, calculate R(n,m)
        for(int i = 1; i<= n; ++i){
            for(int j = 1; j <= i; ++j)
                R[i][j] = R[i][j-1] + 1.0 / (QUA_P[j] - 1) * (R[i][j-1] - R[i-1][j-1]);
            showProcess(50 + 50.0 * i / n);
        }
        putchar('\n');

        return  R[n][n];
    }

public:

    // constructor
    Romberg(Polynomial* polynomial, int maxDivsionNum){
        n = maxDivsionNum;
        h = new double[n+1];

        BIN_P = new int[n];
        calcListBIN_P();

        QUA_P = new int[n+1];
        calcListQUA_P();

        R = new double*[n+1];
        for(int i = 0; i <= n; ++i)
            R[i] = new double[n+1];
        
        poly = polynomial;
    }

    // distructor
    ~Romberg(){
        delete[] h;
        for(int i = 0; i <= n; ++i)
            delete[] R[i];
        delete[] R;
        delete[] BIN_P;
        delete[] QUA_P;
    }

    double Integral(int intervalStart, int intervalEnd){
        a = intervalStart;
        b = intervalEnd;
        calcList_h();
        return integral();
    }
};

int main(){
    Polynomial* poly = new Polynomial();

    int n;
    cout << "Please input the fineness of integral:";
    cin >> n;

    Romberg r1(poly,n);

    double a,b;
    cout << "Please input the start and end of intergral interval:";
    cin >> a >> b;

    cout << r1.Integral(a,b);
    return 0;
}