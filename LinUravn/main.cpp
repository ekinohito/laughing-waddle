#include <iostream>
#include <math.h>
#define ANS 0
#define PARAM 1
#define IGN 2

using namespace std;


void OutVec(long double *x, unsigned int n){
    for (unsigned int i = 0; i < n; i++){
        cout << 'X' << i << " = " << x[i] << endl;
    }
}

void OutVec(long double *x, unsigned int whl, string *names, unsigned int *steps, unsigned int mal){
    for (unsigned int i = 0; i < mal; i++){//для каждого из параметров
        for (unsigned int j = 1; j <= steps[i]; j++){//для каждой степени
            cout << names[i] << '^' << j << " = " << x[i] << endl;
        }
    }
    cout << "W0 = " << x[whl - 1] <<endl;
}

void Frag(string format, string **names, unsigned int **steps, unsigned **ignored, unsigned int &mal, unsigned int &whl, unsigned int &ign, unsigned int &ans){
    mal = 0;
    whl = 0;
    ign = 1;
    for (unsigned int i = 0; i < format.length(); i++) {
        if (format.data()[i]=='*') {
            mal++;
            whl++;
            i++;
            while (format.data()[i]=='*'){
                i++;
                whl++;
            }
        }else if(format.data()[i]== '#'){
            ign++;
        }
    }
    whl = 0;
    for (unsigned int i = 0; i < format.length(); i++) {
        if (format.data()[i]=='*') {
            whl++;
        }
    }
    ans = mal;
    string *namesx = new string[mal];
    unsigned int *stepsx = new unsigned int[mal];
    unsigned int *ignoredx = new unsigned int[ign];
    unsigned int u = 0, o = 0;
    for (unsigned int i = 0; i < format.length(); i++) {
        if (format.data()[i]=='*') {
            i++;
            stepsx[u] = 1;
            while (format.data()[i]=='*'){
                i++;
                stepsx[u]++;
            }
            namesx[u]= format.substr(i, format.find(' ', i)- i);
            //cout << namesx[u] << stepsx[u] << endl;
            u++;
        }else if(format.data()[i]== '#'){
            ignoredx[o] = u;
            o++;
        }else if(format.data()[i]== '@'){
            ans = u;
        }
    }
    ignoredx[ign - 1]= UINT32_MAX;
    *names = namesx;
    *steps = stepsx;
    *ignored = ignoredx;
}

long double** InpMat(unsigned int n){
    long double **a = new long double*[n];
    for (unsigned int i = 0; i < n; i++){
        a[i] = new long double[n + 1];
        for (unsigned int j = 0; j <= n; j++){
           cin >> a[i][j];
        }
    }
    return(a);
}

long double** getLearn(unsigned int n, unsigned int mal, unsigned int whl, unsigned int *steps, unsigned int *ignored, unsigned int ans){
    long double *obj = new long double[whl];
    long double **a = new long double*[whl];

    for (unsigned int i = 0; i < whl; i++){
        a[i]= new long double[whl + 1];
        for (unsigned int j = 0; j <= whl; j++){
            a[i][j] = 0;
        }
    }
    for (unsigned int k = 0; k < n; k++){//для каждого объекта
        unsigned int sov = 0;
        long double x, y = 0;
        unsigned int o = 0;
        for (unsigned int i = 0; i < mal; i++){//для каждого из параметров
            if (i == ans){
                cin >> y;
            }
            while (ignored[o] == i){
                cin >> x;
                //cout << "gotcha" << endl;
                o++;
            }
            cin >> x;
            for (unsigned int j = 0; j < steps[i]; j++){//для каждой степени
                obj[sov]= pow(x, j + 1);
                sov++;
            }
        }
        if (mal == ans){
            cin >> y;
        }
        while (ignored[o] == mal){
            cin >> x;
            //cout << "gotcha" << endl;
            o++;
        }
        obj[sov]= 1;
       // OutVec(obj, whl);

        for (unsigned int i = 0; i < whl; i++){
            long double t = obj[i];
            for (unsigned int j = 0; j < whl; j++){
                a[i][j]+= t*obj[j];
            }
            a[i][whl]+= y*t;
            //OutVec(a[i], whl + 1);
        }
    }
    return a;
}

long double* FindKoef(long double **a, unsigned int n){
    long double *x = new long double[n];
    //прямой
    for (unsigned int k = 1; k < n; k++){
        for (unsigned int j = k; j < n; j++){
            long double m = a[j][k - 1] / a[k - 1][k - 1];
            for (unsigned int i = 0; i < n + 1; i++){
                a[j][i] = a[j][i] - m * a[k - 1][i];
            }
        }
    }
    //обратный
    for (unsigned int k = n; k > 0; k--){
        unsigned int i = k - 1;
        x[i] = a[i][n] / a[i][i];
        for (unsigned int c = n - 1; c > i; c--){
            x[i] = x[i] - a[i][c] * x[c] / a[i][i];
        }
    }
    return(x);
}


int main()
{
    string format;
    cout << "Vvedite stroku, zadayushuyu format obuchayuschey viborki\n";
    getline(cin, format);
    string *names;
    unsigned int *steps;
    unsigned int *ignored;
    unsigned int mal, whl, ign, ans;
    Frag(format, &names, &steps, &ignored, mal, whl, ign, ans);
    //cout << steps[0] << endl << mal << endl;
    //cout << ignored[0] << endl;
    unsigned int n;
    cout << "Vvedite kolichestvo elementov obuchayuschey viborki\n";
    cin >> n;
    long double **a = getLearn(n, mal, ++whl, steps, ignored, ans);
    long double *x = FindKoef(a, whl);
    OutVec(x, whl, names, steps, mal);
    //cout << "Hello World!" << endl;
    cin >> n;
    return 0;
}

/*
37 1 0 13.5 8.5 150
32 2 0 13.5 8.5 150
34 3 0 13.5 8.5 150
33 1 0 21 8.5 150
27 2 0 21 8.5 150
30 3 0 21 8.5 150
26 1 0 30 8.5 150
33 1 0 26 8.5 150
31 1 0 21 8.5 100
32 1 0 21 8.5 250
37 1 0 13 8.5 200
39 1 0 13 8.5 200
40 1 0 13 8.5 200
36 1 0 16 8.5 200
36 1 0 16 8.5 200
35 1 0 16 8.5 200
34 1 0 19 8.5 200
34 1 0 19 8.5 200
33 1 0 19 8.5 200
33 1 0 21 8.5 200
33 1 0 21 8.5 200
32 1 0 21 8.5 200
32 1 0 24 8.5 200
32 1 0 24 8.5 200
31 1 0 24 8.5 200
35 1 0 20 8.5 200
32.8 1 0 20 10 200
31.5 1 0 20 12 200
27.8 1 0 20 15 200
33.3 1 0 20 6.5 200
24 4 0 10 15 150
25 4 0 10 15 150
41.5 5 0 15.5 8.5 175
37.5 5 15 15.5 8.5 175
35.5 5 30 15.5 8.5 175
33.5 5 45 15.5 8.5 175
*/
