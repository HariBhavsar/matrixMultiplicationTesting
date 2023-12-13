#include "naive.cpp"
#include "ijk.cpp"
#include "simd.cpp"
#include "mul.cpp"
#include "threading.cpp"
using namespace std;



int main(int argc, char **argv) {
    if (argc != 2) {
        cout<<"give exactly one argument"<<endl;
        return -1;
    }
    if (argv[1][0] == '0') {
        simd();
    }
    else if (argv[1][0] == '1'){
        naive();
    }
    else if (argv[1][0] == '2') {
        mul();
    }
    else if (argv[1][0] == '3'){
        ijk();
    }
    else if (argv[1][0] == '4') {
        threading();
    }
    else {
        int sum = 0;
        for (int i=0; i<16; i++) {
            sum += i*16*i;
        }
        cout<<sum;
    }
}