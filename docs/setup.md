# How to Setup the Project

## For Develpment

Update Ubuntu repositories and upgrade.

```shell
sudo apt update
sudo apt upgrade
```

For the **terminal**, install: `zsh` and `oh-my-zsh`. `zsh` plugins: `zsh-autosuggestions` and `zsh-syntax-highlighting`. Add both to `.zshrc`.

Install utilities: `sudo apt install git vim`.

An **IDE**: `VSCode`

**GitHub**

Generate SSH Key `ssh-keygen -t ed25519 -C "email@test.com"`, copy it `cat .ssh/id_ed25519.pub` and add it to GitHub account.

Clone the project.

**C stuff**

`sudo apt install build-essential gdb pkg-config`

### Raylib

The following commands are from the Github `raylib` documentation as an example for the process. Check before running them in the GitHub documentation for any updates.

```shell
# install library dependencies
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
# build the project
git clone --depth 1 https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED
sudo make install RAYLIB_LIBTYPE=SHARED
```

For other building options check [this link](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#build-raylib-using-make).

### Git Configuration

```shell
git config --global user.name "Carlos Aguilar Miguel"
git config --global user.email "nukiro@yahoo.com"
git config --global core.editor "vim"
git config --global init.defaultBranch "main"

git config --global alias.a "add"
git config --global alias.st "status"
git config --global alias.plo "pull origin"
git config --global alias.pso "push origin"
git config --global alias.co "checkout"
git config --global alias.cm "commit -m"
```
