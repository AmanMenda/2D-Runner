function install_raylib_on_debian_based_distros(){
    # install raylib's dependencies
    sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

    # clone the repository and build it
    git clone https://github.com/raysan5/raylib.git raylib
    cd raylib
    mkdir build && cd build
    cmake -DBUILD_SHARED_LIBS=ON ..

    # install raylib
    make
    sudo make install
}

# fn install_raylib_on_red_hat_distros()
# {
# }

# fn install_raylib_on_windows()
# {
# }

function main()
{
    if [ `uname` = "Linux" ] ;
    then
        if [ -e "/etc/issue" ] ;
        then
            issue=`cat /etc/issue`
            set -- $issue
        if [ $1 = "Ubuntu" ] ;
        then
            echo "Ubuntu version:" $2
            install_raylib_on_debian_based_distros
        fi
        fi
    fi
}

main