/**
 * socketManager.h
 * Purpose: Manage Socket Server
 */
#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <string>
#include <netinet/in.h>
#include <atomic>

class SocketManager {
private:
    int serverSocket;                // 서버 소켓
    int port;                        // 포트 번호
    struct sockaddr_in serverAddress;
    std::atomic<bool> isRunning;     // 서버 실행 상태

    int findPortNumber();            // 가용 포트를 찾는 내부 함수

public:
    SocketManager();
    ~SocketManager();

    bool StartServer();              // 서버 시작
    void ListenForClients();         // 클라이언트 연결 처리
    void sendResponse(int clientSocket, const std::string& message); // 응답 전송
    void closeServer();              // 서버 종료

    int getPort() const;             // 현재 포트 반환
    bool isServerRunning() const;    // 서버 실행 상태 확인
    int acceptClient();              // 클라이언트 연결 수락
};

#endif // SOCKETMANAGER_H
