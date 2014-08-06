syntax on
set nocompatible    " use vim defaults
set ls=2            " allways show status line

set tabstop=2
set shiftwidth=2
" Use spaces instead of tabs
set expandtab

set clipboard=unnamedplus
set hlsearch         " highlight searches
set incsearch        " do incremental searching
set listchars=tab:>-
set nobackup         " do not keep a backup file
set novisualbell     " turn off visual bell
set nowrap
set number           " show line numbers
set ruler            " show the cursor position all the time
set scrolloff=3      " keep 3 lines when scrolling
set showcmd          " display incomplete commands
set tabpagemax=50
set ttyfast      " don't lag…
set visualbell t_vb= " turn off error beep/flash
set wildmenu         " enhanced tab-completion shows all matching cmds in a popup menu
set wildmode=list:longest,full  " full completion options

let g:loaded_matchparen= 1
set t_Co=256
colorscheme hybrid

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Files, backups and undo
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Turn backup off, since most stuff is in SVN, git et.c anyway...
set nobackup
set nowb
set noswapfile

"autocmd BufRead,BufNewFile * syn match parens /[(){}]/ | hi parens ctermfg=cyan

autocmd FileType css setlocal shiftwidth=4 tabstop=4 expandtab
autocmd FileType javascript setlocal shiftwidth=3 tabstop=3 expandtab
