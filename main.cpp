#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <ostream>

std::mutex mu;


namespace Color {
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);

void print(int port ,bool isopen){
  mu.lock();
  if (isopen)
  {
    std::cout << green << "Port " << port << " : " << "OPEN" << std::endl;
  }else{
    //std::cout << red << "Port " << port << " : " << "CLOSE" << std::endl;
  }
  mu.unlock();
}


static bool port_is_open(const std::string& address, int port)
{

  int sock = 0, client_fd;
  struct sockaddr_in serv_addr;
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) >= 0)
  {
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr) > 0)
    {
      if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) >= 0)
      {
        close(client_fd);
        print(port,true);
        return true;
      }
    }
  }
  print(port,false);
  return false;
}

static std::vector<std::string> split(const std::string& string,
  char delimiter = ' ',
  bool allow_empty = false)
{
  std::vector<std::string> tokens;
  std::stringstream sstream(string);
  std::string token;
  while (std::getline(sstream, token, delimiter))
  {
    if (allow_empty || token.size() > 0)
      tokens.push_back(token);
  }
  return tokens;
}

static int string_to_int(const std::string& string)
{
  std::stringstream sstream(string);
  int i;
  sstream >> i;
  return i;
}

template <typename T>
static void swap(T& a, T& b)
{
  T c = a;
  a = b;
  b = c;
}

template <typename T>
static std::vector<T> range(T min, T max)
{
  if (min > max)
    swap(min, max);
  if (min == max)
    return std::vector<T>(1, min);
  std::vector<T> values;
  for (; min <= max; ++min)
    values.push_back(min);
  return values;
}

static std::vector<int> parse_ports_list(const std::string& list)
{
  std::vector<int> ports;
  for (const std::string& token : split(list, ','))
  {
    std::vector<std::string> strrange = split(token, '-');
    switch (strrange.size())
    {
    case 0:
      ports.push_back(string_to_int(token));
      break;
    case 1:
      ports.push_back(string_to_int(strrange[0]));
      break;
    case 2:
    {
      int min = string_to_int(strrange[0]),
        max = string_to_int(strrange[1]);
      for (int port : range(min, max))
        ports.push_back(port);
      break;
    }
    default:
      break;
    }
  }
  return ports;
}

