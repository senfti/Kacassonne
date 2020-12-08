# Run dependencies
## Ubuntu
`sudo apt-get update && sudo apt-get install libwxgtk3.0-gtk3-0v5 wx-common libzmq5`
## macOS
`brew install zeromq wxmac`

# Compile .Instructions
## Ubuntu
`sudo apt-get update && sudo apt-get install libzmq3-dev libwxgtk3.0-gtk3-dev libwxbase3.0-dev make`
Ubuntu 18.04 package repository default compiler and cmake are too old (g++8 or newer, cmake 3.12 or newer). 
See https://github.com/senfti/Kacassonne/blob/master/docker/Dockerfile for instructions.
## macOS
`brew install zeromq pkgconfig wxmac`
`wget https://raw.githubusercontent.com/zeromq/cppzmq/master/zmq.hpp -O /usr/local/include/zmq.hpp`
In the project folder run `cmake --configure . && cmake --build .` to get the `Kacassonne` executable.
## Windows
You probably have to build wxWidgets (https://github.com/wxWidgets/wxWidgets) and zeromq and zeromqpp yourself. 

# Licence
MIT License 

Copyright (c) 2020 Thomas Senfter (except nlohmann::json)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
