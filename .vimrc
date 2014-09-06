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
set nomodeline       " disable mode lines (security measure)
set novisualbell     " turn off visual bell
set nowrap
set number           " show line numbers
set ruler            " show the cursor position all the time
set scrolloff=3      " keep 3 lines when scrolling
set shortmess+=I                " hide the launch screen
set showcmd          " display incomplete commands
set showmode         " always show what mode we're currently editing in
set tabpagemax=50
set title            " make your xterm inherit the title from Vim
set ttyfast          " don't lag…
set visualbell t_vb= " turn off error beep/flash
set wildmenu         " enhanced tab-completion shows all matching cmds in a popup menu
set wildmode=list:longest,full  " full completion options

let g:loaded_matchparen= 1
set t_Co=256
colorscheme hybrid

" Toggle show/hide invisible chars
nnoremap <leader>i :set list!<cr>

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Files, backups and undo
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Turn backup off, since most stuff is in SVN, git et.c anyway...
set nobackup         " do not keep a backup file
set noswapfile
set nowritebackup 

set directory=~/.vim/.tmp,~/tmp,/tmp
                                " store swap files in one of these directories
                                " (in case swapfile is ever turned on)

"autocmd BufRead,BufNewFile * syn match parens /[(){}]/ | hi parens ctermfg=cyan

set statusline=\ %{HasPaste()}%<%-15.25(%f%)%m%r%h\ %w\ \ 
set statusline+=\ \ \ [%{&ff}/%Y] 
set statusline+=\ \ \ %<%20.30(%{hostname()}:%{CurDir()}%)\ 
set statusline+=%=%-10.(%l,%c%V%)\ %p%%/%L

function! CurDir()
    let curdir = substitute(getcwd(), $HOME, "~", "")
    return curdir
endfunction

function! HasPaste()
    if &paste
        return '[PASTE]'
    else
        return ''
    endif
endfunction

" \g generates the header guard
map <leader>g :call IncludeGuard()<CR>
fun! IncludeGuard()
   let basename = substitute(bufname(""), '.*/', '', '')
   let guard = '_' . substitute(toupper(basename), '\.', '_', "H")
   call append(0, "#ifndef " . guard)
   call append(1, "#define " . guard)
   call append( line("$"), "#endif // for #ifndef " . guard)
endfun

" Strip trailing whitespace
map <leader>w :call StripTrailingWhitespace()<CR>
fun! StripTrailingWhitespace()
    " Don't strip on these filetypes
    if &ft =~ 'markdown'
        return
    endif
    %s/\s\+$//e
endfun

set encoding=utf-8                                  
set termencoding=utf-8
set fileencoding=utf-8
set fileencodings=ucs-bom,utf-8,big5,gb2312,latin1
