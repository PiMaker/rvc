#!/bin/sh

echo "Configuring network..."

# Start loopback interface, it will auto-assign 127.0.0.1/8 as IP
ip link set up lo

PLID=$(cat /sys/kernel/rvc/player_id)
echo "Player ID: $PLID"
PLID=$(( (PLID + 1) % 255 ))
echo "Network ID: $PLID"

# Configure rvcnet for external networking
ip link set dev rvcnet up
ip addr add "10.0.0.$PLID/24" dev rvcnet

echo "Network state:"
ip addr show
