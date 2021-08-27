## My fork of dwm

dwm is an extremely fast, small, and dynamic window manager for X.

> Requirements
In order to build dwm you need the Xlib header files.

> Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):
```
make clean install
```

> Running dwm
Add the following line to your .xinitrc to start dwm using startx:
```
exec dwm
```

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:
```
DISPLAY=foo.bar:1 exec dwm
```
(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:
```
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
    sleep 1
done &
exec dwm
```

> Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

### How to keep dwm up to date and push to your onw git repo

Most of the info on how to patch/update can be found here
[pathces](https://dwm.suckless.org/customisation/patches_in_git/)

> Remotes
See remotes with:
```
git remote -v
```
origin : suckless's dwm repository
my\_repo : github repo to save my own customization

For customization always pull/push to my\_repo in my\_dwm branch (and sub-branches)
To pull updates pull from origin into the master branch (see next section)

> Branches
master : contains dwm's original binaries as in [suckless](git://git.suckless.org/dwm)
my\_dwm : contains customized binaries - you should only make changes here
Show branches:
```
git branch -vv
```

> Update origin
To update:
```
git checkout master
git pull origin
```
In case of some conflicts:
```
git checkout my\_dwm
git rebase --preserve-merges master
```

> Push/pull changes to/from my\_repo
For example
```
git push my_repo my_dwm
```
\* when the default upstream is set for the current branch you can omit repo and branch name. This can be done with:
    git push --set-upstream my_repo my_dwm

> Patch program

For git users, use -3 to fix the conflict easily:
```
cd dwm
git apply patches/patch.diff
```

For patches formatted with git format-patch:
```
cd dwm
git am patches/patch.diff
```

For tarballs:
```
cd dwm
patch -p1 < patches/patch.diff
```
