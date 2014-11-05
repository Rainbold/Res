#! /usr/bin/expect -f
set timeout 60
spawn /home/ssh1 | player15@172.18.3.213
expect "password: $"
send "RainbowAppleFlutterPinkie\n"
interact
