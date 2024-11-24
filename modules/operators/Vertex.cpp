// Vertex.cpp
#include "Vertex.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
    os << "Vertex(Index: " << vertex.GetIndex() << ", NodeVector: " << vertex.ReadNodeVector() << ")";
    return os;
}

// Constructors and Destructors
Vertex::Vertex()
    : index(0),
      _node(std::make_unique<NodeVector>(0, Vector3(0.0f, 0.0f, 0.0f))), // 필수 매개변수 전달
      _bearingVectorList(std::make_unique<std::vector<BearingVector>>()) {}

Vertex::~Vertex() {
    // Cleanup if necessary
}

// NodeVector Methods
void Vertex::UpdateNodeVector(const NodeVector& node) {
    *_node = node;
    index = node.Index; // Vertex의 index를 NodeVector의 index와 동기화
}

void Vertex::CreateNodeVector(const NodeVector& node) {
    _node = std::make_unique<NodeVector>(node);
}

void Vertex::DeleteNodeVector() {
    _node.reset();
}

// BearingVector Methods
void Vertex::PostBearingVector(const BearingVector& bearing) {
    _bearingVectorList->push_back(bearing);
}

void Vertex::PutBearingVector(const BearingVector& bearing) {
    if (!_bearingVectorList->empty()) {
        (*_bearingVectorList)[_bearingVectorList->size() - 1] = bearing;
    }
}

void Vertex::DeleteBearingVector() {
    if (!_bearingVectorList->empty()) {
        _bearingVectorList->pop_back();
    }
}
