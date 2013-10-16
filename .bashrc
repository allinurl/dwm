#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
PS1='[\u@\h \W]\$ '

if [ -e /usr/share/terminfo/x/xterm-256color ]; then
        export TERM='xterm-256color'
else
        export TERM='xterm-color'
fi

set_prompt_style () {
    if [ -n "$SSH_CLIENT" ]; then
        PS1="┌─[\[\e[0;35m\]\h\[\e[0m\] \[\e[1;33m\]\w:\[\e[0m\] \[\e[1;31m\]«SSH»\[\e[0m\]]\n└─╼ "
    else
        PS1="┌─[\[\e[35m\]\h\[\e[0m\] \[\e[32m\]\w\[\e[0m\]]\n└─╼ "
    fi
}

set_prompt_style

# set history variables 
unset HISTFILESIZE
HISTSIZE="10000"
HISTCONTROL=ignoreboth:erasedups
# share history across all terminals
PROMPT_COMMAND="history -a; history -c; history -r"
export HISTSIZE PROMPT_COMMAND
