g++ gen.cpp -o gen
g++ trying.cpp -o4 -fopt-info-optall-optimized -ftree-vectorize -fopenmp -mavx -o trying
./gen > input.txt
echo "Input has been sent"
./trying 0 < input.txt > outputSIMD.txt
echo "simd done"
./trying 1 < input.txt > outputNAIVE.txt
echo "naive done"
./trying 2 < input.txt > outputPar.txt
echo "par done"
./trying 3 < input.txt > output.txt
echo "ijk done"
./trying 4 < input.txt > outputThread.txt