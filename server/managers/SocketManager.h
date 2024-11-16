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
    // 실행 상태 플래그 (ServerManager에서 주입)
    std::atomic<bool>& isRunning;

    int serverSocket;                // 서버 소켓
    int port;                        // 포트 번호
    struct sockaddr_in serverAddress;

    int findPortNumber();            // 가용 포트를 찾는 내부 함수

public:
    SocketManager(std::atomic<bool>& runningFlag); // 플래그 주입받는 생성자
    ~SocketManager();

    bool StartServer();              // 서버 시작
    void ListenForClients();         // 클라이언트 연결 처리
    void sendResponse(int clientSocket, const std::string& message); // 응답 전송
    void closeServer();              // 서버 종료

    int getPort() const;             // 현재 포트 반환
    int acceptClient();              // 클라이언트 연결 수락
};

#endif // SOCKETMANAGER_H
