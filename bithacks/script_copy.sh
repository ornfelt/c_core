#!/usr/bin/env bash

fileText=$(cat ~/.local/bin/my_scripts/script_help_docs/script_copy.txt)

#set -o noglob
IFS=$'\n' textSplit=($fileText)
#set +o noglob

# Options
#echo "${textSplit[0]}"
opt1="${textSplit[0]}"
opt2="${textSplit[1]}"
opt3="${textSplit[2]}"
opt4="${textSplit[3]}"
opt5="${textSplit[4]}"
opt6="${textSplit[5]}"
opt7="${textSplit[6]}"
opt8="${textSplit[7]}"
opt9="${textSplit[8]}"
opt10="${textSplit[9]}"
opt11="${textSplit[10]}"
opt12="${textSplit[11]}"
opt13="${textSplit[12]}"
opt14="${textSplit[13]}"
opt15="${textSplit[14]}"
opt16="${textSplit[15]}"
opt17="${textSplit[16]}"
opt18="${textSplit[17]}"
opt19="${textSplit[18]}"
opt20="${textSplit[19]}"
opt21="${textSplit[20]}"
opt22="${textSplit[21]}"
opt23="${textSplit[22]}"
opt24="${textSplit[23]}"
opt25="${textSplit[24]}"
opt26="${textSplit[25]}"
opt27="${textSplit[26]}"
opt28="${textSplit[27]}"
opt29="${textSplit[28]}"
#otherOpt=$(echo $fileText | sed -n '1p')
#otherOpt=$(echo $fileText | awk 'NR==1')

# Variable passed to rofi
options="$opt1\n$opt2\n$opt3\n$opt4\n$opt5\n$opt6\n$opt7\n$opt8\n$opt9\n$opt10\n$opt11\n$opt12\n$opt13\n$opt14\n$opt15\n$opt16\n$opt17\n$opt18\n$opt19\n$opt20\n$opt21\n$opt22\n$opt23\n$opt24\n$opt25\n$opt26\n$opt27\n$opt28\n$opt29"

chosen="$(echo -e "$options" | rofi -theme "/home/jonas/.config/rofi/themes/gruvbox/gruvbox-dark2.rasi" -p "Choose a command to copy" -dmenu -selected-row 0)"

case $chosen in
    $opt1)
		#echo "$opt1" | xclip -sel clip
		echo "$opt1" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt2)
		echo "$opt2" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt3)
		echo "$opt3" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt4)
		echo "$opt4" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt5)
		echo "$opt5" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt6)
		echo "$opt6" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt7)
		echo "$opt7" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt8)
		echo "$opt8" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt9)
		echo "$opt9" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt10)
		echo "$opt10" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt11)
		python3 ~/.local/bin/my_scripts/script_help_docs/command_copy3.py
        ;;
    $opt12)
		echo "$opt12" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt13)
		echo "$opt13" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt14)
		echo "$opt14" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt15)
		python3 ~/.local/bin/my_scripts/script_help_docs/command_copy1.py
        ;;
    $opt16)
		python3 ~/.local/bin/my_scripts/script_help_docs/command_copy2.py
        ;;
    $opt17)
		echo "$opt17" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt18)
		echo "$opt18" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt19)
		echo "$opt19" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt20)
		echo "$opt20" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt21)
		echo "$opt21" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt22)
		echo "$opt22" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt23)
		echo "$opt23" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt24)
		echo "$opt24" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt25)
		echo "$opt25" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt26)
		echo "$opt26" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt27)
		echo "$opt27" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
    $opt28)
		python3 ~/.local/bin/my_scripts/script_help_docs/command_copy4.py
        ;;
    $opt29)
		echo "$opt29" | sed "s/\s*#.*//g" | xclip -sel clip
        ;;
esac
