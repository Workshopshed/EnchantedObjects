#! /bin/sh
# Install Tools
opkg update
opkg install distribute
opkg install python-openssl
opkg install python-curl 

easy_install pip

# Install Python Libraries
pip install parse

