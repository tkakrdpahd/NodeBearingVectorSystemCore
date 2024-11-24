// Vertex.h
#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <memory>
#include <ostream>
// Google Test Access
#include <gtest/gtest_prod.h>

#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"

/**
 * @brief Vertex class
 * 
 */
class Vertex {
private:
    int index; // Auto assign
    std::unique_ptr<NodeVector> _node; // Essential Component
    std::unique_ptr<std::vector<BearingVector>> _bearingVectorList;

    // NodeVector
    void CreateNodeVector(const NodeVector& node);
    void DeleteNodeVector();

    // BearingVectorList
    void CreateBearingVectorList();
    void UpdateBearingVectorList();
    void DeleteBearingVectorList();

    // Allow Google Test to access private members
    FRIEND_TEST(VertexTest, CreateAndUpdateNodeVector);
    FRIEND_TEST(VertexTest, AddAndReadBearingVectors);
    FRIEND_TEST(VertexTest, UpdateAndDeleteBearingVectors);
    FRIEND_TEST(VertexTest, BearingVectorListLifecycle);
    FRIEND_TEST(VertexTest, DeleteNodeVector);

public:
    // Constructors and Destructors
    Vertex();
    ~Vertex();

    // NodeVector Methods
    void UpdateNodeVector(const NodeVector& node);

    // BearingVector Methods
    void PostBearingVector(const BearingVector& bearing);
    void PutBearingVector(const BearingVector& bearing);
    void DeleteBearingVector();

    // Getter for index
    int GetIndex() const { return index; }

    // Getter Methods
    const NodeVector& ReadNodeVector() const { return *(_node); }
    const std::vector<BearingVector>& ReadBearingVectorList() const { return *(_bearingVectorList); }

    // Output Operator Overload Declaration
    friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex);
};

#endif // VERTEX_H
