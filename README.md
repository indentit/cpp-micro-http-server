# cpp-micro-http-server

HTTP server in C++ for you to copy-paste into you micro-services project.

The code is small and straight forward to make it easy to audit and understand what it does and how.

## Repository structure
Composed of two folders: `server` with the server implementation (this is the code that you want);
`test` with an example of how to use the server code.

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

Start by checking the code in the [server](server) folder.
