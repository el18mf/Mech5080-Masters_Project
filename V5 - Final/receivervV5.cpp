#include <iostream>
#include <fstream>
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <chrono>
#include <thread>
#include <ctime>            // Include for time functions
#include <sstream>          // Include for stringstream
#include <vector>           // Include for vector
#include <iomanip>          // Include for hex parsing

const char* UDPFilePath = "C:\\Users\\Mathew\\Desktop\\rF2_data_files\\Received.csv";

// Function to handle errors
void handleError(const std::string& message) {
    std::cerr << "Error: " << message << " - " << WSAGetLastError() << std::endl;
    WSACleanup();
    exit(EXIT_FAILURE);
}

// Function to clear the terminal screen
void clearScreen() {
// Wait for the specified duration
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    system("cls"); // For Windows

    // For Linux/Unix, use "clear":
    // system("clear");
}

// Function to convert hexadecimal string to bytes
std::vector<unsigned char> hexStringToBytes(const std::string& hex) {
    std::vector<unsigned char> bytes;
    std::istringstream iss(hex);

    // Ensure stringstream sets hexadecimal conversion mode
    iss >> std::hex;

    unsigned int byte;
    while (iss >> byte) {
        bytes.push_back(static_cast<unsigned char>(byte));
    }

    return bytes;
}

int main() {
    // Initialize Winsock
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
        handleError("WSAStartup failed");
    }

    // Create a UDP socket
    SOCKET udpSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udpSocket == INVALID_SOCKET) {
        handleError("Failed to create socket");
    }

    // Bind the socket to the local address and port
    sockaddr_in localAddr;
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(10815); // Specify your UDP port here
    localAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(udpSocket, (sockaddr*)&localAddr, sizeof(localAddr)) == SOCKET_ERROR) {
        handleError("Bind failed");
    }

    std::cout << "Waiting for data on UDP port 10815..." << std::endl;

    // Receive data from the UDP socket and write to CSV file
    char buffer[1024];
    sockaddr_in remoteAddr;
    int addrLen = sizeof(remoteAddr);
    int bytesReceived;
    
    while (true) {
        // Clear the terminal screen before each update
        clearScreen();
        bytesReceived = recvfrom(udpSocket, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&remoteAddr, &addrLen);
        if (bytesReceived == SOCKET_ERROR) {
            handleError("recvfrom failed");
        }

        buffer[bytesReceived] = '\0'; // Null-terminate the received data

        // Process the received data
        std::string hexData(buffer);
        std::vector<unsigned char> bytes = hexStringToBytes(hexData);

        // Open or create the CSV file in append mode
        std::ofstream outputFile(UDPFilePath, std::ios::app);
        if (!outputFile.is_open()) {
            handleError("Failed to open file");
        }

        // Write received data to CSV file
        for (unsigned char byte : bytes) {
            outputFile << static_cast<int>(byte) << ",";
        }
        outputFile << std::endl;

        // Close the file
        outputFile.close();

        // Print received data to terminal
        std::cout << "Received " << bytesReceived << " bytes from " << inet_ntoa(remoteAddr.sin_addr) << ":" << ntohs(remoteAddr.sin_port) << std::endl;
        std::cout << "Type: Roll, Pitch, HeavAccel,  Yaw,  SwayAccel, SurgeAcc" << std::endl;
        std::cout << "Data: " << hexData << std::endl;
    }

    // Close the socket and clean up Winsock
    closesocket(udpSocket);
    WSACleanup();

    return 0;
}