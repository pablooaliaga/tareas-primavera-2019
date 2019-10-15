import socket

 

msgFromClient       = "Hello UDP Server"

bytesToSend         = str.encode(msgFromClient)

ip = raw_input()
port = input()

serverAddressPort   = (ip, port)

bufferSize          = 64

 

# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

 

# Send to server using created UDP socket

UDPClientSocket.sendto(bytesToSend, serverAddressPort)

 
while True:
    msgFromServer = UDPClientSocket.recvfrom(bufferSize)
    msg = msgFromServer[0]
    print(msg)