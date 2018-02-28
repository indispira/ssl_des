#!/bin/bash

clear
rm log
make && make clean && \
./ft_ssl && echo "" && ./ft_ssl foobar && echo "" && \
echo toto | ./ft_ssl base64 && \
echo toto | base64 && echo "" && \
echo dG90bwo= | ./ft_ssl base64 -d && \
echo dG90bwo= | base64 -d && echo "" && \
echo "foo bar team" | ./ft_ssl des-ecb -a -k ABCDEFGH && \
echo "foo bar team" | openssl des-ecb -a -K 4142434445464748 && echo "" && \
echo "m6zNpGSQDR/P6CZN2jZKVA==" | ./ft_ssl des-ecb -ad -k ABCDEFGH && \
echo "m6zNpGSQDR/P6CZN2jZKVA==" | openssl des-ecb -a -d -K 4142434445464748 && echo "" && \
echo "foobar" | ./ft_ssl des -a -k ABCDEFGH && \
echo "foobar" | openssl des-ecb -a -K 4142434445464748 && echo "" && \
echo "foo bar" | ./ft_ssl des -a -k abcdabcd && \
echo "foo bar" | openssl des-ecb -a -K 6162636461626364 && echo "" && \
echo "foo  bar" | ./ft_ssl des -a -k ABCDEFGH && \
echo "foo  bar" | openssl des-ecb -a -K 4142434445464748 && echo "" && \
echo "Khlwd2/7rYY=" | ./ft_ssl des -ad -k ABCDEFGH && \
echo "Khlwd2/7rYY=" | openssl des-ecb -a -d -K 4142434445464748 && echo "" && \
echo "YZF3QKaabXUwxNg3obhMfw==" | ./ft_ssl des -ad -k abcdabcd && \
echo "YZF3QKaabXUwxNg3obhMfw==" | openssl des-ecb -a -d -K 6162636461626364 && echo "" && \
echo "4MS2QKyOz9KVwxXuw06T7w==" | ./ft_ssl des -ad -k ABCDEFGH && \
echo "4MS2QKyOz9KVwxXuw06T7w==" | openssl des-ecb -a -d -K 4142434445464748 && echo "" && \
echo "Petite phrase de test pour voir si ca marche bien :)" | ./ft_ssl des3 -a -k1 ABCDEFGH -k2 ABCDEFGH -k3 ABCDEFGH && \
echo "b8TZKRNg8csShFmkKTDbF+oF6hbWLpkceaWE3e4sHh+VdZ0BfDNntcjdxivp2R3MvvKSJYUBmAU=" | ./ft_ssl des3 -a -d -k1 ABCDEFGH -k2 ABCDEFGH -k3 ABCDEFGH && echo "" && \
echo "toto" | ./ft_ssl des-cbc -a -k ABCDEFGH -v 0011223344556677 && \
echo "toto" | openssl des-cbc -a -K 4142434445464748 -iv 0011223344556677 && echo "" && \
echo "lJ0cR2/yHX8=" | ./ft_ssl des-cbc -a -k1 ABCDEFGH -k2 ABCDEFGH -k3 ABCDEFGH -d -v 0011223344556677 && \
echo "lJ0cR2/yHX8=" | openssl des-cbc -a -K 4142434445464748 -d -iv 0011223344556677 && echo "" && \
echo "one deep secret" | ./ft_ssl des-cbc -a -k abcdabcd -v 0011223344556677 && \
echo "one deep secret" | openssl des-cbc -a -K 6162636461626364 -iv 0011223344556677 && echo "" && \
echo "zqYWONX68rWNxl7msIdGC67Uh2HfVEBo" | ./ft_ssl des-cbc -ad -k abcdabcd -v 0011223344556677 && \
echo "zqYWONX68rWNxl7msIdGC67Uh2HfVEBo" | openssl des-cbc -a -d -K 6162636461626364 -iv 0011223344556677 && echo "" && \
echo "Test finished"
