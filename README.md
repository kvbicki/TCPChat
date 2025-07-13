# Chat Application - Server & Client

## 📝 Description  
A multi-client chat system with:  
- **Server**: Manages connections, broadcasts messages, and handles private chats  
- **Clients**: Connect to server, send/receive messages in real-time  

---

## ✨ Features  

### 🖥️ Server  
✅ Multi-threaded client handling  
✅ Nickname-based user identification  
✅ Global message broadcasting  
🔒 Private messaging (`/msg` command)  
📋 Online user listing (`/list` command)  
♻️ Graceful disconnect handling  

### 💻 Client  
🌐 TCP/IP connectivity  
📨 Message sending with commands:  
- `/quit` - Disconnect  
- `/list` - Show online users  
- `/msg <nick> <text>` - Private message  

---

## 🛠️ Build & Run  

### Prerequisites  
- CMake ≥ 3.10  
- Windows OS (Winsock2)  
- C++17 compiler  

### Build Steps  
```bash
mkdir build && cd build
cmake ..
cmake --build .

## 🏃‍♂️ Execution

### Server
| Component | Command       | Default Port |
|-----------|--------------|-------------|
| Server    | `./server`   | 12345       |

### Client
| Component | Command       | Connection Target         |
|-----------|--------------|--------------------------|
| Client    | `./client`   | 127.0.0.1:12345          |

## ⌨️ Command Reference

| Command   | Action               | Example                 |
|-----------|----------------------|-------------------------|
| `/quit`   | Disconnect           | `/quit`                 |
| `/list`   | Show online users    | `/list`                 |
| `/msg`    | Send private message | `/msg bob Hello there!` |

## 📂 Project Structure

```text
├── client/
│   ├── Client.cpp
│   └── main.cpp
├── server/
│   ├── Clients.cpp
│   ├── ClientHandler.cpp
│   ├── Server.cpp
│   └── main.cpp
└── CMakeLists.txt