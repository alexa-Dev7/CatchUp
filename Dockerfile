FROM ubuntu:20.04

# Set non-interactive mode to prevent tzdata prompts
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install required dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    libssl-dev \
    libcrypto++-dev \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Install uWebSockets manually (since it's not in Ubuntu repos)
RUN git clone https://github.com/uNetworking/uWebSockets && \
    cd uWebSockets && \
    make && make install && \
    cd .. && rm -rf uWebSockets

# Copy project files
WORKDIR /app
COPY . .

# Build the project
RUN g++ -std=c++17 -o chat_server main.cpp storage.cpp encryption.cpp websocket_server.cpp -luWS -lssl -lcrypto

# Run the server
CMD ["./chat_server"]
