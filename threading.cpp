#include <iostream>
#include <thread>
#include <immintrin.h>
#include <chrono>
#include "threadMatrix.h"
using namespace std;
    void mulChunks (threadMatrix *t, threadMatrix b,int size,float **a,float ***rowPackets,int threadNumber) {
        __m256 va,vb,vresult;
        __m128 vlow,vhigh,vstore;
        if (threadNumber == 1) {
        for (int i=0; i<size/3; i++) {
            for (int j=0; j<size/3; j++) {
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
                //cout<<"hold"<<endl;
                //cout<<t->a[i][j]<<" ";
            }
            //cout<<endl;
        }
        //cout<<"Printed testing"<<endl;
        //return;
        }
        else if (threadNumber == 2) {
        for (int i=0; i<size/3; i++) {
            for (int j=size/3; j<size*2/3; j++) {
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

        }
        else if (threadNumber == 4) {
        for (int i=0; i<size/3; i++) {
            for (int j=size*2/3; j<size; j++) {
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

        }
        else if (threadNumber == 3) {
        for (int i=size/3; i<size*2/3; i++) {
            for (int j=0; j<size/3; j++) {
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

        }
        else if (threadNumber == 5) {
        for (int i=size/3; i<size*2/3; i++) {
            for (int j=size/3; j<size*2/3; j++) {
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

        }
        else if (threadNumber == 6){
        for (int i=size/3; i<size*2/3; i++) {
            for (int j=size*2/3; j<size; j++) {
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

        }
        else if (threadNumber == 7) {
        for (int i=size*2/3; i<size; i++) {
            for (int j=0; j<size/3; j++) {
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

        }
        else if (threadNumber == 8) {
        for (int i=size*2/3; i<size; i++) {
            for (int j=size/3; j<size*2/3; j++) {
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

        }
        else {
        for (int i=size*2/3; i<size; i++) {
            for (int j=size*2/3; j<size; j++) {
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

        }
    }
threadMatrix* threadMatrix::multiply(threadMatrix b) {
        
        float one[8] __attribute__ ((aligned (32)));
        float two[8] __attribute__ ((aligned (32)));
        float result[8] __attribute__ ((aligned (32)));
        
        if (size != b.size) {
            return nullptr;
        }
        threadMatrix *t = new threadMatrix(size);
        //mulChunks(t,b,size,a,rowPackets,va,vb,vresult,vlow,vhigh,vstore,1);
        //mulChunks(t,b,size,a,rowPackets,va,vb,vresult,vlow,vhigh,vstore,2);
        //mulChunks(t,b,size,a,rowPackets,va,vb,vresult,vlow,vhigh,vstore,3);
        //mulChunks(t,b,size,a,rowPackets,va,vb,vresult,vlow,vhigh,vstore,4);
        thread t1(mulChunks,t,b,size,a,rowPackets,1);
        thread t2(mulChunks,t,b,size,a,rowPackets,2);
        thread t3(mulChunks,t,b,size,a,rowPackets,3);
        thread t4(mulChunks,t,b,size,a,rowPackets,4);
        thread t5(mulChunks,t,b,size,a,rowPackets,5);
        thread t6(mulChunks,t,b,size,a,rowPackets,6);
        thread t7(mulChunks,t,b,size,a,rowPackets,7);
        thread t8(mulChunks,t,b,size,a,rowPackets,8);
        thread t9(mulChunks,t,b,size,a,rowPackets,9);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();
        t9.join();

        //cout<<"Yaha pohoche"<<endl;

        return t;
    }

void foo () {
    cout<<"Hello there"<<endl;
    int sum = 0;
    for (int i=0; i<1000; i++) {
        for (int j=0; j<1000; j++) {
            for (int k=0; k<1000; k++) {
                sum += i*j;
                sum = sum*k;
            }
        }
    }
    cout<<"Sum is "<<sum<<endl;
}

void response (float x) {
    cout<<"General Kenobi"<<x<<endl;
}

using namespace std;
void threading() {

    //cout<<"Enter the dimensions of square matrices"<<endl;
    int n;
    cin >> n;
    threadMatrix u(n);
    //cout<<"Enter matrix 1"<<endl;
    u.takeInputs();
    //u.printMatrix();

    threadMatrix v(n);
    //cout<<"Enter matrix 2"<<endl;
    v.takeInputs();
    //v.printMatrix();
    auto start = chrono::high_resolution_clock::now();
    threadMatrix *mul = u.multiply(v);
    auto end = chrono::high_resolution_clock::now();
    if (mul == nullptr) {
        return;
    }
    auto elapsed = chrono::duration_cast<std::chrono::duration<double>>(end - start);

    //cout<<"Printing result"<<endl;
    //mul->printMatrix(); 
    cout<<elapsed.count()<<endl;

 //   thread t1(foo);
   // thread t2(response,0.25);
    //t1.join();
    //t2.join();
}