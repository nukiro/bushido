# How to Setup the Project

## For Develpment

Update Ubuntu repositories and upgrade.

```shell
sudo apt update
sudo apt upgrade
```

For the **terminal**, install: `zsh` and `oh-my-zsh`.

Install utilities: `sudo apt install git vim`.

An **IDE**: `VSCode`

**GitHub**

Generate SSH Key `ssh-keygen -t ed25519 -C "email@test.com"`, copy it `cat .ssh/id_ed25519.pub` and add it to GitHub account.

Clone the project.

**C stuff**

`sudo apt install build-essential gdb pkg-config`

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
