# lock
```
================================================
||                                            ||
||                  WELCOME                   ||
||                     TO                     ||
||                                            ||
||                 .--------.                 ||
||                / .------. \                ||
||               / /        \ \               ||  
||               | |        | |               ||
||              _| |________| |_              ||
||            .' |_|        |_| '.            ||
||            '._____ ____ _____.'            ||
||            |     .'____'.     |            ||
||            '.__.'.'    '.'.__.'            ||
||            '.__  |      |  __.'            ||
||            |   '.'.____.'.'   |            ||
||            '.____'.____.'____.'            ||
||            '.________________.'            ||
||                                            ||
||                    LOCK                    ||
||                                            ||
================================================
      Conveniently and safely store links, 
         passwords, and sensitive data
             through user password
                 authentication
```
# About
Store any sensitive data (i.e. links, passwords, emails, etc) through your Bash shell interpreter. Can access sensitive data using any shell text editor of choice (i.e. Emacs, Vim, or Nano)

Syntax: `lock [-evnh]`

Options:

a`Print all sensitive data to console`

e`Access sensitive data using Emacs`

v`Access sensitive data using Vim`

n`Access sensitive data using Nano`

h`Show help page`

# To Do:

- add decryption using GPG or openssl
  - currently uses Caeser Cipher using large prime number
  - modify chmod permissions as second layer of security
- create Master software that allows for changing / recovering passwords  
