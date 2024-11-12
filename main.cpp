/**
 * main.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 11, 2024
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <thread>

#include "Vector3.h"
#include "CoordinateConverter.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "LinerSegment.h"
#include "AttributesManager.h"
#include "SocketServer.h"

// 전역 변수 선언
AttributesManager attributesManager;

// 테스트 함수들
void NodeVectorTest(AttributesManager& _attributesManager) {
    // 여러 개의 SphericalNodeVector 생성 및 NodeVector 초기화 (PI 단위 사용)
    Vector3 sphericalCoords1(10.0f, static_cast<float>(M_PI / 2), static_cast<float>(M_PI / 4)); // r, theta, phi
    Vector3 sphericalCoords2(15.0f, static_cast<float>(M_PI / 4), static_cast<float>(M_PI / 2)); // r, theta, phi

    // SphericalNodeVector 생성자 호출: (int, Vector3)
    SphericalNodeVector sphericalNode1(1, sphericalCoords1);
    SphericalNodeVector sphericalNode2(2, sphericalCoords2);

    // NodeVector 생성자 호출 (SphericalNodeVector 사용)
    NodeVector node01(sphericalNode1);
    NodeVector node02(sphericalNode2);

    // AttributesManager를 사용하여 NodeVector 생성 및 저장
    _attributesManager.CreateNodeVector(node01);
    _attributesManager.CreateNodeVector(node02);
}

void BearingVectorTest(AttributesManager& _attributesManager) {
    // Bearing Vector 생성 및 초기화
    const auto& storedNodes = _attributesManager.getNodeVectors();
    if (storedNodes.empty()) {
        std::cerr << "No nodes available for creating BearingVectors." << std::endl;
        return;
    }

    // 첫 번째 노드를 사용하여 BearingVectors 생성
    NodeVector node = storedNodes[0];

    // Create a BearingVector
    int bearingIndex = 1;
    // Angles vector: angles.x = depth, angles.y = phi_i, angles.z = theta_i
    // Let's set depth = 0.5, phi = 30°, theta = 60°
    Vector3 bearingAngles(0.5f, 30.0f * 180, 60.0f * 180);
    // Force vector components
    Vector3 bearingForce(10.0f, 5.0f, 2.0f);

    BearingVector bearingVector1(bearingIndex, node, bearingAngles, bearingForce);

    // AttributesManager를 사용하여 BearingVector 생성 및 저장
    _attributesManager.CreateBearingVector(bearingVector1);
}

void LinerSegmentTest(AttributesManager& _attributesManager) {
    // NodeVectorWithBearing 초기화
    NodeVectorWithBearing node1;
    NodeVectorWithBearing node2;

    // AttributesManager에서 NodeVector와 해당 인덱스에 맞는 BearingVector 가져오기
    const auto& storedNodes = _attributesManager.getNodeVectors();
    const auto& storedBearings = _attributesManager.getBearingVectors();

    if (storedNodes.size() >= 2) {
        node1.node = storedNodes[0];
        node2.node = storedNodes[1];

        // Node 1과 Node 2에 해당하는 BearingVectors 추가
        for (const auto& bearing : storedBearings) {
            if (bearing.getNodeIndex() == node1.node.getSphericalNodeVector().index) {
                node1.bearings.push_back(bearing);
                std::cout << "Bearing vector added to Node 1, Node Index: " << node1.node.getSphericalNodeVector().index << std::endl;
            } else if (bearing.getNodeIndex() == node2.node.getSphericalNodeVector().index) {
                node2.bearings.push_back(bearing);
                std::cout << "Bearing vector added to Node 2, Node Index: " << node2.node.getSphericalNodeVector().index << std::endl;
            }
        }

        // Bearing Vector가 잘 추가되었는지 확인
        std::cout << "Node 1 bearing vectors count: " << node1.bearings.size() << std::endl;
        std::cout << "Node 2 bearing vectors count: " << node2.bearings.size() << std::endl;

        // LinerSegment 생성 및 AttributesManager에 추가
        LinerSegment linerSegment(node1, node2, 50);

        // AttributesManager를 사용하여 LinerSegment 생성 및 저장
        _attributesManager.CreateLinerSegment(linerSegment);

        // LinerSegment의 샘플링된 점 출력
        linerSegment.samplingBezierCurve(); // 함수 이름 변경됨
        const auto& sampledPoints = linerSegment.getSampledPoints();
        if (!sampledPoints.empty()) {
            std::cout << "Sampled Points from LinerSegment:" << std::endl;
            for (const auto& point : sampledPoints) {
                std::cout << "(x: " << point.x << ", y: " << point.y << ", z: " << point.z << ")" << std::endl;
            }
        } else {
            std::cout << "No sampled points generated from LinerSegment." << std::endl;
        }
    } else {
        std::cout << "Not enough NodeVectors in AttributesManager to create a LinerSegment." << std::endl;
    }
}

void AttributesManagerTest(AttributesManager& _attributesManager) {
    // NodeVectorTest 함수를 호출하여 NodeVector 생성 및 저장
    NodeVectorTest(_attributesManager);

    // BearingVectorTest 함수를 호출하여 BearingVector 생성 및 저장
    BearingVectorTest(_attributesManager);

    // LinerSegmentTest 함수를 호출하여 LinerSegment 생성 및 저장
    LinerSegmentTest(_attributesManager);
}

// Socket 서버 테스트 함수로 AttributesManager의 데이터를 반환하게 함
void SocketServerTest(AttributesManager& attributesManager) {
    int serverPort = 8080;
    SocketServer server(serverPort, attributesManager);

    if (server.startServer()) {
        server.listenForClients();
    } else {
        std::cerr << "Failed to start the server." << std::endl;
    }
}

int main() {
    // 테스트 함수 호출 (데이터 추가)
    AttributesManagerTest(attributesManager);

    // 서버를 실행하여 클라이언트 요청에 응답 (별도의 스레드)
    std::thread serverThread(SocketServerTest, std::ref(attributesManager));
    serverThread.join(); // 서버 스레드가 종료될 때까지 메인 스레드가 대기

    return 0;
}
