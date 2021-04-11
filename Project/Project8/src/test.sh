make
./vmm addresses.txt > test.txt
diff test.txt correct.txt -s