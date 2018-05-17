#!/usr/bin/env python

# Import Libraries
import RPi.GPIO as GPIO
import subprocess

# Define GPIO Pin Number
gpioPin=3

# Define GPIO Function
GPIO.setmode(GPIO.BCM)
GPIO.setup(gpioPin, GPIO.IN)
GPIO.wait_for_edge(gpioPin, GPIO.FALLING)

# Command
subprocess.call(['shutdown', '-h', 'now'], shell=False)