# A simple socket exercise

This is an exercise so I could start undestanding sockets programming. The ``server.c`` listens to connections on the specified port and print received messages. The ``client.c`` allows to connect and send these messages.


## Usage

Compile the files:

```
gcc server.c -o server
gcc client.c -o client
```

Then start the server and run the client:

```
./server [port]

./client [host ip] [port]
```

Now you can send a message.


## Credits

Most of the code was created following this tutorial:

- <https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html>


