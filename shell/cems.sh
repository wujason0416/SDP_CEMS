#!/bin/bash
# /etc/init.d/CEMS
 
### BEGIN INIT INFO
# Provides: embbnux
# Required-Start: $remote_fs $syslog
# Required-Stop: $remote_fs $syslog
# Default-Start: 2 3 4 5
# Default-Stop: 0 1 6
# Short-Description: SPD_CEMS initscript
# Description: 此程式用來管理CEMS資訊連網服務 SPD CEMS Service
# Authoried by: Jason Wu @ Mactronic Technology Ltd.
### END INIT INFO
 
case "$1" in
    start)
        echo "Starting SPD CEMS Service"
        sudo python /usr/cems/SPD_cems_mac.py &
        ;;
    stop)
        echo "Stopping SPD CEMS Service"
        #killall ledblink.py
        kill $(ps aux | grep -m 1 'python /usr/cems/SPD_cems_mac.py' | awk '{ print $2 }')
        ;;
    *)
        echo "Usage: service SPD CEMS start|stop"
        exit 1
        ;;
esac
exit 0

