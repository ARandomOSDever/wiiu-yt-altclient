# wiiu-yt-altclient
This is a work in progress alternative Youtube client for the Nintendo Wii U
## Why use this?
 - In order to properly use the official client you need to find a specific version of the client which was removed from the update servers (title ID 0005000010105700) and you need a WUPS [plugin](https://github.com/PretendoNetwork/GiveMiiYouTube) to use it
 - The official client uses the TV interface, which personally is the worst YT UI
    - To be frank, I barely used the TV interface other than fiddling around in the Wii U client
## Building
You need to have the following programs/libraries (and their dependencies) in order to build this:
 - `devkitPPC`
 - `WUT`
 - [`SDL2`](https://github.com/yawut/SDL)
 - `elf2rpl` (part of `wut-tools`)
 - `wiiu-pkg-config`
 - `ninja`
 - `meson`
Configure using `meson`: 
```bash
# you can change "build" to any directory name of your choosing
meson setup build --cross-file crossfile.ini
```
and compile with `ninja` or `meson compile`:
```bash
cd build

# you can do this
ninja

# or you can do this
meson compile
```
A RPX file called "yt-altclient.rpx" will be compiled