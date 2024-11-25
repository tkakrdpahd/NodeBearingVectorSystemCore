// Server.h
// Author: Minseok Doo
// Date: 2024.11.22

#ifndef SERVER_H
#define SERVER_H

#include <drogon/drogon.h>

#include "LinearSegment.h"
#include "LinearSegmentDTO.h"

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

        // GET /linearSegment/get 엔드포인트 설정
        app().registerHandler("/linearSegment/get",
            [](const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback) {
                // 응답 생성
                // auto resp = HttpResponse::newHttpResponse();
                // resp->setBody(std::string("Hello, World!"));
                // callback(resp);

                // Get data;
                // Return to LinearSegmentDTO.h;
                // Get Struct from LinearSegmentDTO.h;
                // Return to Data handler LinearSegment.h;
                // Return data from LinearSegment.h;
            },
            {Get});

        // POST /echo 엔드포인트 설정
        app().registerHandler("/linearSegment/post",
            [](const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback) {
                // 요청 본문을 그대로 응답으로 반환
                // auto resp = HttpResponse::newHttpResponse();
                // resp->setBody(std::string(req->getBody()));
                // callback(resp);
            },
            {Post});
    }
};

#endif // SERVER_H
