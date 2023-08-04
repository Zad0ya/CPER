#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#ifdef _WIN32
#pragma comment(lib, "iphlpapi.lib")
#else
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

// Функция для получения MAC-адреса сетевого адаптера
std::string getMACAddress()
{
    std::string macAddress;

#ifdef _WIN32
    IP_ADAPTER_INFO adapterInfo[16];
    DWORD bufferSize = sizeof(adapterInfo);

    DWORD result = GetAdaptersInfo(adapterInfo, &bufferSize);
    if (result != ERROR_SUCCESS) {
        std::cerr << "Failed to get MAC address. Error code: " << result << std::endl;
        return macAddress;
    }

    PIP_ADAPTER_INFO adapter = adapterInfo;
    macAddress = std::string(adapter->Address, adapter->Address + adapter->AddressLength);
#else
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return macAddress;
    }

    struct ifreq ifr;
    struct sockaddr_in* sin;

    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ);
    if (ioctl(sock, SIOCGIFHWADDR, &ifr) != -1) {
        sin = (struct sockaddr_in*)&ifr.ifr_addr;
        char* macChar = (char*)&sin->sin_addr.s_addr;

        macAddress = std::string(macChar, macChar + 6);
    }
    else {
        std::cerr << "Failed to get MAC address." << std::endl;
    }

    close(sock);
#endif

    return macAddress;
}


