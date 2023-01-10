## My fork of dwm

dwm is an extremely fast, small, and dynamic window manager for X.

#### Requirements

In order to build dwm you need the Xlib header files.

#### Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):
```
make clean install
```

#### Running dwm

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

#### Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

### How to keep dwm up to date and push to your onw git repo

Most of the info on how to patch/update can be found here
[patches](https://dwm.suckless.org/customisation/patches_in_git/)

#### Remotes

See remotes with:
```
git remote -v
```
origin : suckless's dwm repository\
my\_repo : github repo to save my own customization

For customization always pull/push to my\_repo in my\_dwm branch (and sub-branches)\
To pull updates pull from origin into the master branch (see next section)

#### Branches

master : contains dwm's original binaries as in <git://git.suckless.org/dwm>\
my\_dwm : contains customized binaries - you should only make changes here\
Show branches:
```
git branch -vv
```

#### Update origin

To update:
```
git checkout master
git pull origin
```

In case of some conflicts:
```
git checkout my_dwm
git rebase --preserve-merges master
```

#### Push/pull changes to/from my\_repo

For example
```
git push my_repo my_dwm
```

\* when the default upstream is set for the current branch you can omit repo and branch name. This can be done with:`
```
git push --set-upstream my_repo my_dwm
```

#### Patch

It is good practice to create a new branch for the patch to try fron the branch of the last implemented patch:
```
git checkout -b patch_name-patch last_patch-patch
```

For git users, use -3 to fix the conflict easily:
```
cd dwm
patch -p1 patches/patch.diff
```

Most patches change config.def.h, copy these changes in config.h with vimfidd:
```
vimdiff config.def.h config.h
```
do: obtain change\
dp: put change\
]c: next change\
[c: prev change\

To keep the patch, commit changes locally and merge changes in the my\_dwm branch.
```
git checkout my_dwm
git merge last_patch-patch
```

### Patches

- swallow
    - `dwm-swallow-20201211-61bb8b2.diff`
- actualfullscreen
    - `dwm-actualfullscreen-20191112-cb3f58a.diff`
- Colored emojis support with libxft-bgra
- restarttsig
    - `dwm-restartsig-20180523-6.2.diff`
- xresources
    - `dwm-xresources-6.2.diff`
- statuscmd
    - `dwm-statuscmd-20210405-67d76bd.diff`
- vanity-gaps
    - `dwm-vanitygaps-20190508-6.2.diff`
- [statuscolors](https://github.com/witty91/dwm-patches)
    - `dwm-statuscolors-statuscmd-signal-6.2.diff`
- systray
    - `dwm-systray-20200914-61bb8b2.diff`
- alpha
    - `dwm-alpha-20201019-61bb8b2.diff`

**NOTE**: since `restarttsig` and `statuscolors` use the same range of escape characters
(ASCII < 32), this range was split into 16 characters for signals (max 16 dwmblocks) and 16
for colorschemes, the latter accessible from `\x11` forward.
