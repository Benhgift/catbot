Clone ODE from https://bitbucket.org/odedevs/ode/ and then compile/install it

    ./configure --enable-double-precision --with-trimesh-optcode --enable-new-trimesh --enable-shared
    make
    sudo make install

Then copy the `ode/include/drawstuff` folder into `/usr/local/include/,` and the `ode/drawstuff/src/.libs/libdrawstuff.a` to `/usr/local/lib`

Then just cd to catbot and `make`
