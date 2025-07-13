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