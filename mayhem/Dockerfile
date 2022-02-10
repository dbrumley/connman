FROM ubuntu:20.04 as builder

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y autoconf libtool pkg-config libglib2.0-dev libdbus-1-dev libxtables-dev libgnutls28-dev libreadline-dev make

ADD . /connman-src
WORKDIR /connman-src

RUN rm -rf build && mkdir build

RUN ./bootstrap && \
    cd build/ && \
    ../configure --enable-debug --disable-dependency-tracking && \
    make -j $(grep -c ^processor /proc/cpuinfo)

FROM ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y libglib2.0-0 libc6-dbg && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder /connman-src/build/mayhem/fuzz_dhcp /
