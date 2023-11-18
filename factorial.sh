#!/bin/bash
read -p "Enter the numver for fact: " no
fact=1
if [[ $no -eq 0 || $no -eq 1 ]]; then
	fact=1
else
	for (( i=1 ; i <= $no ; i++ )); do
		fact=$(( $fact * $i ))
	done
fi

echo " $fact "

factorial() {
	local num=$1;
	if [[ $num -lt 1 ]]; then
		echo 1
	else
		local ans=$(factorial $(( num-1 )) )
		echo $(( num * ans ))
	fi


}
result=$(factorial $no)
echo "$result"
