#include <iostream>
#include <xmmintrin.h>
#include <chrono>
#include <iomanip>
using namespace std;
//#define float int
class matrix {

    public:

    float **a;
    int size;

    matrix(int n) {
        size = n;
        float **t = new float *[n];
        for (int i=0; i<n; i++) {
            t[i] = new float [n];
        }
        a = t;
    }

    //~matrix() {
      //  for (int i=0; i<size; i++) {
        //    delete []a[i];
        //}
        //delete []a;
        //cout<<"deleted matrix"<<endl;
    //}

    void takeInputs() {
        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                cin>>a[i][j];
            }
        }
    }

    void printMatrix() {
        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                cout<<fixed<<setprecision(3)<<a[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    matrix *multiply(matrix b) {
        if (size != b.size) {
            return nullptr;
        }
        matrix *t = new matrix(size);

        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                for (int k=0; k<size; k++) {
                    t->a[i][j] += a[i][k]*b.a[k][j];
                }
            }
        }

        //cout<<"Yaha pohoche"<<endl;

        return t;
    }

};

void naive () {
    //cout<<"bruh"<<endl;
    //cout<<"Enter the dimensions of square matrices"<<endl;
    int n;
    cin >> n;
    matrix u(n);
    //cout<<"Enter matrix 1"<<endl;
    u.takeInputs();
    //u.printMatrix();

    matrix v(n);
    //cout<<"Enter matrix 2"<<endl;
    v.takeInputs();
    //v.printMatrix();
    auto start = chrono::high_resolution_clock::now();
    matrix *mul = u.multiply(v);
    auto end = chrono::high_resolution_clock::now();
    if (mul == nullptr) {
        return;
    }
    auto elapsed = chrono::duration_cast<std::chrono::duration<double>>(end - start);

    //cout<<"Printing result"<<endl;
    //mul->printMatrix(); 
    cout<<elapsed.count()<<endl;
}