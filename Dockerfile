# Use an official lightweight C++ image
FROM ubuntu:latest

# Set working directory
WORKDIR /app

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    libssl-dev \
    libcrypto++-dev \
    libz-dev \
    libuv1-dev \
    git \
    wget \
    curl \
    pkg-config \
    build-essential 

# Install uWebSockets
RUN git clone https://github.com/uNetworking/uWebSockets.git && \
    cd uWebSockets && \
    make && make install && \
    cd .. && rm -rf uWebSockets

# Install nlohmann/json
RUN mkdir -p /usr/include/nlohmann && \
    wget -O /usr/include/nlohmann/json.hpp https://github.com/nlohmann/json/releases/latest/download/json.hpp

# Copy project files
COPY . .

# Compile the C++ code
RUN g++ -std=c++17 -o chat_server main.cpp storage.cpp encryption.cpp websocket_server.cpp \
    -luWS -lssl -lcrypto -lpthread -lz -luv

# Expose the WebSocket server port
EXPOSE 9001

# Run the WebSocket server
CMD ["./chat_server"]
