# syntax=docker/dockerfile:1.6

FROM arm64v8/debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
        git \
        ca-certificates \
        pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src

# Сначала только cmake-файлы — лучше кешируется
COPY CMakeLists.txt ./
COPY http-server/CMakeLists.txt ./http-server/

# Затем исходники
COPY http-server/ ./http-server/

# Конфигурация и сборка (Release)
RUN cmake -S . -B build -G Ninja \
        -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --parallel

EXPOSE 8080

ENTRYPOINT ["/src/build/http-server/http-server"]
