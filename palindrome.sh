#!/bin/bash
read -p "Enter the num to check palindrome: " no
original=$no
reversed_no=0;
while [ $no -gt 0 ]; do
	digit=$(( $no % 10 ))
	reversed_no=$(( $reversed_no * 10 + $digit ))
	no=$(( $no / 10))
done
echo "$reversed_no:"
if [ $original -eq $reversed_no ]; then
	echo "no is palindrome" 
else
	echo "not palindrome"
fi
