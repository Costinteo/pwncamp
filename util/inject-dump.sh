#!/usr/bin/env bash

BINARY=$1
SOURCE=$2

B64=$(cat $BINARY | base64 --wrap=0)

sed -i "s|REPLACE_ME|$B64|g" $SOURCE
