import socket

# Connect to the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect(("localhost", 8080))
    s.sendall(b"your_custom_command\n")  # Send a custom command
    data = s.recv(1024)

print("Received", repr(data))
