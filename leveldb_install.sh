#!/bin/sh

SANDBOX_DIR=/tmp/leveldb_install

## Bootstraps a sandbox dir
create_sandbox() {
  if [ ! -d $SANDBOX_DIR ]
    then
        mkdir -p $SANDBOX_DIR;
    fi
}

## Pulls and statically compiles last snappy version from repo
compile_snappy() {
    cd $SANDBOX_DIR
    svn checkout http://snappy.googlecode.com/svn/trunk/ snappy-read-only

    cd snappy-read-only
    ./autogen.sh
    ./configure --enable-shared=no --enable-static=yes
    make clean
    make CXXFLAGS='-g -O2 -fPIC'
}

## Pull and install last leveldb version from repo
compile_leveldb() {
    cd $SANDBOX_DIR
    git clone https://code.google.com/p/leveldb/ || (cd leveldb; git pull)

    cd leveldb
    make clean
    make LDFLAGS='-L../snappy-read-only/.libs/ -Bstatic -lsnappy -shared' OPT='-fPIC -O2 -DNDEBUG -DSNAPPY -I../snappy-read-only' SNAPPY_CFLAGS=''

    sudo cp -f $SANDBOX_DIR/leveldb/libleveldb.so* /usr/local/lib/
    sudo cp -rf $SANDBOX_DIR/leveldb/include/leveldb /usr/local/include/
}

create_sandbox
compile_snappy
compile_leveldb

## Destroy the sandbox
rm -rf $SANDBOX_DIR
