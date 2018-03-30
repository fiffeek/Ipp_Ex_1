#!/bin/bash

if [ -z $1 ]
then
  clear
  echo "------------"
  echo "scriptTest.sh"
  echo "------------"
  echo "./script_test <prog> <dir> <valgrind_flag>"
  echo "where <prog> = program and <dir> = output directory"
  echo "------------"
  echo "runs every *.in file in /<dir> on <prog>"
  echo "and checks the output files with all *.out and *.err in /<dir>"
  echo "------------"
  echo "if <valgrind_flag> is set to -nonval it does not run memory checks"
  echo "otherwise it searches for memory leaks"
  echo "------------"
else
  failed=0
  count=0

  echo "Testing in directory /$2."

  for f in $2/*.in; do
    alreadyFailed=0
    (( count++ ))

    printf "Test [${count}] from [${f::-3}]: "
    echo "" >temp.out
    echo "" >temp.err
    echo "" >valgrind.txt

    if [ "$3" == "-val" ]; then
      valgrind --error-exitcode=15 --leak-check=full \
      --show-leak-kinds=all --errors-for-leak-kinds=all -q \
      --log-file="valgrind.txt" ./$1 <${f} 1>temp.out 2>temp.err
    else
      ./$1 <${f} 1>temp.out 2>temp.err
    fi

    CODE=$?

    if [ "$(diff -q temp.out ${f%.in}.out)" != "" ] \
        || [ "$(diff -q temp.err ${f%.in}.err)" != "" ]; then
      (( failed++ ))
      (( alreadyFailed++ ))
      printf "\e[31m[failed]\e[39m with return code = \e[94m[${CODE}]\e[39m."
    else
      printf "\e[32m[passed]\e[39m with return code = \e[94m[${CODE}]\e[39m."
    fi

    if [ "$3" != "-val" ]; then
      echo ""
    fi

    if [[ $(tail --lines=1 valgrind.txt) != "" ]] && [ "$3" == "-val" ]; then
      echo -e " Valgrind returned \e[91m[ERROR]\e[39m."
      if [ $alreadyFailed == 0 ]; then
        (( failed++ ))
      fi
    elif [ "$3" == "-val" ]; then
      echo -e " Valgrind returned \e[92m[NO ERRORS]\e[39m".
    fi
  done

  echo ""
  echo "Tests: [${count}]"
  echo "Failures: [${failed}]"

  rm -f valgrind.txt temp.out temp.err
fi
