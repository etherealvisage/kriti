#!/bin/sh

rm -rf headers ; mkdir headers

for file in `find src -type f -name '*.h' -o -name '*.hpp'`; do
    HEADERS_NAME=$(echo $file | sed -e 's/src/headers/')
    mkdir -p $(dirname $HEADERS_NAME)
    echo $file $HEADERS_NAME
    ln $file $HEADERS_NAME
    chmod 644 $HEADERS_NAME
done
