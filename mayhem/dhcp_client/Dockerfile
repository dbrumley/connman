FROM --platform=linux/amd64 ubuntu:20.04 as builder

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y autoconf libtool pkg-config libglib2.0-dev libdbus-1-dev libxtables-dev libgnutls28-dev libreadline-dev make clang

ADD . /connman-src
WORKDIR /connman-src
RUN rm -rf build && mkdir build
RUN ./bootstrap && \
    cd build/ && \
    CC=clang ../configure --enable-debug --disable-dependency-tracking && \
    make -j $(grep -c ^processor /proc/cpuinfo) && \
    cp mayhem/dhcp_client/fuzz_dhcp_client /fuzz_dhcp_client_uninst

FROM --platform=linux/amd64 ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y libglib2.0-0 libc6-dbg && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder /fuzz_dhcp_client_uninst /
