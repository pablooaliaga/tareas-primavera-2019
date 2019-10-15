import socket


bufferSize  = 64
localIP     = raw_input()
localPort   = input()


# Create a datagram socket

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

 

# Bind to address and ip

UDPServerSocket.bind((localIP, localPort))

 

print("\n[*] UDP server up and listening")

 

# Listen for incoming datagrams
bytesAdressPair = UDPServerSocket.recvfrom(bufferSize)
message = bytesAdressPair[0]
address = bytesAdressPair[1]
    
clientMsg = "Message from Client: {}".format(message)
clientIP  = "Client IP Address: {}".format(address)
print(clientMsg)
print(clientIP)


while(True):
    
    msgFromServer       = raw_input()
    bytesToSend = str.encode(msgFromServer)
    chunks, chunk_size = len(bytesToSend), bufferSize
    packages = []
    for i in range(0, chunks, chunk_size):
        packages.append(msgFromServer[i:i+chunk_size])
    
    # Sending a reply to client
    for package in packages:        
        UDPServerSocket.sendto(package, address)