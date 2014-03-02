#!/bin/sh
#
# ~/.xinitrc
#
# Executed by startx (run your window manager from here)

if [ -d /etc/X11/xinit/xinitrc.d ]; then
  for f in /etc/X11/xinit/xinitrc.d/*; do
    [ -x "$f" ] && . "$f"
  done
  unset f
fi

xscreensaver -no-splash &
~/.statusbar.sh
xrdb -merge ~/.Xresources 
xset +fp ~/.fonts
xset +fp /usr/share/fonts/local &
fc-cache -fv
xset fp rehash &
xinput set-prop "SynPS/2 Synaptics TouchPad" "Synaptics Finger" 50 60 256
synclient RTCornerButton=2
sh ~/.fehbg &

exec /usr/local/bin/dwm

# exec gnome-session
# exec startkde
# exec startxfce4
# ...or the Window Manager of your choice
