#!/usr/bin/env python
import socket, sys
import threading
import json


try:
    listening_port = int(input("[*] Enter Listening Port Number: "))
except KeyboardInterrupt:
    print ("\n[*] User Requested An Interrupt")
    print ("[*] Applicatino Exiting...")
    sys.exit()

try:
    with open('config.json', 'r') as f:
        distros_dict = json.load(f)
        user = distros_dict['user']
        blocked = distros_dict['blocked']
        forbidden_words = distros_dict['forbidden_words']

except Exception:
    print("[*] Error, cant parse json")
    sys.exit()


max_conn = 5 
buffer_size = 8192
threads_list = []

def start():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.bind(('', listening_port))
        s.listen(max_conn)
        print("[*] Initializing Sockets ... Done")
        print("[*] Socket Binded Successfully ...")
        print("[*] Server Started Successfully [%d]\n" % (listening_port))
    except Exception as e:
        print(e)
        print ("[*] Unable to initialize Socket")
        sys.exit(2)

    while True:
        try:
            conn, addr = s.accept()
            data = conn.recv(buffer_size)
            t = threading.Thread(target= conn_string, args=(conn, data, addr))
            t.start()

        except KeyboardInterrupt:
            s.close()
            print ("\n[*] Proxy Server Shutting Down ...")
            print ("Vuela Alto Chimuelo!")
            sys.exit(1)

    s.close()
    return


def conn_string(conn, data, addr):
    try:
        data=data.decode()
        first_line = data.split('\r\n')[0]
        url = first_line.split(' ')[1]
        http_pos = url.find("://")
        if (http_pos==-1):
            temp = url
        else:
            temp = url[(http_pos+3):]
        cutted_url=temp ##used for blocked
        webserver_pos = temp.find("/")
        if webserver_pos == -1:
            webserver_pos = len(temp)
        webserver = ""

        port_pos = temp.find(":")
        port = -1
        if(port_pos == -1 or webserver_pos < port_pos):
            port = 80
            webserver = temp[:webserver_pos]
        else:
            port = int((temp[(port_pos+1):])[:webserver_pos-port_pos-1])
            webserver = temp[:port_pos]

        '''print('\n'+str(webserver))
        print('\n'+str(port))
        print('\n'+str(conn))
        print('\n'+str(addr))
        print('\n'+str(data))'''
        proxy_server(webserver, port, conn, addr, data, cutted_url)
    
    except Exception as e:
        print(e)
        pass
    finally:
        return

def proxy_server(webserver, port, conn, addr, data, compare_url):
    try:
        print("[*] Doing prhttp://anakena.dcc.uchile.cl:8989/oxy ...")
        
        ##check Blocked Pages
        print("[*] Checking if page is allowed ...")
        if pageBlocked(compare_url):
            blocked="HTTP/1.1 403 Forbidden\r\n"
            blocked+="\r\n" #endHeaders
            blocked+="403 - FORBIDDEN UWU!.\n"
            blocked=blocked.encode()
            print("[*] PAGE BLOCKED!")
            conn.send(blocked)
            conn.close()
            sys.exit(1)
            return

        print("[*] Page allowed!! Pase mijo'")
        ##added Custom Header
        data=addHeader(data,'X-ElQuePregunta',user)
        print("\n")
        print(data)

        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((webserver,port))
        s.send(data.encode())
        while 1:
            reply = s.recv(buffer_size)
            reply = reply.decode() ##using utf-8
            data_pos = reply.find("\r\n\r\n")
            censored_data = reply[data_pos:]
            print(forbidden_words)
            for pair in forbidden_words:
                items = pair.items()
                for (word,replace) in items:
                    censored_data = replaceWord(censored_data, word,replace)

            reply = reply[:data_pos] + censored_data

            print(reply)
            
            reply = reply.encode() #using utf-8

            if(len(reply) > 0):
                conn.send(reply)
                

                dar = float(len(reply))
                dar = float(dar / 1024)
                dar = "%.3s" % (str(dar))
                dar = "%s KB" % (dar)
                print("[*] Request Done: %s => %s <=" % (str(addr[0]),str(dar)))
            else:
                break
        s.close()
        conn.close()
        sys.exit(1)
  

    except (socket.error, KeyboardInterrupt, Exception) as e:
        print(e)
        s.close()
        conn.close()
        sys.exit(1)
    
    finally:
        return

def addHeader(data, name, value):
    endpos = data.find("\r\n\r\n")
    r = data[:endpos] + ("\r\n%s:%s" % (name,value)) + data[endpos:]
    print("[*] Header added!")
    return r

def pageBlocked(url):

    print("-----")
    print(url)
    for page in blocked:
        pos=page.find("//")
        if(pos != -1):
            page=page[pos+2:]
    
        if(page[:4]=="www."):
            page=page[4:]
        print(page)
        if (url == page):
            return True
    return False

def replaceWord(stream, word, replace):
    return stream.replace(word,replace)



start()



