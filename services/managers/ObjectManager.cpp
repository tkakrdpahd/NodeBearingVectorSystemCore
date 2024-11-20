/**
 * ObjectManager.cpp
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 13, 2024
 * Last Modified: Nov 16, 2024
 * 
 * Purpose: Implementation of ObjectManager methods
 */

#include "ObjectManager.h"
#include "LinearSegment.h"
#include "SurfaceSegment.h"
#include <algorithm>

// 생성자
ObjectManager::ObjectManager(const std::string& managerName)
    : index(0), max(0.0f), min(0.0f),
      name(managerName),
      nodeVectors(std::make_unique<std::vector<NodeVector>>()),
      bearingVectors(std::make_unique<std::vector<BearingVector>>()),
      linearSegments(std::make_unique<std::vector<LinearSegment>>()),
      surfaceSegments(std::make_unique<std::vector<SurfaceSegment>>())
{
    std::cout << "ObjectManager '" << name << "' 생성됨.\n";
}

// 소멸자
ObjectManager::~ObjectManager()
{
    std::cout << "ObjectManager '" << name << "' 소멸됨.\n";
}

// Getters and Setters for name
std::string ObjectManager::GetName() const {
    return name;
}

void ObjectManager::SetName(const std::string& newName) {
    name = newName;
    std::cout << "ObjectManager 이름이 '" << newName << "'으로 변경됨.\n";
}

// NodeVector Methods
bool ObjectManager::createNodeVector(int id, const Vector3& position) {
    // 중복된 ID가 있는지 확인
    if (findIndexById(*nodeVectors, id).has_value()) {
        std::cerr << "NodeVector 추가 실패: 중복된 ID " << id << " 존재.\n";
        return false;
    }
    nodeVectors->emplace_back(id, position);
    std::cout << "NodeVector 추가됨. ID: " << id << ", Position: " << position << "\n";
    return true;
}

std::optional<NodeVector> ObjectManager::readNodeVector(int id) const {
    auto it = findIndexById(*nodeVectors, id);
    if (it.has_value()) {
        std::cout << "NodeVector 읽기 성공. ID: " << id << "\n";
        return nodeVectors->at(it.value());
    }
    std::cerr << "NodeVector 읽기 실패: ID " << id << " 존재하지 않음.\n";
    return std::nullopt;
}

bool ObjectManager::updateNodeVector(int id, const Vector3& newPosition) {
    auto it = findIndexById(*nodeVectors, id);
    if (it.has_value()) {
        nodeVectors->at(it.value()).Vector = newPosition;
        std::cout << "NodeVector 업데이트 성공. ID: " << id << ", New Position: " << newPosition << "\n";
        return true;
    }
    std::cerr << "NodeVector 업데이트 실패: ID " << id << " 존재하지 않음.\n";
    return false;
}

bool ObjectManager::deleteNodeVector(int id) {
    auto it = findIndexById(*nodeVectors, id);
    if (it.has_value()) {
        nodeVectors->erase(nodeVectors->begin() + it.value());
        std::cout << "NodeVector 삭제됨. ID: " << id << "\n";
        return true;
    }
    std::cerr << "NodeVector 삭제 실패: ID " << id << " 존재하지 않음.\n";
    return false;
}

// BearingVector Methods
bool ObjectManager::createBearingVector(const NodeVector& node, const Vector3& force, const Vector3& vector) {
    // NodeVector의 ID를 기준으로 BearingVector의 중복 여부 확인
    auto it = std::find_if(bearingVectors->begin(), bearingVectors->end(),
                           [&](const BearingVector& bv) {
                               return bv.Node.Index == node.Index;
                           });
    if (it != bearingVectors->end()) {
        std::cerr << "BearingVector 추가 실패: Node ID " << node.Index << "에 대한 BearingVector 이미 존재.\n";
        return false;
    }
    bearingVectors->emplace_back(node, force, vector);
    std::cout << "BearingVector 추가됨. Node ID: " << node.Index << ", Force: " << force << ", Vector: " << vector << "\n";
    return true;
}

std::optional<BearingVector> ObjectManager::readBearingVector(const NodeVector& node) const {
    auto it = std::find_if(bearingVectors->begin(), bearingVectors->end(),
                           [&](const BearingVector& bv) {
                               return bv.Node.Index == node.Index;
                           });
    if (it != bearingVectors->end()) {
        std::cout << "BearingVector 읽기 성공. Node ID: " << node.Index << "\n";
        return *it;
    }
    std::cerr << "BearingVector 읽기 실패: Node ID " << node.Index << "에 대한 BearingVector 존재하지 않음.\n";
    return std::nullopt;
}