std::vector<int> getCommonPort(){
   std::vector<int> commonPorts = {
    7, //Echo
    19, //Chargen
    20, //FTP Data Transfer
    21, //FTP Command Control
    22, //FTPS/SSH
    23, //Telnet
    25, //SMTP
    26, //SMTP
    42, //WINS Replication
    43, //WHOIS
    49, //TACACS
    53, //DNS service
    67, //DHCP
    68, //DHCP
    69, //TFTP
    70, //Gopher
    79, //Finger
    80, //HTTP
    88, //Kerberos
    102, //MS Exchange
    110, //POP3
    113, //Ident
    119, //NNTP (Usenet)
    123, //NTP
    135, //Microsoft RPC
    137, //NetBIOS
    138, //NetBIOS
    139, //NetBIOS
    143, //IMAP
    161, //SNMP
    162, //SNMP
    177, //XDMCP
    179, //BGP
    194, //IRC
    201, //AppleTalk
    264, //BGMP
    318, //TSP
    381, //HP Openview
    382, //HP Openview
    383, //HP Openview
    389, //LDAP
    411, //Direct Connect
    412, //Direct Connect
    443, //HTTPS
    445, //Microsoft DS
    464, //Kerberos
    465, //SMTP over SSL
    497, //Retrospect
    500, //ISAKMP
    512, //rexec
    513, //rlogin
    514, //syslog
    515, //LPD/LPR
    520, //RIP
    521, //RIPng (IPv6)
    540, //UUCP
    554, //RTSP
    546, //DHCPv6
    547, //DHCPv6
    560, //rmonitor
    563, //NNTP over SSL
    587, //SMTP SSL
    591, //FileMaker
    593, //Microsoft DCOM
    631, //Internet Printing Protocol
    636, //LDAP over SSL
    639, //MSDP (PIM)
    646, //LDP (MPLS)
    691, //MS Exchange
    860, //iSCSI
    873, //rsync
    902, //VMware Server
    989, //FTP over SSL
    990, //FTP over SSL
    993, //IMAP SSL
    995, //POP3 SSL
    1025, //Microsoft RPC
    1026, //Windows Messenger
    1027, //Windows Messenger
    1028, //Windows Messenger
    1029, //Windows Messenger
    1080, //SOCKS Proxy
    1080, //MyDoom
    1194, //OpenVPN
    1214, //Kazaa
    1241, //Nessus
    1311, //Dell OpenManage
    1337, //WASTE
    1433, //Microsoft SQL
    1434, //Microsoft SQL
    1512, //WINS
    1589, //Cisco VQP
    1701, //L2TP
    1723, //MS PPTP
    1725, //Steam
    1741, //CiscoWorks 2000
    1755, //MS Media Server
    1812, //RADIUS
    1813, //RADIUS
    1863, //MSN
    1985, //Cisco HSRP
    2000, //Cisco SCCP
    2002, //Cisco ACS
    2049, //NFS
    2077, //WebDAV/WebDisk
    2078, //WebDAV/WebDisk SSL
    2082, //cPanel
    2083, //cPanel SSL
    2086, //WHM
    2087, //WHM SSL
    2095, //Webmail
    2096, //Webmail SSL
    2100, //Oracle XDB
    2222, //DirectAdmin
    2302, //Halo
    2483, //Oracle DB
    2484, //Oracle DB
    2745, //Bagle.H
    2967, //Symantec AV
    3050, //Interbase DB
    3074, //XBOX Live
    3124, //HTTP Proxy
    3127, //MyDoom
    3128, //HTTP Proxy
    3222, //GLBP
    3260, //iSCSI Target
    3306, //MySQL
    3389, //Terminal Server
    3689, //iTunes
    3690, //Subversion
    3724, //World of Warcraft
    3784, //Ventrilo
    3785, //Ventrilo
    4333, //mSQL
    4444, //Blaster
    4664, //Google Desktop
    4672, //eMule
    4899, //- Radmin
    5000, //UPnP
    5001, //Slingbox
    5001, //iperf
    5004, //RTP
    5005, //RTP
    5050, //Yahoo! Messenger
    5060, //SIP
    5190, //AIM/ICQ
    5222, //XMPP/Jabber
    5223, //XMPP/Jabber
    5432, //PostgreSQL
    5500, //VNC Server
    5554, //Sasser
    5631, //pcAnywhere
    5632, //pcAnywhere
    5800, //VNC over HTTP
    5900, //VNC Server
    5901, //VNC Server
    5902, //VNC Server
    5903, //VNC Server
    5904, //VNC Server
    5905, //VNC Server
    5906, //VNC Server
    5907, //VNC Server
    5908, //VNC Server
    5909, //VNC Server
    5910, //VNC Server
    5911, //VNC Server
    5912, //VNC Server
    5913, //VNC Server
    5914, //VNC Server
    5915, //VNC Server
    5916, //VNC Server
    5917, //VNC Server
    5918, //VNC Server
    5919, //VNC Server
    5920, //VNC Server
    5921, //VNC Server
    5922, //VNC Server
    5923, //VNC Server
    5924, //VNC Server
    5925, //VNC Server
    5926, //VNC Server
    5927, //VNC Server
    5928, //VNC Server
    5929, //VNC Server
    5930, //VNC Server
    5931, //VNC Server
    5932, //VNC Server
    5933, //VNC Server
    5934, //VNC Server
    5935, //VNC Server
    5936, //VNC Server
    5937, //VNC Server
    5938, //VNC Server
    5939, //VNC Server
    5940, //VNC Server
    5941, //VNC Server
    5942, //VNC Server
    5943, //VNC Server
    5944, //VNC Server
    5945, //VNC Server
    5946, //VNC Server
    5947, //VNC Server
    5948, //VNC Server
    5949, //VNC Server
    5950, //VNC Server
    5951, //VNC Server
    5952, //VNC Server
    5953, //VNC Server
    5954, //VNC Server
    5955, //VNC Server
    5956, //VNC Server
    5957, //VNC Server
    5958, //VNC Server
    5959, //VNC Server
    5960, //VNC Server
    5961, //VNC Server
    5962, //VNC Server
    5963, //VNC Server
    5964, //VNC Server
    5965, //VNC Server
    5966, //VNC Server
    5967, //VNC Server
    5968, //VNC Server
    5969, //VNC Server
    5970, //VNC Server
    5971, //VNC Server
    5972, //VNC Server
    5973, //VNC Server
    5974, //VNC Server
    5975, //VNC Server
    5976, //VNC Server
    5977, //VNC Server
    5978, //VNC Server
    5979, //VNC Server
    5980, //VNC Server
    5981, //VNC Server
    5982, //VNC Server
    5983, //VNC Server
    5984, //VNC Server
    5985, //VNC Server
    5986, //VNC Server
    5987, //VNC Server
    5988, //VNC Server
    5989, //VNC Server
    5990, //VNC Server
    5991, //VNC Server
    5992, //VNC Server
    5993, //VNC Server
    5994, //VNC Server
    5995, //VNC Server
    5996, //VNC Server
    5997, //VNC Server
    5998, //VNC Server
    5999, //VNC Server
    6000, //X11
    6001, //X11
    6112, //Battle.net
    6129, //DameWare
    6257, //WinMX
    6346, //Gnutella
    6347, //Gnutella
    6500, //GameSpy Arcade
    6566, //SANE
    6588, //AnalogX
    6665, //IRC
    6666, //IRC
    6667, //IRC
    6668, //IRC
    6669, //IRC
    6679, //IRC over SSL
    6697, //IRC over SSL
    6699, //Napster
    6881, //BitTorrent
    6891, //Windows Live
    6892, //Windows Live
    6893, //Windows Live
    6894, //Windows Live
    6895, //Windows Live
    6896, //Windows Live
    6897, //Windows Live
    6898, //Windows Live
    6899, //Windows Live
    6900, //Windows Live
    6901, //Windows Live
    6970, //Quicktime
    7212, //GhostSurf
    7648, //CU-SeeMe
    7649, //CU-SeeMe
    8000, //Internet Radio
    8080, //HTTP Proxy
    8086, //Kaspersky AV
    8087, //Kaspersky AV
    8118, //Privoxy
    8200, //VMware Server
    8500, //Adobe ColdFusion
    8767, //TeamSpeak
    8866, //Bagle.B
    9100, //HP JetDirect
    9101, //Bacula
    9102, //Bacula
    9103, //Bacula
    9119, //MXit
    9800, //WebDAV
    9898, //Dabber
    9988, //Rbot/Spybot
    9999, //Urchin
    10000, //Webmin
    10000, //BackupExec
    10113, //NetIQ
    10114, //NetIQ
    10115, //NetIQ
    10116, //NetIQ
    11371, //OpenPGP
    12035, //Second Life
    12036, //Second Life
    12345, //NetBus
    13720, //NetBackup
    13721, //NetBackup
    14567, //Battlefield
    15118, //Dipnet/Oddbob
    19226, //AdminSecure
    19638, //Ensim
    20000, //Usermin
    24800, //Synergy
    25999, //Xfire
    27015, //Half-Life
    27017, //MongoDB
    27374, //Sub7
    28960, //Call of Duty
    31337
  };
  return commonPorts;
}

int main(int argc, char* argv[]) {
  std::string address;
  std::vector<int>  ports = getCommonPort();

  if (argc <=1){
    char*buff[256];
    gethostname((char*)buff,256);
    address = "localhost";///(char*)buff;
  }

  if (argc > 1) {
    address = argv[1];
  }
  if (argc > 2) {
    std::string str(argv[2]);
    if(str.find("all") != std::string::npos){
      ports.clear();
      for (size_t i = 0; i < 65535; i++) {
        ports.push_back(i);
      }
    }else{
      ports = parse_ports_list(str);
    }
  }
  
  std::cout << "Scanning " << address << "...\n";
  std::cout << "Port count " <<  ports.size() << "...\n";
  std::vector<std::thread>threads;
  for (size_t i = 0; i < ports.size(); i++)
  {
    auto port = ports[i];
    try
    {
      threads.push_back( std::thread(port_is_open,address, port));
    }
    catch(const std::exception& e)
    {
      sleep(2000);
      i--;
    }
  }
  
  for (size_t i = 0; i < threads.size(); i++)
  {
    //std::cout << "thread waiting for "  << i << std::endl;
    threads[i].join();
  }
  std::cout << std::flush;
  return 0;
}