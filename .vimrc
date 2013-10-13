syntax on
set nocompatible    " use vim defaults
set ls=2            " allways show status line

set tabstop=4
set shiftwidth=4
set expandtab

set hlsearch         " highlight searches
set incsearch        " do incremental searching
set nobackup         " do not keep a backup file
set novisualbell     " turn off visual bell
set nowrap
set number           " show line numbers
set ruler            " show the cursor position all the time
set scrolloff=3      " keep 3 lines when scrolling
set showcmd          " display incomplete commands
set tabpagemax=50 
set visualbell t_vb= " turn off error beep/flash
set listchars=tab:>-

let g:loaded_matchparen= 1
set t_Co=256
colorscheme slate 


"autocmd BufRead,BufNewFile * syn match parens /[(){}]/ | hi parens ctermfg=cyan

"set cinkeys=0{,0},:,0#,!,!^F
"set softtabstop=2
"set tabstop=4       " numbers of spaces of tab character
"set shiftwidth=4    " numbers of spaces to (auto)indent

"set cindent
"set smartindent
"set autoindent

autocmd FileType css setlocal shiftwidth=4 tabstop=4 expandtab
autocmd FileType javascript setlocal shiftwidth=3 tabstop=3 expandtab
