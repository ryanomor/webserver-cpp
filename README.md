# Barebones Transmission Control Protocol (TCP) Server

## Quick Setup
- In your IDE, make sure you have a C++ compiler installed. In VS Code, you can use the "Code Runner" extension.
- Run `main.cpp`
- Connect to the running TCP server by opening another terminal window and run `telnet localhost 54000`. You s hould see a message like `Connected to localhost.`
    - if `telnet` is not installed, run `brew install telnet`
- Begin to type in any message and hit enter. You should see the message displayed on the server you have running. It should also get echoed back to the client where you typed the message