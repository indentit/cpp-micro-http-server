# cpp-micro-http-server

Asynchronous C++ HTTP server, for you to copy-paste into you micro-services project.

The code is small and straight forward to make it easy to audit and understand what it does and how.

## Repository and code structure
The repository is composed of two folders: `server` with the server implementation (this is the code that you want);
`test` with an example of how to use the server code.

The source code in the `server` folder has the following components.
- `server` creates and starts the server.
- `acceptor` accepts client connections and creates new service objects to handle them.
- `http-service` handles a client connection.
- `header` represents a HTTP header.
- `request` represents a client HTTP request.
- `response` represents a response to be sent to the client.

## Additional resources and documentation
We have a series of articles in [indentit.com](https://indentit.com) that explain in detail the
concepts behind this server and also how the code works.

### The routing component
[Router overview article](https://indentit.com/posts/webapps/cpp-http-router/)


## How to use it
The idea is for you to integrate the source code directly into you project.
You can do it any way you wish, for example you can just copy paste the `server` folder into your project.

The way we use it is through git submodules.
The advantage being that by integrating the server code into a project as a git submodules allows you to
pull updates from this repository.

Start by checking the code in the [test](server) folder.

To add it as a git submodule you can use a command like the following.
```shell
git submodule add git@github.com:indentit/cpp-micro-http-server.git third_party/cpp-micro-http-server
```

## Dependencies and building
As dependency there's the [stand-alone non-boost library](https://think-async.com/Asio/asio-1.24.0/doc/) which is used for the TCP socket communication layer.
This a header based library with good documentation.

To build the test example do the following.
```shell
cd test
mkdir build
cd build
cmake ..
make
```
