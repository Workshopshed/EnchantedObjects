#! /bin/sh
# Install Tools
opkg update
opkg install distribute
opkg install python-openssl
easy_install pip
# Install Python Libraries
pip install requests
