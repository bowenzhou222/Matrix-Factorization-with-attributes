# Matrix-Factorization-with-attributes

Firstly compile the MF.c by gcc MF.c -o MF<br />
Rename the Movielens 100K dataset to udata.txt<br />

all but n test:<br />
./MF all_but_base.txt all_but_test.txt 5 all-but y KNN<br />
./MF all_but_base.txt all_but_test.txt 15 all-but y KNN<br />
...


given n test:<br />
./MF all_but_base.txt all_but_test.txt 5 given y KNN<br />
./MF all_but_base.txt all_but_test.txt 10 given y KNN<br />
...

simple MF test on u1.base and u1.test<br />
./MF u1.base u1.test 20 n y KNN<br />
