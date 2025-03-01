# Use an official Linux base image
FROM ubuntu:latest

# Set working directory
WORKDIR /app

# Install dependencies
RUN apt-get update && apt-get install -y \
    git \
    g++ \
    cmake \
    make \
    libssl-dev \
    libcrypto++-dev \
    libcrypto++-dev \
    build-essential \
    pkg-config \
    libuv1-dev \
    zlib1g-dev

# Install uWebSockets properly
RUN git clone --recurse-submodules https://github.com/uNetworking/uWebSockets.git && \
    cd uWebSockets && \
    make && make install && \
    cd .. && rm -rf uWebSockets

# Copy source code into the container
COPY . /app

# Compile the C++ code
RUN g++ -std=c++17 -o chat_server main.cpp storage.cpp encryption.cpp websocket_server.cpp -luWS -lssl -lcrypto -lpthread -lz -luv

# Expose the WebSocket server port
EXPOSE 9000

# Run the server
CMD ["./chat_server"]
