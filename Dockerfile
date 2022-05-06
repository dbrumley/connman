FROM --platform=linux/amd64 ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y libglib2.0-0 libdbus-1-3 libxtables12 libgnutls30 libreadline5 libasan5 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

ADD ./src/connmand /

