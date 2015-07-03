# Quickstart

Clone ODE from `hg clone https://bitbucket.org/odedevs/ode/` and then compile/install ode using these commands

    sudo apt-get install build-essential autoconf
    ./configure --enable-double-precision --with-trimesh-optcode --enable-new-trimesh --enable-shared
    make
    sudo make install

Then copy the `ode/include/drawstuff` folder into `/usr/local/include/,` and the `ode/drawstuff/src/.libs/libdrawstuff.a` to `/usr/local/lib`

Then just `cd` to catbot and `make`
