# Matrix-Factorization-with-attributes

Firstly compile the MF.c by gcc MF.c -o MF
Rename the Movielens 100K dataset to udata.txt

all but n test:
./MF all_but_base.txt all_but_test.txt 5 all-but y KNN
./MF all_but_base.txt all_but_test.txt 15 all-but y KNN
...


given n test:
./MF all_but_base.txt all_but_test.txt 5 given y KNN
./MF all_but_base.txt all_but_test.txt 10 given y KNN
...

simple MF test on u1.base and u1.test
./MF u1.base u1.test 20 n y KNN
