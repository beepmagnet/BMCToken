# BeepMagnet International Ltd


### Download Supported Platforms

[![OK-windows](http://i.imgur.com/kJIvcip.png)](https://beepmagnet.info/#jf_download) [![OK-mac](http://i.imgur.com/eW5Hlpc.png)](https://beepmagnet.info/#jf_download) [![OK-ubuntu](http://imgur.com/orQ2ta4.png)](https://beepmagnet.info/#jf_download) 

--------------------

# BMCToken Development process

Developers work in their own forks, then submit pull requests when
they think their feature or bug fix is ready.  

The patch will be accepted if there is broad consensus that it is a
good thing.  Developers should expect to rework and resubmit patches
if they don't match the project's coding conventions (see coding.txt)
or are controversial.

The master branch is regularly built and tested, but is not guaranteed
to be completely stable. Tags are regularly created to indicate new
stable release versions of BMCToken.

Feature branches are created when there are major new features being
worked on by several people.

From time to time a pull request will become outdated. If this occurs, and
the pull is no longer automatically merge able; a comment on the pull will
be used to issue a warning of closure. The pull will be closed 15 days
after the warning if action is not taken by the author. Pull requests closed
in this manner will have their corresponding issue labelled 'stagnant'.

Issues with no commits will be given a similar warning, and closed after
15 days from their last activity. Issues closed in this manner will be 
labelled 'stale'.





#Linux Distribution Specific Instructions
#Ubuntu & Debian
#Dependency Build Instructions


Build requirements:

sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils python3 libboost-system-dev libboost-filesystem-dev  libboost-chrono-dev libboost-test-dev libboost-thread-dev

BerkeleyDB is required for the wallet.

For Ubuntu only: db4.8 packages are available here. You can add the repository and install using the following commands:

sudo apt-get install software-properties-common
sudo add-apt-repository ppa:bitcoin/bitcoin
sudo apt-get update
sudo apt-get install libdb4.8-dev libdb4.8++-dev


Ubuntu and Debian have their own libdb-dev and libdb++-dev packages, but these will install BerkeleyDB 5.1 or later, which break binary wallet compatibility with the distributed executables which are based on BerkeleyDB 4.8. If you do not care about wallet compatibility, pass --with-incompatible-bdb to configure.

See the section "Disable-wallet mode" to build BMCToken without wallet.

Optional (see --with-miniupnpc and --enable-upnp-default):

sudo apt-get install libminiupnpc-dev
ZMQ dependencies (provides ZMQ API 4.x):

sudo apt-get install libzmq3-dev
Dependencies for the GUI
If you want to build litecoin-qt, make sure that the required packages for Qt development are installed. Qt 5 is necessary to build the GUI. To build without GUI pass --without-gui.

To build with Qt 5 you need the following:

sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler
libqrencode (optional) can be installed with:

sudo apt-get install libqrencode-dev
Once these are installed, they will be found by configure and a beepmagnet executable will be built by default.



Get the version of Boost that you require. This is for 1.55 but feel free to change or manually download yourself:
wget -O boost_1_58_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.gz/download tar xzvf boost_1_58_0.tar.gz cd boost_1_58_0/


Get the required libraries, main ones are icu for boost::regex support:
sudo apt-get update sudo apt-get install build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev libboost-all-dev



Boost's bootstrap setup:

./bootstrap.sh --prefix=/usr/

Then build it with:

./b2

and eventually install it:

sudo ./b2 instal








