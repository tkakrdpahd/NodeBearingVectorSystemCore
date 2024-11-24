// Vertex.cpp
#include "Vertex.h"
#include <iostream>

// 정적 변수로 글로벌 인덱스 관리
static int global_vertex_index = 0;

// Constructor
Vertex::Vertex()
    : index(++global_vertex_index), _node(nullptr), _bearingVectorList(nullptr)
{
    // NodeVector 및 BearingVectorList 초기화
    CreateNodeVector(NodeVector(0, Vector3(0.0f, 0.0f, 0.0f)));
    CreateBearingVectorList();

    std::cout << "Vertex created with Index: " << index << std::endl;
}

// Destructor
Vertex::~Vertex()
{
    DeleteBearingVectorList();
    DeleteNodeVector();
    std::cout << "Vertex with Index: " << index << " destroyed." << std::endl;
}

// Private Methods for NodeVector Management

/**
 * @brief NodeVector를 생성합니다.
 *        초기화 시 index는 0, Vector3는 (0,0,0)으로 설정됩니다.
 * @param node 생성할 NodeVector 객체
 */
void Vertex::CreateNodeVector(const NodeVector& node)
{
    if (!_node)
    {
        _node = std::make_unique<NodeVector>(node);
        std::cout << "NodeVector created with Index: " << node.Index 
                  << " and Vector3(0,0,0)." << std::endl;
    }
    else
    {
        std::cerr << "NodeVector already exists. Use UpdateNodeVector to modify." << std::endl;
    }
}

/**
 * @brief NodeVector를 삭제합니다.
 */
void Vertex::DeleteNodeVector()
{
    if (_node)
    {
        _node.reset();
        std::cout << "NodeVector deleted." << std::endl;
    }
    else
    {
        std::cerr << "NodeVector is already deleted or not initialized." << std::endl;
    }
}

// Private Methods for BearingVectorList Management

/**
 * @brief BearingVector 리스트를 생성합니다.
 */
void Vertex::CreateBearingVectorList()
{
    if (!_bearingVectorList)
    {
        _bearingVectorList = std::make_unique<std::vector<BearingVector>>();
        std::cout << "BearingVectorList created." << std::endl;
    }
}

/**
 * @brief BearingVector 리스트를 읽어들입니다.
 */
void Vertex::ReadBearingVectorList() const
{
    if (_bearingVectorList && !_bearingVectorList->empty())
    {
        for (const auto& bearing : *_bearingVectorList)
        {
            std::cout << bearing << std::endl;
        }
    }
    else
    {
        std::cerr << "BearingVectorList is empty or not initialized." << std::endl;
    }
}

/**
 * @brief BearingVector 리스트를 업데이트합니다.
 *        현재는 모든 BearingVector의 Force를 (1,1,1)로 업데이트하는 예시입니다.
 *        필요에 따라 로직을 수정할 수 있습니다.
 */
void Vertex::UpdateBearingVectorList()
{
    if (_bearingVectorList && !_bearingVectorList->empty())
    {
        for (auto& bearing : *_bearingVectorList)
        {
            bearing.Force = Vector3(1.0f, 1.0f, 1.0f);
        }
        std::cout << "BearingVectorList updated." << std::endl;
    }
    else
    {
        std::cerr << "BearingVectorList is empty or not initialized." << std::endl;
    }
}

/**
 * @brief BearingVector 리스트를 삭제합니다.
 */
void Vertex::DeleteBearingVectorList()
{
    if (_bearingVectorList)
    {
        _bearingVectorList->clear();
        _bearingVectorList.reset();
        std::cout << "BearingVectorList deleted." << std::endl;
    }
    else
    {
        std::cerr << "BearingVectorList is already deleted or not initialized." << std::endl;
    }
}

// Public Methods for NodeVector Management

/**
 * @brief NodeVector의 데이터를 읽어들입니다.
 */
void Vertex::ReadNodeVector() const
{
    if (_node)
    {
        std::cout << *_node << std::endl;
    }
    else
    {
        std::cerr << "NodeVector is not initialized." << std::endl;
    }
}

/**
 * @brief NodeVector의 데이터를 업데이트합니다.
 * @param node 새로운 NodeVector 데이터
 */
void Vertex::UpdateNodeVector(const NodeVector& node)
{
    if (_node)
    {
        *_node = node;
        std::cout << "NodeVector updated to Index: " << node.Index
                  << ", Vector3: " << node.Vector << std::endl;
    }
    else
    {
        std::cerr << "NodeVector is not initialized. Use CreateNodeVector to create it first." << std::endl;
    }
}

// Public Methods for BearingVector Management

/**
 * @brief 새로운 BearingVector를 추가합니다.
 * @param bearing 추가할 BearingVector 객체
 */
void Vertex::PostBearingVector(const BearingVector& bearing)
{
    if (_bearingVectorList)
    {
        _bearingVectorList->emplace_back(bearing);
        std::cout << "BearingVector added to the list." << std::endl;
    }
    else
    {
        std::cerr << "BearingVectorList is not initialized." << std::endl;
    }
}

/**
 * @brief 모든 BearingVector를 출력합니다.
 */
void Vertex::GetBearingVector() const
{
    ReadBearingVectorList();
}

/**
 * @brief 특정 BearingVector를 업데이트합니다.
 *        현재는 리스트의 첫 번째 BearingVector를 업데이트하는 예시입니다.
 * @param bearing 업데이트할 BearingVector 객체
 */
void Vertex::PutBearingVector(const BearingVector& bearing)
{
    if (_bearingVectorList)
    {
        if (!_bearingVectorList->empty())
        {
            (*_bearingVectorList)[0] = bearing;
            std::cout << "First BearingVector updated." << std::endl;
        }
        else
        {
            std::cerr << "BearingVectorList is empty. Use PostBearingVector to add new BearingVectors." << std::endl;
        }
    }
    else
    {
        std::cerr << "BearingVectorList is not initialized." << std::endl;
    }
}

/**
 * @brief 마지막 BearingVector를 삭제합니다.
 */
void Vertex::DeleteBearingVector()
{
    if (_bearingVectorList && !_bearingVectorList->empty())
    {
        _bearingVectorList->pop_back();
        std::cout << "Last BearingVector removed from the list." << std::endl;
    }
    else
    {
        std::cerr << "No BearingVectors to delete." << std::endl;
    }
}
