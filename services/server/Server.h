// Server.h
// Author: Minseok Doo
// Date: 2024.11.22

#ifndef SERVER_H
#define SERVER_H

#include <drogon/drogon.h>

class Server {
public:
    Server() {
        setupRoutes();
    }

    void run() {
        // 서버 실행 (포트 8080)
        drogon::app().addListener("0.0.0.0", 8080);
        drogon::app().run();
    }

private:
    void setupRoutes() {
        using namespace drogon;

        // GET /hello 엔드포인트 설정
        app().registerHandler("/hello",
            [](const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback) {
                // 응답 생성
                auto resp = HttpResponse::newHttpResponse();
                resp->setBody(std::string("Hello, World!")); // std::string으로 변환
                callback(resp);
            },
            {Get});

        // POST /echo 엔드포인트 설정
        app().registerHandler("/echo",
            [](const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback) {
                // 요청 본문을 그대로 응답으로 반환
                auto resp = HttpResponse::newHttpResponse();
                resp->setBody(std::string(req->getBody()));
                callback(resp);
            },
            {Post});
    }
};

#endif // SERVER_H
