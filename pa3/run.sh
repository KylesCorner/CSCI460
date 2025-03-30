#! /bin/bash
rm service.txt
rm results.txt
make clean

touch service.txt
touch results.txt
make

valgrind --leak-check=full --show-leak-kinds=all ./multi-lookup 5 5 serviced.txt results.txt input/names1*.txt

