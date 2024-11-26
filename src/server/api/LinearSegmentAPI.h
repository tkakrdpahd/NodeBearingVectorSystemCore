// LinearSegmentAPI.h
// Get, Post, Put, Patch, Delete

#ifndef LINEARSEGMENTAPI_H
#define LINEARSEGMENTAPI_H

#include <drogon/drogon.h>

#include "CoordinateConverter.h"
#include "LinearSegment.h"
#include "LinearSegmentDTO.h"

class LinearSegmentAPI {
    private:
        /* data */
        CoordinateConverter _coordinateConverter;
        LinearSegmentDTO _linearSegmentDTO;
    public:
        void SetupRoutes() {
            using namespace drogon;

            app().registerHandler("/linearSegment/get",
                [](const HttpRequestPtr& req,
                    std::function<void(const HttpResponsePtr&)>&& callback) {
                    // Response
                },
                {Get});

            app().registerHandler("/linearSegment/post",
                [](const HttpRequestPtr& req,
                    std::function<void(const HttpResponsePtr&)>&& callback) {
                    // Response
                },
                {Post});
            
            app().registerHandler("/linearSegment/put",
                [](const HttpRequestPtr& req,
                    std::function<void(const HttpResponsePtr&)>&& callback) {
                    // Response
                },
                {Put});

            app().registerHandler("/linearSegment/patch",
                [](const HttpRequestPtr& req,
                    std::function<void(const HttpResponsePtr&)>&& callback) {
                    // Response
                },
                {Patch});

            app().registerHandler("/linearSegment/delete",
                [](const HttpRequestPtr& req,
                    std::function<void(const HttpResponsePtr&)>&& callback) {
                    // Response
                },
                {Delete});
        }

        LinearSegmentAPI(/* args */);
        ~LinearSegmentAPI();
};

#endif // LINEARSEGMENTAPI_H