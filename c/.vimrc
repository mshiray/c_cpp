" VIM configuration file with cofig param set for c programming

"### Generic config

" VIM configuration file 

set number
set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab

set colorcolumn=80
highlight ColorColumn ctermbg=darkgray

"Show what mode you are currently editing in
set showmode

" Turn syntax highlighting on.
syntax on

"Reacts to the syntax/style of the code you are editing
set smartindent

" Highlight cursor line underneath the cursor horizontally.
set cursorline

" Show file stats.
set ruler

" Security.
set modelines=0


" Status bar.
set laststatus=2


set incsearch        " Search highlights as you type
set hlsearch         " Highlight search matches
set ignorecase       " Search case insensitive

" Async jobs (VIM 8+)

set updatetime=100
set signcolumn=yes


" ### C programming specific config

augroup project
  autocmd!
  autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
augroup END

" add folders to be included in the path
let &path="/include,/data"

" map F8 key to compile and run the current file

map <F8> :w <CR> :!gcc % -o %< && ./%< <CR>
