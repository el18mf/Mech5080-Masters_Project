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
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    system("cls"); // For Windows
}

// Function to convert ASCII hexadecimal string to text
std::string hexToText(const std::string& hexString) {
    std::string text;
    for (size_t i = 0; i < hexString.length(); i += 2) {
        std::string hexPair = hexString.substr(i, 2);
        int byte;
        std::istringstream(hexPair) >> std::hex >> byte;
        text.push_back(static_cast<char>(byte));
    }
    return text;
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
        clearScreen();
        bytesReceived = recvfrom(udpSocket, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&remoteAddr, &addrLen);
        if (bytesReceived == SOCKET_ERROR) {
            handleError("recvfrom failed");
        }

        buffer[bytesReceived] = '\0'; // Null-terminate the received data

        // Convert ASCII hexadecimal string to text
        std::string textData = hexToText(buffer);

        // Open or create the CSV file in append mode
        std::ofstream outputFile(UDPFilePath, std::ios::app);
        if (!outputFile.is_open()) {
            handleError("Failed to open file");
        }

        // Write received data to CSV file
        outputFile << textData << std::endl;

        // Close the file
        outputFile.close();

        // Print received data to terminal
        std::cout << "Received " << bytesReceived << " bytes from " << inet_ntoa(remoteAddr.sin_addr) << ":" << ntohs(remoteAddr.sin_port) << std::endl;
        std::cout << "Data: " << textData << std::endl;
    }

    // Close the socket and clean up Winsock
    closesocket(udpSocket);
    WSACleanup();

    return 0;
}