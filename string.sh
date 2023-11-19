#!/bin/bash
string="Samarth"
string1=""
for (( i=${#string} - 1 ;i >= 0 ; i-- )); do
	string1+="${string:i:1}"
done
echo "${string1}"

reverse() {
	local input="$1"
	local ans=""
	for (( i=${#input} - 1 ; i >= 0 ; i-- )); do
		ans+="${input:i:1}"
	done
	echo "$ans"
}
original="samarth"
reversed=$(reverse "$original" )

echo "reversed : $reversed"
