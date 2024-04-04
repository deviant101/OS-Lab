#!/bin/bash
read -p "Enter 1st Number : " num1
read -p "Enter 2nd Number : " num2
read -p "Enter 3rd Number : " num3

result=$((num1 + num2 + num3))

echo "Sum: $result"