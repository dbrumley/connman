#!/bin/bash

if [[ $# -lt 1 ]]; then
  echo usage: $0 \<IMAGE\>
  exit 1
fi

image="$1"

cd ../../
docker build -t $image -f mayhem/dnsproxy/Dockerfile .
docker push $image
cd -

mayhem init --project connman --target dnsproxy --cmd '/connmand' $image
mayhem run .