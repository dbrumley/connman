FROM ubuntu:20.04 as builder

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y autoconf libtool pkg-config libglib2.0-dev libdbus-1-dev libxtables-dev libgnutls28-dev libreadline-dev make libasan5

ADD . /connman-src
WORKDIR /connman-src

RUN rm -rf build && mkdir build

RUN ./bootstrap && \
    cd build/ && \
    CFLAGS='-fsanitize=address' LDFLAGS='-fsanitize=address' ../configure --enable-debug --disable-dependency-tracking && \
    make -j $(grep -c ^processor /proc/cpuinfo) && \
    cp mayhem/fuzz_dhcp /fuzz_dhcp_asan

RUN rm -rf build && mkdir build

RUN ./bootstrap && \
    cd build/ && \
    ../configure --enable-debug --disable-dependency-tracking && \
    make -j $(grep -c ^processor /proc/cpuinfo) && \
    cp mayhem/fuzz_dhcp /fuzz_dhcp_uninst

FROM ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y libglib2.0-0 libasan5 && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder /fuzz_dhcp_asan /
COPY --from=builder /fuzz_dhcp_uninst /
