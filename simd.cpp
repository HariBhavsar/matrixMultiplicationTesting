#include <immintrin.h> // Need this in order to be able to use the AVX "intrinsics" (which provide access to instructions without writing assembly)
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std;

class simdMatrix {
    public:
    float **a;

    float ***rowPackets;
    float ***colPackets;

    int size;
    simdMatrix(int n) {
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

    simdMatrix *transpose () {
        simdMatrix* t = new simdMatrix(size);
        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                t->a[j][i] = a[i][j];
            }
        }
        return t;
    }

    simdMatrix* multiply(simdMatrix b) {
        
        float one[8] __attribute__ ((aligned (32)));
        float two[8] __attribute__ ((aligned (32)));
        float result[8] __attribute__ ((aligned (32)));
        __m256 va,vb,vresult;
        __m128 vlow,vhigh,vstore;
        
        if (size != b.size) {
            return nullptr;
        }
        simdMatrix *t = new simdMatrix(size);

        //simdMatrix *c = b.transpose();
        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                for (int k=0; k<size; k+=8) {
                    if (k + 8 >= size) {
                        for (int l=k; l<size; l++) {
                            t->a[i][j] += a[i][l]*b.a[l][j];
                        }
                        // normal
                    }
                    else {
                        //simd

                        va = _mm256_loadu_ps(rowPackets[i][k/8]); //one[i] will 
                        vb = _mm256_loadu_ps(b.colPackets[j][k/8]);
                        vresult = _mm256_mul_ps(va, vb);
                        
                        vlow = _mm256_extractf128_ps(vresult, 0);
                        vhigh = _mm256_extractf128_ps(vresult, 1);

                        vstore = _mm_add_ps(vlow,vhigh);
                        vstore = _mm_hadd_ps(vstore,vstore);
                        vstore = _mm_hadd_ps(vstore,vstore);
                        t->a[i][j] += _mm_cvtss_f32(vstore);
                    }
                }
            }
        }


        //cout<<"Yaha pohoche"<<endl;

        return t;
    }

};

void simd() {

    cout<<"Enter the dimensions of square matrices"<<endl;
    int n;
    cin >> n;
    simdMatrix u(n);
    cout<<"Enter matrix 1"<<endl;
    u.takeInputs();
    //u.printMatrix();

    simdMatrix v(n);
    cout<<"Enter matrix 2"<<endl;
    v.takeInputs();
    //v.printMatrix();
    auto start = chrono::high_resolution_clock::now();
    simdMatrix *mul = u.multiply(v);
    auto end = chrono::high_resolution_clock::now();
    if (mul == nullptr) {
        return;
    }
    auto elapsed = chrono::duration_cast<std::chrono::duration<double>>(end - start);

    cout<<"Printing result"<<endl;
    mul->printMatrix(); 
    cout<<"Number of cycles is "<<elapsed.count()<<endl;
    
}