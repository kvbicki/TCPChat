 Chat Application — Server and Client
📄 Description
This is a simple terminal-based chat application consisting of a server and multiple clients. The server handles multiple client connections, broadcasts messages to all users, and supports private messaging between clients.

✨ Features
🖥️ Server
Handles multiple client connections simultaneously using threads

Maintains a list of connected clients with nicknames

Supports broadcasting messages to all clients

Implements private messaging (/msg)

Provides a list of connected users (/list)

Handles client disconnections gracefully

💻 Client
Connects to the server using IP address and port

Sends and receives messages in real-time

Supports the following commands:

/quit — Disconnect from server

/list — Show list of connected users

/msg [nickname] [message] — Send private message to a specific user

⚙️ Building the Application
🛠 Requirements
Windows OS (uses Winsock2)

CMake 3.10 or higher

C++17 compatible compiler

🏗️ Build Steps
Clone this repository:

bash
Kopiuj
Edytuj
git clone https://github.com/your-username/chat-app.git
cd chat-app
Create a build directory:

bash
Kopiuj
Edytuj
mkdir build
cd build
Run CMake:

bash
Kopiuj
Edytuj
cmake ..
Build the project:

bash
Kopiuj
Edytuj
cmake --build .
This will generate two executables:

server — The chat server

client — The chat client

🚀 Usage
Start the Server
bash
Kopiuj
Edytuj
./server
The server listens on port 12345 by default.

Start a Client
bash
Kopiuj
Edytuj
./client
The client will connect to 127.0.0.1:12345 by default.
On connection, it will prompt the user to enter a nickname.

🔧 Supported Commands
/quit — Disconnect from the server

/list — Display all connected users

/msg [nickname] [message] — Send a private message

📝 Notes
The server informs all users when someone joins or leaves the chat.

Private messages are only delivered if the target nickname exists.

All communication is plain-text and terminal-based.