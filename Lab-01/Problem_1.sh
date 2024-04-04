#!/bin/bash

cat FROM > TO
rm FROM
mv TO ./FINAL_FILE
read -p "Search : " Name
grep Farrukh ./FINAL_FILE