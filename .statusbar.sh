#!/bin/bash
# DWM status script
# Colors: 1 = normal, 2 = selected, 3 = urgent

dte(){
dte="$(date +"%a %b %d %Y, %H:%M:%S")"
echo -e "\x02 \x01$dte"
}

bat(){
perc="$(awk 'NR==1 {print +$4}' <(acpi -V))"
online="$(grep "on-line" <(acpi -V))"
if [ -z "$online" ] && [ "$perc" -gt "50" ]; then
  echo -e "\x02 \x01$perc%"
elif [ -z "$online" ] && [ "$perc" -le "49" ]; then
  echo -e "\x02 \x01$perc%"
elif [ -z "$online" ] && [ "$perc" -le "15" ]; then
  echo -e "\x03 $perc%"
elif [ -z "$online" ] && [ "$perc" -le "5" ]; then
  echo -e "\x03 $perc%"
else
  echo -e "\x02 \x01$perc%"
fi
}

vol(){
mute=`amixer get Master | grep "Mono:" | awk '{print $6}'`
if [ $mute == "[on]" ]
  then
    vol=`amixer get Master | grep -m 1 -o '[0-9][0-9]*%'`
      echo -e "\x02 \x01$vol"
  else
    echo -e "\x02   "
fi
}

net(){
essid=`iwgetid | awk -F ':' '{print $2}' | sed -e 's/"//g'`
signal=`awk '/wlan0:/ {print $3}' /proc/net/wireless |sed -e 's/\.//g'`
perc=`echo $[$signal *100 /70]`
echo -e "\x02 \x01$essid $perc"
}

disk(){
#diskinfo=`df -h | awk '/^\/dev\//{print $6 "=" $3 "/" $2}'`
#root=`df -h | grep rootfs | awk '{print $3"/"$2":"$5}'`
root=`df -h | grep \/dev\/sda6 | awk '{print $3}'`
#windows=`df -h | grep media | awk '{print $3"/"$2":"$5}'`
echo -e "\x02 \x01$root"
}

mem(){
mem=`free -m | awk '/cache:/ {printf("%dMB", $3)}'`
echo -e "\x02 \x01$mem"
}

cpu(){
read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
sleep 0.5
read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
temp=`acpi -t | awk '/Thermal 0/ {printf("%d", $4)}'`
echo -e "\x02 \x01$cpu% \x02 \x01$temp°C"
}

backlight(){
backlight=`xbacklight`
echo -e "\x02 \x01$backlight%"
}

# Pipe to status bar
while true ; do
  xsetroot -name "$(cpu) $(mem) $(disk) $(net) $(vol) $(bat) $(backlight) $(dte)"
  sleep 1s
done &