bool ObjectManager::updateBearingVector(const NodeVector& node, const Vector3& newForce) {
    auto it = std::find_if(bearingVectors->begin(), bearingVectors->end(),
                           [&](BearingVector& bv) {
                               return bv.Node.Index == node.Index;
                           });
    if (it != bearingVectors->end()) {
        it->Force = newForce;
        std::cout << "BearingVector 업데이트 성공. Node ID: " << node.Index << ", New Force: " << newForce << "\n";
        return true;
    }
    std::cerr << "BearingVector 업데이트 실패: Node ID " << node.Index << "에 대한 BearingVector 존재하지 않음.\n";
    return false;
}

bool ObjectManager::deleteBearingVector(const NodeVector& node) {
    auto it = std::find_if(bearingVectors->begin(), bearingVectors->end(),
                           [&](const BearingVector& bv) {
                               return bv.Node.Index == node.Index;
                           });
    if (it != bearingVectors->end()) {
        bearingVectors->erase(it);
        std::cout << "BearingVector 삭제됨. Node ID: " << node.Index << "\n";
        return true;
    }
    std::cerr << "BearingVector 삭제 실패: Node ID " << node.Index << "에 대한 BearingVector 존재하지 않음.\n";
    return false;
}

// LinearSegment Methods
bool ObjectManager::createLinearSegment(const NodeVector& startNode, const std::vector<BearingVector>& startBearing,
                                       const NodeVector& endNode, const std::vector<BearingVector>& endBearing) {
    linearSegments->emplace_back(startNode, startBearing, endNode, endBearing);
    std::cout << "LinearSegment 추가됨. Start Node ID: " << startNode.Index << ", End Node ID: " << endNode.Index << "\n";
    return true;
}

std::vector<LinearSegment> ObjectManager::readAllLinearSegments() const {
    return *linearSegments;
}

bool ObjectManager::deleteLinearSegment(const NodeVector& startNode, const NodeVector& endNode) {
    auto it = std::find_if(linearSegments->begin(), linearSegments->end(),
                           [&](const LinearSegment& ls) {
                               return ls.getStartNode().Index == startNode.Index &&
                                      ls.getEndNode().Index == endNode.Index;
                           });
    if (it != linearSegments->end()) {
        linearSegments->erase(it);
        std::cout << "LinearSegment 삭제됨. Start Node ID: " << startNode.Index << ", End Node ID: " << endNode.Index << "\n";
        return true;
    }
    std::cerr << "LinearSegment 삭제 실패: 해당 세그먼트를 찾을 수 없습니다.\n";
    return false;
}

// SurfaceSegment Methods
bool ObjectManager::createSurfaceSegment(int id) {
    // 중복된 ID가 있는지 확인
    for (const auto& ss : *surfaceSegments) {
        if (ss.getIndex() == id) {
            std::cerr << "SurfaceSegment 추가 실패: 중복된 ID " << id << " 존재.\n";
            return false;
        }
    }
    surfaceSegments->emplace_back();
    surfaceSegments->back().setIndex(id);
    std::cout << "SurfaceSegment 추가됨. ID: " << id << "\n";
    return true;
}

std::vector<SurfaceSegment> ObjectManager::readAllSurfaceSegments() const {
    return *surfaceSegments;
}

bool ObjectManager::deleteSurfaceSegment(int id) {
    auto it = std::find_if(surfaceSegments->begin(), surfaceSegments->end(),
                           [&](const SurfaceSegment& ss) {
                               return ss.getIndex() == id;
                           });
    if (it != surfaceSegments->end()) {
        surfaceSegments->erase(it);
        std::cout << "SurfaceSegment 삭제됨. ID: " << id << "\n";
        return true;
    }
    std::cerr << "SurfaceSegment 삭제 실패: ID " << id << " 존재하지 않음.\n";
    return false;
}

// Manager Functions
void ObjectManager::SaveAll() {
    // JSON 변환 및 저장 로직 구현
    // JsonConverter::ConvertToJson(*nodeVectors, *bearingVectors, *linearSegments, *surfaceSegments);
    // std::cout << "모든 ObjectManager 데이터 저장됨.\n";
}

void ObjectManager::DeleteAll() {
    nodeVectors->clear();
    bearingVectors->clear();
    linearSegments->clear();
    surfaceSegments->clear();
    std::cout << "모든 ObjectManager 데이터 삭제됨.\n";
}

// 출력 연산자 오버로드 정의
std::ostream& operator<<(std::ostream& os, const ObjectManager& obj)
{
    os << "ObjectManager(Name: " << obj.name << ", Index: " << obj.index << ", Max: " << obj.max << ", Min: " << obj.min << ")\n";
    os << "  NodeVectors:\n";
    for (const auto& nv : *(obj.nodeVectors)) {
        os << "    " << nv << "\n";
    }
    os << "  BearingVectors:\n";
    for (const auto& bv : *(obj.bearingVectors)) {
        os << "    " << bv << "\n";
    }
    os << "  LinearSegments:\n";
    for (const auto& ls : *(obj.linearSegments)) {
        os << "    " << ls << "\n";
    }
    os << "  SurfaceSegments:\n";
    for (const auto& ss : *(obj.surfaceSegments)) {
        os << "    " << ss << "\n";
    }
    return os;
}
