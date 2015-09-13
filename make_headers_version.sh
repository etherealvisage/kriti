#!/bin/sh

rm -rf headers ; mkdir headers

for file in `find src -type f -name '*.h'`; do
    HEADERS_NAME=$(echo $file | sed -e 's/src/headers/')
    mkdir -p $(dirname $HEADERS_NAME)
    echo $file $HEADERS_NAME
    cp $file $HEADERS_NAME
done
