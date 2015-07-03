# Quickstart

Clone ODE from `hg clone https://bitbucket.org/odedevs/ode/` and then compile/install ode using these commands

    sudo apt-get install build-essential autoconf libtool autoconf automake
 pkg-config
    ./configure --enable-double-precision --with-trimesh-optcode --enable-new-trimesh --enable-shared
    make
    sudo make install

Then from the root ode directory run these to copy the extra lib things for visuals

    sudo cp -p drawstuff/src/.libs/libdrawstuff.a /usr/local/lib/
    sudo cp -p drawstuff/src/libdrawstuff.la /usr/local/lib/
    sudo cp -rp include/drawstuff /usr/local/include/
    sudo cp -rp drawstuff/textures /usr/local/include/drawstuff/

Then just `cd` to catbot and `make`
