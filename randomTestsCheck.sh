#!/bin/bash

rm -f testrandom/*

# number of actions in one test
A=$(( $(od -An -N4 -tu4 /dev/random) % 50 + 10 ))
# D number of tests
D=$(( $(od -An -N4 -tu4 /dev/random) % 300 + 10 ))
# D=$(( RANDOM % 5000 ))

gcc -o random_test_generator random_test_generator.c
g++ -o brute brute.cpp

echo "Number of tests to generate: $D"

for (( i = 0; i < $D; i++ )); do
  E=$(( $(od -An -N4 -tu4 /dev/random) % 100000 + 1 ))
  B=$(( (RANDOM % 5) + 5))
  C=$(( (RANDOM % 5) + 5))

  echo "$A $B $C $E" >preq.in
  echo "" >deb.txt

  ./random_test_generator <preq.in >testrandom/rand${i}.in 2>deb.txt

  if [ -s deb.txt ]
  then
    rm -f deb.txt
  else
    rm -f deb.txt
    rm -f rand${i}.in
  fi

  ./brute <testrandom/rand${i}.in 1>testrandom/rand${i}.out 2>testrandom/rand${i}.err

  sleep 0.1
done

./scriptTest.sh main testrandom

rm -f preq.in