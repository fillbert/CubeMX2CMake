#!/bin/bash

# Version of Segger J-Link
JLINK_VER=V792c

# Version of cross-compilation gcc-arm-none-eabi toolchain
GCC_ARM_NONE_EABI_VER=10.3-2021.10

# Get the path of this script
SCRIPT_DIR="$(dirname "$(realpath "$0")")"

# Local path to JLink deb file
LOCAL_JLINK_DEB=${SCRIPT_DIR}/JLink_Linux_${JLINK_VER}_x86_64.deb

# Link to cross-compilation gcc-arm-none-eabi toolchain
URL_GCC_ARM_NONE_EABI=https://developer.arm.com/-/media/Files/downloads/gnu-rm/${GCC_ARM_NONE_EABI_VER}/gcc-arm-none-eabi-${GCC_ARM_NONE_EABI_VER}-x86_64-linux.tar.bz2

# Install some prerequisites and nice-to-haves
sudo apt-get clean
sudo apt-get update -qy
sudo apt-get upgrade -qy
sudo apt-get install -qy \
    curl \
    wget \
    build-essential \
    gcc-multilib \
    g++-multilib\
    git \
    python3 \
    python3-pip \
    nano \
    zip \
    unzip \
    libxcursor1 \
    libxrandr2 \
    libxfixes3 \
	gdb
	
# fix gzip for WSL 22.04LTS
echo -en '\x10' | sudo dd of=/usr/bin/gzip count=1 bs=1 conv=notrunc seek=$((0x189))

# Requared for SEGGER DEBUG
sudo apt-get install -qy libncurses5	
# Install Python modules
python3 -m pip install --upgrade pip setuptools wheel
pip3 install --upgrade kconfiglib~=14.1.0 cmake~=3.25
pip3 install --update cmake kconfiglib

# Install cross-compilation gcc-arm-none-eabi toolchain
curl  -fSL -o ~/gcc-arm-none-eabi-tools.tar  ${URL_GCC_ARM_NONE_EABI}
sudo  tar -xvf ~/gcc-arm-none-eabi-tools.tar --directory /opt
rm -f gcc-arm-none-eabi-tools.tar

# Install Segger J-Link 
wget --post-data 'accept_license_agreement=accepted&non_emb_ctr=confirmed&submit=Download+software' https://www.segger.com/downloads/jlink/JLink_Linux_${JLINK_VER}_x86_64.deb
sudo apt-get install -qy ${LOCAL_JLINK_DEB}
sudo apt-get -qy --fix-broken install 
rm -f ${LOCAL_JLINK_DEB}

# export all pathes
export PATH="$HOME/.local/bin":$PATH
export PATH="/usr/bin":$PATH
export PATH="/opt/gcc-arm-none-eabi-${GCC_ARM_NONE_EABI_VER}/bin":$PATH


