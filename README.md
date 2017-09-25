# lrsinglelinkedlist
Single linked list implementation in C 

This is a learning project so some code is purposefully convoluted ( pointer arithmetic in delete function for example )

This project was made from my [library starter project](https://github.com/Liam-Ryan/C-Static-Library-Starter) 

**Dependencies**

- CMake
- FindPkgConfig
- Check
- pthread( required by check )

**Warning**

Library only been tested on Linux systems

**Getting started**

1. Install dependencies and clone repo with git or download a zip. Check is available in most Linux distro repositories.
1. Create a build folder in the project directory - mkdir build
1. Navigate to the build folder and run `cmake ..`
1. Hopefully you won't see any errors, if you do you likely have a missing dependency
1. Run `make` in the project directory, if you have errors now it's probably my fault - please raise an issue!
1. If all went well then you can navigate to test folder and run `./testexec` You should see output saying 3 tests of 
3 passed
1. If you wish you can break a test to make sure all is working as it should - go to library.c and change the output 
string in hello(). Re-run make and run the new testexec binary and you should see a failure

**Want a shared library instead of static?**

No problem, just change the option in library/CMakeLists.txt to ON before building per the instructions above and you'll
have a shiny new .so library in no time!

**Memory Leaks and debugging**

To run valgrind properly or to debug your unit tests you need to uncomment `srunner_set_fork_status(sr, CK_NOFORK);` 
in test.c. This does prevent check from catching segfaults so be aware of that. After uncommenting and rebuilding the 
testexec binary with make you can then run `valgrind --leak-check=full ./testexec` from the build/test directory.  
