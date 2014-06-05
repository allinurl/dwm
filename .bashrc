#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=never'
PS1='[\u@\h \W]\$ '

if [ -e /usr/share/terminfo/x/xterm-256color ]; then
        export TERM='xterm-256color'
else
        export TERM='xterm-color'
fi

set_prompt_style () {
	PS1="\[$(tput bold)\]\[$(tput setaf 0)\]\t \[$(tput setaf 1)\][\[$(tput setaf 7)\]\u\[$(tput setaf 1)\]@\[$(tput setaf 1)\]\h \[$(tput setaf 7)\]\W\[$(tput setaf 1)\]]\[$(tput setaf 1)\]\\$ \[$(tput sgr0)\]"
}

set_prompt_style

# set history variables 
unset HISTFILESIZE
HISTSIZE="10000"
HISTCONTROL=ignoreboth:erasedups
# share history across all terminals
PROMPT_COMMAND="history -a; history -c; history -r"
export HISTSIZE PROMPT_COMMAND

