" VIM configuration file with cofig param set for c programming

set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab

set colorcolumn=110
highlight ColorColumn ctermbg=darkgray

augroup project
  autocmd!
  autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
augroup END

" add folders to be included in the path
let &path="/include,/data"

" map F8 key to compile and run the current file

map <F8> :w <CR> :!gcc % -o %< && ./%< <CR>
