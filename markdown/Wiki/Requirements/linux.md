
<div align="center">
    
# ![icons8-linux-100](https://user-images.githubusercontent.com/81469821/222534362-fdf42531-1b05-48df-a3a5-b39acb3cf691.png) Linux Requirements
    
</div>

<div align="center">   
<h3>
<a href="#Ubuntu">Ubuntu</a>
    <a href="#Ubuntu">Debian</a>
        <a href="#Ubuntu">Fedora</a>
</h3>
</div>

<h2> Software</h2>

> Boost ≥ 1.81    
> MariaDB ≥ 10.11.2  
> OpenSSL ≥ 1.x.x, 3.x.x not supported
> CMake ≥ 3.18.4 
> Clang ≥ 11 or GCC ≥ 10   
> zlib ≥ 1.2.7

<h2>Hardware</h2>
    
> Processor with SSE2 support  
> 2GB of RAM   
> 2GB of SWAP

<div id="Ubuntu"></div> 

## Ubuntu
    
### A. For Ubuntu 20.04 LTS <sup>This may work for older versions too(not tested)</sup>

Ubuntu 20.04 LTS have an old version of cmake in package manager. So we need to install the new version fo cmake first.

A.1. Uninstall the default version provided by Ubuntu's package manager (if Installed) and configuration by using:
```
sudo apt remove --purge --auto-remove cmake
```
or:
```
sudo apt purge --auto-remove cmake
```
A.2. Prepare for installation    
```
sudo apt update && \
sudo apt install -y software-properties-common lsb-release && \
sudo apt clean all
```
A.3. Obtain a copy of kitware's signing key.
```
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
```
A.4. Add kitware's repository to your sources list.
```
sudo apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"
```
A.5. As an optional step, is recommended that we also install the kitware-archive-keyring package to ensure that Kitware's keyring stays up to date as they rotate their keys.
```
sudo apt update
sudo apt install kitware-archive-keyring
sudo rm /etc/apt/trusted.gpg.d/kitware.gpg
```
A.6. If running sudo apt update gets the following error:
```
Err:7 https://apt.kitware.com/ubuntu bionic InRelease
The following signatures couldn't be verified because the public key is not available: NO_PUBKEY 6AF7F09730B3F0A4
Fetched 11.0 kB in 1s (7552 B/s)
```
Copy the public key you got after "NO_PUBKEY" and run this command: 

```
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 6AF7F09730B3F0A4 
```
P.S. Don't use this key, it can be not the same as yours

Finally we can update and install all requirements.
To do that u need to run:
```
sudo apt update  && sudo apt install git cmake make gcc g++ clang libssl-dev libbz2-dev libreadline-dev libncurses-dev libboost-all-dev mariadb-server mariadb-client libmariadb-dev libmariadb-dev-compat -y
```
After The installation finished you are ready for next step. [Core Installation](markdown/Wiki/CoreInstallation/linux.md)