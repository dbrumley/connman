#!/bin/bash

if [[ $# -lt 1 ]]; then
  echo usage: $0 \<IMAGE\>
  exit 1
fi

image="$1"

cd ../../
docker build -t $image -f mayhem/dhcp_client/Dockerfile .
docker push $image
cd -

mayhem init --advanced-triage true --project connman --target dhcp-client --cmd '/fuzz_dhcp_client @@' $image
mayhem run .