# AT
AT (activity timer) is a (very) small terminal utility with stopwatch-like features for measuring time. AT's original intended use is to provide some insight on time spent during computer activities such as coding, browsing social media, studying, just waisting time, etc. With title feature implemented for aesthetic purposes.

## Usage
Running `$ at` will display stopwatch in the middle of the terminal while `$ at title` will also display stopwatch in the middle of the terminal but with `title` above the stopwatch. After the user quits AT will display how much time was spent ont `title` activity or if no title is given as an argument just the time.
`at --help` output:
```
at [title]
Runtime: 
    d        : refresh display 
    <space>  : play/pause
    r        : restart
    q        : exit 
```

## Installation
Make sure you have pthread, ncurses & boost timer development library installed. \
On debian like system you can get the dependancies with:
```
$ sudo apt install libpthread-stubs0-dev libncurses6-dev libboost-timer1.67-dev
```

Then install AT with:
```
$ sudo make install
```

And to uninstall:
```
# sudo make uninstall
```
