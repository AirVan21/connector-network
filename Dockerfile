# Use an official Ubuntu base image
FROM ubuntu:24.04

# Set environment variables to avoid interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install required tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    clang \
    clangd \
    libstdc++-13-dev \
    git \
    libboost-all-dev \
    libssl-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /connector-network

# Set the default command
CMD ["bash"]
