#include <iostream>
#include <iomanip>
using namespace std;
#include <immintrin.h>
class threadMatrix {
    public:
    float **a;

    float ***rowPackets;
    float ***colPackets;

    int size;
    threadMatrix(int n) {
        size = n;
        float **t = new float *[n];
        float ***u = new float **[n];
        float ***v = new float **[n];
        for (int i=0; i<n; i++) {
            float **f = new float *[n/8];
            float **f2 = new float *[n/8];
            
            for (int j=0; j<n/8; j++) {
                float *bruh = new float [8];
                f[j] = bruh;
                float *tmp = new float [8];
                f2[j] = tmp;
            }

            u[i] = f;
            v[i] = f2;
        }

        rowPackets = u;
        colPackets = v;

        for (int i=0; i<n; i++) {
            t[i] = new float [n];
        }
        a = t;
    }

    void orgMatrix() {
        for (int i=0; i<size; i++) {
            for (int j=0; j<size/8; j++) {
                int tmp = j*8;
                for (int k=0; k<8; k++) {
                    rowPackets[i][j][k] = a[i][tmp+k];
                }
            }
        }
        for (int i=0; i<size; i++) {
            for (int j=0; j<size/8; j++) {
                int tmp = j*8;
                for (int k=0; k<8; k++) {
                    colPackets[i][j][k] = a[tmp+k][i];
                }
            }
        }
    }

    void takeInputs() {
        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                cin>>a[i][j];
            }
        }
        orgMatrix();
    }

    void printMatrix() {
        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                cout<<fixed<<setprecision(3)<<a[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    threadMatrix *transpose () {
        threadMatrix* t = new threadMatrix(size);
        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                t->a[j][i] = a[i][j];
            }
        }
        return t;
    }


    threadMatrix *multiply(threadMatrix b);
};
