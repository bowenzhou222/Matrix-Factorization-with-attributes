# Matrix-Factorization-with-attributes

Datasets can be downloaded from MovieLens<br />

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

