GCC=gcc-4.8.3
BINUTILS=binutils-2.24

function get()
{
	wget ftp://ftp.gnu.org/gnu/gcc/$GCC/$GCC.tar.bz2
	wget ftp://ftp.gnu.org/gnu/binutils/$BINUTILS.tar.bz2
	tar -xf $GCC.tar.bz2
	tar -xf $BINUTILS.tar.bz2
}

function setup()
{
	mkdir -p cross
	export PREFIX="$(pwd)/cross"
	export TARGET=i686-elf
	export PATH="$PREFIX/bin:$PATH"

	mkdir -p build/binutils build/gcc
}

function build_binutils()
{
	cd build/binutils
	../../$BINUTILS/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-werror --with-sysroot
	make
	make install
	cd -
}

function build_gcc()
{
	cd build/gcc
	../../$GCC/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
	make all-gcc
	make all-target-libgcc
	make install-gcc
	make install-target-libgcc
	cd -
}

function build()
{
	setup
	build_binutils
	#build_gcc
}

build

