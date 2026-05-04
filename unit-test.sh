#!/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi


# check nmap on its own, no sudo, no argument, expected output : help


# TODO should it?
# check nmap without the admin rights,  expected output : must run as sudo


# check for all of the different flags, and their expected output with wrong and right syntax
