# minitalk
a server and a client exchanging data using UNIX signals

# explanation 
    this proejct simply use two signals (SIGUSR/SIGUSR2) to send a message from the client which is a process to another process the server.
    the bonus part is able to send unicode characters with acknowledge message.
# resources
  an advanced book about programming in UNIX env : https://xesoa.com/wp-content/uploads/2014/04/APUE-3rd.pdf
# usage
    use "make" to create server and client.
    run the server "./server" on the terminal.
    run the client with 2 arguments "./client PID_server MSG".
    use "make clean" to delete the client and the server
    for the bonus part, works the same with "make bonus" "make fclean".
