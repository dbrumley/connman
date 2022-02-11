FROM ubuntu:20.04 as builder

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y autoconf libtool pkg-config libglib2.0-dev libdbus-1-dev libxtables-dev libgnutls28-dev libreadline-dev make clang

ADD . /connman-src
WORKDIR /connman-src
RUN rm -rf build && mkdir build
RUN ./bootstrap && \
    cd build/ && \
    CC=clang CFLAGS='-fsanitize=memory' LDFLAGS='-fsanitize=memory' ../configure --enable-debug --disable-dependency-tracking && \
    make -j $(grep -c ^processor /proc/cpuinfo) && \
    cp mayhem/fuzz_dhcp /fuzz_dhcp_msan
WORKDIR /
RUN rm -rf /connman-src

ADD . /connman-src
WORKDIR /connman-src
RUN rm -rf build && mkdir build
RUN ./bootstrap && \
    cd build/ && \
    CC=clang CFLAGS='-fsanitize=address' LDFLAGS='-fsanitize=address' ../configure --enable-debug --disable-dependency-tracking && \
    make -j $(grep -c ^processor /proc/cpuinfo) && \
    cp mayhem/fuzz_dhcp /fuzz_dhcp_asan
WORKDIR /
RUN rm -rf /connman-src

ADD . /connman-src
WORKDIR /connman-src
RUN rm -rf build && mkdir build
RUN ./bootstrap && \
    cd build/ && \
    CC=clang ../configure --enable-debug --disable-dependency-tracking && \
    make -j $(grep -c ^processor /proc/cpuinfo) && \
    cp mayhem/fuzz_dhcp /fuzz_dhcp_uninst

FROM ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y libglib2.0-0 && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder /fuzz_dhcp_msan /
COPY --from=builder /fuzz_dhcp_asan /
COPY --from=builder /fuzz_dhcp_uninst /
