import socket
import sys
from threading import Thread
import time

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    
def check_ip_port(args):
    try:
        ip = args[0]
        port = int(args[1])
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        result = sock.connect_ex((ip,port))
        sock.close()
        if result == 0:
            print(bcolors.OKGREEN+ "port {0} is on".format(port))
            return True
        else:
            return False
    except:
        pass

def get_default_ports():
    commonPorts = {
    7, #Echo
    19, #Chargen
    20, #FTP Data Transfer
    21, #FTP Command Control
    22, #FTPS/SSH
    23, #Telnet
    25, #SMTP
    26, #SMTP
    42, #WINS Replication
    43, #WHOIS
    49, #TACACS
    53, #DNS service
    67, #DHCP
    68, #DHCP
    69, #TFTP
    70, #Gopher
    79, #Finger
    80, #HTTP
    88, #Kerberos
    102, #MS Exchange
    110, #POP3
    113, #Ident
    119, #NNTP (Usenet)
    123, #NTP
    135, #Microsoft RPC
    137, #NetBIOS
    138, #NetBIOS
    139, #NetBIOS
    143, #IMAP
    161, #SNMP
    162, #SNMP
    177, #XDMCP
    179, #BGP
    194, #IRC
    201, #AppleTalk
    264, #BGMP
    318, #TSP
    381, #HP Openview
    382, #HP Openview
    383, #HP Openview
    389, #LDAP
    411, #Direct Connect
    412, #Direct Connect
    443, #HTTPS
    445, #Microsoft DS
    464, #Kerberos
    465, #SMTP over SSL
    497, #Retrospect
    500, #ISAKMP
    512, #rexec
    513, #rlogin
    514, #syslog
    515, #LPD/LPR
    520, #RIP
    521, #RIPng (IPv6)
    540, #UUCP
    554, #RTSP
    546, #DHCPv6
    547, #DHCPv6
    560, #rmonitor
    563, #NNTP over SSL
    587, #SMTP SSL
    591, #FileMaker
    593, #Microsoft DCOM
    631, #Internet Printing Protocol
    636, #LDAP over SSL
    639, #MSDP (PIM)
    646, #LDP (MPLS)
    691, #MS Exchange
    860, #iSCSI
    873, #rsync
    902, #VMware Server
    989, #FTP over SSL
    990, #FTP over SSL
    993, #IMAP SSL
    995, #POP3 SSL
    1025, #Microsoft RPC
    1026, #Windows Messenger
    1027, #Windows Messenger
    1028, #Windows Messenger
    1029, #Windows Messenger
    1080, #SOCKS Proxy
    1080, #MyDoom
    1194, #OpenVPN
    1214, #Kazaa
    1241, #Nessus
    1311, #Dell OpenManage
    1337, #WASTE
    1433, #Microsoft SQL
    1434, #Microsoft SQL
    1512, #WINS
    1589, #Cisco VQP
    1701, #L2TP
    1723, #MS PPTP
    1725, #Steam
    1741, #CiscoWorks 2000
    1755, #MS Media Server
    1812, #RADIUS
    1813, #RADIUS
    1863, #MSN
    1985, #Cisco HSRP
    2000, #Cisco SCCP
    2002, #Cisco ACS
    2049, #NFS
    2077, #WebDAV/WebDisk
    2078, #WebDAV/WebDisk SSL
    2082, #cPanel
    2083, #cPanel SSL
    2086, #WHM
    2087, #WHM SSL
    2095, #Webmail
    2096, #Webmail SSL
    2100, #Oracle XDB
    2222, #DirectAdmin
    2302, #Halo
    2483, #Oracle DB
    2484, #Oracle DB
    2745, #Bagle.H
    2967, #Symantec AV
    3050, #Interbase DB
    3074, #XBOX Live
    3124, #HTTP Proxy
    3127, #MyDoom
    3128, #HTTP Proxy
    3222, #GLBP
    3260, #iSCSI Target
    3306, #MySQL
    3389, #Terminal Server
    3689, #iTunes
    3690, #Subversion
    3724, #World of Warcraft
    3784, #Ventrilo
    3785, #Ventrilo
    4333, #mSQL
    4444, #Blaster
    4664, #Google Desktop
    4672, #eMule
    4899, #- Radmin
    5000, #UPnP
    5001, #Slingbox
    5001, #iperf
    5004, #RTP
    5005, #RTP
    5050, #Yahoo! Messenger
    5060, #SIP
    5190, #AIM/ICQ
    5222, #XMPP/Jabber
    5223, #XMPP/Jabber
    5432, #PostgreSQL
    5500, #VNC Server
    5554, #Sasser
    5631, #pcAnywhere
    5632, #pcAnywhere
    5800, #VNC over HTTP
    5900, #VNC Server
    5901, #VNC Server
    5902, #VNC Server
    5903, #VNC Server
    5904, #VNC Server
    5905, #VNC Server
    5906, #VNC Server
    5907, #VNC Server
    5908, #VNC Server
    5909, #VNC Server
    5910, #VNC Server
    5911, #VNC Server
    5912, #VNC Server
    5913, #VNC Server
    5914, #VNC Server
    5915, #VNC Server
    5916, #VNC Server
    5917, #VNC Server
    5918, #VNC Server
    5919, #VNC Server
    5920, #VNC Server
    5921, #VNC Server
    5922, #VNC Server
    5923, #VNC Server
    5924, #VNC Server
    5925, #VNC Server
    5926, #VNC Server
    5927, #VNC Server
    5928, #VNC Server
    5929, #VNC Server
    5930, #VNC Server
    5931, #VNC Server
    5932, #VNC Server
    5933, #VNC Server
    5934, #VNC Server
    5935, #VNC Server
    5936, #VNC Server
    5937, #VNC Server
    5938, #VNC Server
    5939, #VNC Server
    5940, #VNC Server
    5941, #VNC Server
    5942, #VNC Server
    5943, #VNC Server
    5944, #VNC Server
    5945, #VNC Server
    5946, #VNC Server
    5947, #VNC Server
    5948, #VNC Server
    5949, #VNC Server
    5950, #VNC Server
    5951, #VNC Server
    5952, #VNC Server
    5953, #VNC Server
    5954, #VNC Server
    5955, #VNC Server
    5956, #VNC Server
    5957, #VNC Server
    5958, #VNC Server
    5959, #VNC Server
    5960, #VNC Server
    5961, #VNC Server
    5962, #VNC Server
    5963, #VNC Server
    5964, #VNC Server
    5965, #VNC Server
    5966, #VNC Server
    5967, #VNC Server
    5968, #VNC Server
    5969, #VNC Server
    5970, #VNC Server
    5971, #VNC Server
    5972, #VNC Server
    5973, #VNC Server
    5974, #VNC Server
    5975, #VNC Server
    5976, #VNC Server
    5977, #VNC Server
    5978, #VNC Server
    5979, #VNC Server
    5980, #VNC Server
    5981, #VNC Server
    5982, #VNC Server
    5983, #VNC Server
    5984, #VNC Server
    5985, #VNC Server
    5986, #VNC Server
    5987, #VNC Server
    5988, #VNC Server
    5989, #VNC Server
    5990, #VNC Server
    5991, #VNC Server
    5992, #VNC Server
    5993, #VNC Server
    5994, #VNC Server
    5995, #VNC Server
    5996, #VNC Server
    5997, #VNC Server
    5998, #VNC Server
    5999, #VNC Server
    6000, #X11
    6001, #X11
    6112, #Battle.net
    6129, #DameWare
    6257, #WinMX
    6346, #Gnutella
    6347, #Gnutella
    6500, #GameSpy Arcade
    6566, #SANE
    6588, #AnalogX
    6665, #IRC
    6666, #IRC
    6667, #IRC
    6668, #IRC
    6669, #IRC
    6679, #IRC over SSL
    6697, #IRC over SSL
    6699, #Napster
    6881, #BitTorrent
    6891, #Windows Live
    6892, #Windows Live
    6893, #Windows Live
    6894, #Windows Live
    6895, #Windows Live
    6896, #Windows Live
    6897, #Windows Live
    6898, #Windows Live
    6899, #Windows Live
    6900, #Windows Live
    6901, #Windows Live
    6970, #Quicktime
    7212, #GhostSurf
    7648, #CU-SeeMe
    7649, #CU-SeeMe
    8000, #Internet Radio
    8080, #HTTP Proxy
    8086, #Kaspersky AV
    8087, #Kaspersky AV
    8118, #Privoxy
    8200, #VMware Server
    8500, #Adobe ColdFusion
    8767, #TeamSpeak
    8866, #Bagle.B
    9100, #HP JetDirect
    9101, #Bacula
    9102, #Bacula
    9103, #Bacula
    9119, #MXit
    9800, #WebDAV
    9898, #Dabber
    9988, #Rbot/Spybot
    9999, #Urchin
    10000, #Webmin
    10000, #BackupExec
    10113, #NetIQ
    10114, #NetIQ
    10115, #NetIQ
    10116, #NetIQ
    11371, #OpenPGP
    12035, #Second Life
    12036, #Second Life
    12345, #NetBus
    13720, #NetBackup
    13721, #NetBackup
    14567, #Battlefield
    15118, #Dipnet/Oddbob
    19226, #AdminSecure
    19638, #Ensim
    20000, #Usermin
    24800, #Synergy
    25999, #Xfire
    27015, #Half-Life
    27017, #MongoDB
    27374, #Sub7
    28960, #Call of Duty
    31337
  }
    return commonPorts

def main():
    host="localhost"
    ports=get_default_ports()
    
    args = sys.argv[1:]
    
    #args = ["139.177.179.194" , "55321"]
    
    threads_arr=[]
    if len(args) >=1:
        host = args[0]
        
    if len(args) >=2:
        ports=[]
        if args[1] == "all":
            for i in range(65535):
                ports.append(i)
        else:
            parts=args[1].split('-')
            if len(parts)>1:
                for i in range(int(parts[0]),int(parts[1])):
                    ports.append(i)
            else:
                ports.append(args[1])
    
    for i in ports:
        done=False
        while not done:
            try:
                thread = Thread(target = check_ip_port, args = [(host,i,)])
                thread.start()
                threads_arr.append(thread)
                done = True
            except:
                time.sleep( 5 )
            
    for item in threads_arr:
        item.join()
    print('done')

if __name__ == "__main__":
    main()