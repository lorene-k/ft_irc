# ft_irc

**ft_irc** is a simplified Internet Relay Chat (IRC) server implemented in C++ as part of the École 42 core curriculum. It follows the RFC 1459 protocol basics and allows multiple users to connect using netcat and the IRC reference client **irssi**.

It also includes a simple bonus bot capable of responding to basic keywords inside a channel.


## Features

- Multi-user chat server over TCP
- Handles multiple clients simultaneously
- Parses and responds to standard IRC commands:
  - `PASS`, `NICK`, `USER`, `JOIN`, `PART`, `PRIVMSG`, `QUIT`, `PING`, etc...
- Channel management with user tracking
- Implements message broadcasting to channel members
- Authentication via server password
- Graceful connection handling and user cleanup
- Bonus: Simple IRC bot connects to the server and automatically joins a channe, then responds to specific keywords.


## System Calls Used
- `socket()`, `bind()`, `listen()`, `accept()`
- `recv()`, `send()`
- `poll()` for I/O multiplexing
- `close()`
- `getaddrinfo()`, `inet_ntoa()`, etc...

## Installation

```bash
git clone https://github.com/yourusername/ft_irc.git
cd ft_irc
make
```

## Usage - examples
Launch the server with chosen port and password as arguments :
```bash
./ircserv 6667 example-password
```

### 1. Using `nc` (netcat)

You can connect to your IRC server using `nc` (netcat) for testing purposes:

```bash
nc localhost 6667
```
Once connected, type the following IRC commands :

PASS 'password' \
NICK nickname \
USER username 0 * :User Realname \
JOIN #channel \
PRIVMSG #channel :example message \

### 2. Using `irssi`
For a more realistic IRC experience, you can use the irssi client. Connect to irssi with :
```bash
irssi -c localhost -p 6667 -w example-password -n nickname
```

Then, inside the irssi interface, test by entering commands like :
```bash
/join #channel
/part
/privmsg target-nickname msg
/quit
...
```
