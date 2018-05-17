#! /bin/sh

### BEGIN INIT INFO
# Provides:          listen-for-shutdown.py
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
### END INIT INFO


case "$1" in
  start)
    echo "Starting listening-for-shutdown"
    sudo python /usr/local/bin/halt.py &
    ;;
  stop)
    echo "Stopping listening-for-shutdown"
     sudo killall python
    ;;
  *)
    echo "Usage: service listening-for-shutdown {start|stop}"
    exit 1
    ;;
esac

exit 0
