./gen < num.txt > input.txt
./trying 0 < input.txt > outputSIMD.txt
./trying 1 < input.txt > outputNAIVE.txt
./trying 2 < input.txt > outputPar.txt
./trying 3 < input.txt > output.txt
./trying 4 < input.txt > outputThread.txt