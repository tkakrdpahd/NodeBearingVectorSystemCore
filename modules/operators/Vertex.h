/**
 * Vertex.h
 * Linked File: Vertex.cpp
 */
#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <memory>
// Google Test Access
#include <gtest/gtest_prod.h>

#include "Vector3.h"
#include "NodeVector.h"
#include "BearingVector.h"

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
        void ReadBearingVectorList() const;
        void UpdateBearingVectorList();
        void DeleteBearingVectorList();

        // Allow Google Test to access private members
        FRIEND_TEST(VertexTest, CreateAndUpdateNodeVector);
        FRIEND_TEST(VertexTest, AddAndReadBearingVectors);
        FRIEND_TEST(VertexTest, UpdateAndDeleteBearingVectors);
        FRIEND_TEST(VertexTest, BearingVectorListLifecycle);
        FRIEND_TEST(VertexTest, DeleteNodeVector);
    public:
        // NodeVector
        void ReadNodeVector() const;
        void UpdateNodeVector(const NodeVector& node);

        // BearingVector
        void PostBearingVector(const BearingVector& bearing);
        void GetBearingVector() const;
        void PutBearingVector(const BearingVector& bearing);
        void DeleteBearingVector();

        Vertex();
        ~Vertex();

        // Getter for index
        int GetIndex() const { return index; }
};

#endif // VERTEX_H
