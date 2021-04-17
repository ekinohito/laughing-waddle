#include <iostream>
#include <math.h>

using namespace std;

void grdnt(double* Xmas, double* Tmas, int N, double a, double b, double c, double* da, double* db, double* dc){
    *da = 0;
    *db = 0;
    *dc = 0;
    for(int i = 0; i < N; i++){
        double t = a*Xmas[i]*Xmas[i] + b*Xmas[i] + c - Tmas[i];
        *da += Xmas[i]*Xmas[i]*t;
        *db += Xmas[i]*t;
        *dc += t;
    }
}

double shag(double* Xmas, double* Tmas, int N, double a, double b, double c, double da, double db, double dc){
    double chis = 0.0, znam = 0.0;
    for(int i = 0; i < N; i++){
        double temp = da*Xmas[i]*Xmas[i] + db*Xmas[i] + dc;
        znam += temp*temp;
        chis -= temp*(a*Xmas[i]*Xmas[i] + b*Xmas[i] + c - Tmas[i]);
    }
    return(chis/znam);
}

int main(){
    int N;
    cin >> N;

    /*
    пример ввода
    который находит a = 2; b = -5; c = 8
    4
    1 3 5 7
    5 11 33 71
    */

    double Xmas[20];
    for(int i = 0; i < N; i++){
        cin >> Xmas[i];
    }

    double Tmas[20];
    for(int i = 0; i < N; i++){
        cin >> Tmas[i];
    }

    double a = 0.0, b = 0.0, c = 0.0, res = 1.0;
    double da = 1.0, db = 1.0, dc = 1.0;
    /*
    for(int j = 1; j < 10000; j++){
        grdnt(Xmas, Tmas, N, a, b, c, &da, &db, &dc);
        res = shag(Xmas, Tmas, N, a, b, c, da, db, dc);
        da *= res;
        db *= res;
        dc *= res;
        a += da;
        b += db;
        c += dc;
    }
    */
    const double eps = 1e-9;
    while((abs(da) > eps)||(abs(db) > eps)||(abs(dc) > eps)){
        grdnt(Xmas, Tmas, N, a, b, c, &da, &db, &dc);
        res = shag(Xmas, Tmas, N, a, b, c, da, db, dc);
        da *= res;
        db *= res;
        dc *= res;
        a += da;
        b += db;
        c += dc;
    }

    cout << da << ' ' << db << ' ' << dc << endl;
    cout << a << ' ' << b << ' ' << c << endl;

    res = 0;
    for(int i = 0; i < N; i++){
        double t = a*Xmas[i]*Xmas[i] + b*Xmas[i] + c - Tmas[i];
        res += t*t;
    }
    res /= 2;
    cout << res << endl;
    /*
    cin >> a >> b >> c;

    grdnt(Xmas, Tmas, N, a, b, c, &da, &db, &dc);
    cout << da << ' ' << db << ' ' << dc << endl;
    res = shag(Xmas, Tmas, N, a, b, c, da, db, dc);
    cout << res << endl;
    cout << (da * res) << ' ' << (db * res) << ' ' << (dc * res) << endl;
    */
}

/*int main()
{
    int N;
    cin >> N;

    double Xmas[20];
    for(int i = 0; i < N; i++){
        cin >> Xmas[i];
    }

    double Tmas[20];
    for(int i = 0; i < N; i++){
        cin >> Tmas[i];
    }

    double a = 0.0, b = 0.0, c = 0.0, res = 0.0;
    double shag1 = 0.0000001;

    for(int shag = 1; shag < 10000000; shag++){
        double da = 0.0, db = 0.0, dc = 0.0;

        for(int i = 0; i < N; i++){
            double t = a*Xmas[i]*Xmas[i] + b*Xmas[i] + c - Tmas[i];
            da += Xmas[i]*Xmas[i]*t;
            db += Xmas[i]*t;
            dc += t;
        }

        double mod = sqrt(da*da + db*db + dc*dc);
        da = da/mod;
        db = db/mod;
        dc = dc/mod;

        da = da*shag1;
        db = db*shag1;
        dc = dc*shag1;

        a -= da;
        b -= db;
        c -= dc;


    }
    for(int i = 0; i < N; i++){
        double t = a*Xmas[i]*Xmas[i] + b*Xmas[i] + c - Tmas[i];
        res += t*t;
    }
    res /= 2;
    cout << res;
    //cout << "Hello World!" << endl;
    return 0;
}*/
