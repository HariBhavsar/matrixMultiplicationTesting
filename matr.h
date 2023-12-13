#include <iostream>
#include <xmmintrin.h>
using namespace std;
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
                cout<<a[i][j]<<" ";
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