#!/bin/bash

set -x 

echo "Installing dependencies for Arcade..."

sudo apt-get update

sudo apt-get install -y \
    build-essential cmake clang-format pkg-config libcriterion-dev \
    libfreetype6-dev \
    libwayland-dev wayland-protocols libxkbcommon-dev \
    libx11-dev libxext-dev libgl1-mesa-dev \
    libasound2-dev libpulse-dev \
    libncurses5-dev libncursesw5-dev \
    liballegro5-dev liballegro-image5-dev liballegro-ttf5-dev liballegro-primitives5-dev

echo "Dependencies installed successfully"