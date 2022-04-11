#!/bin/sh
#!/bin/bash

answer=$(cat ./ip_filter.tsv | ./ip_filter | md5sum)
echo $answer
md5="24e7a7b2270daee89c64d3ca5fb3da1a"

if [ "$answer" -ne "$md5" ]
    exit -1
exit 1
