#ifndef BEARINGVECTOR_H
#define BEARINGVECTOR_H

#include "Vector3.h"
#include "NodeVector.h"
#include <ostream>

/**
 * @class BearingVector
 * @brief Represents a bearing vector associated with a node.
 */
class BearingVector {
private:
    NodeVector node; ///< Associated NodeVector object.

public:
    int index;          ///< Unique identifier for the BearingVector.
    Vector3 force;      ///< Force applied to the bearing vector.
    Vector3 vector;     ///< The bearing vector in 3D space.

    /**
     * @brief Constructs a BearingVector with the given parameters.
     * @param idx Unique identifier for the BearingVector.
     * @param nd Associated NodeVector object.
     * @param frc Force applied to the bearing vector.
     * @param vec The bearing vector in 3D space.
     */
    BearingVector(int idx, const NodeVector& nd, const Vector3& frc, const Vector3& vec);

    /**
     * @brief Destructor for BearingVector.
     */
    ~BearingVector();

    /**
     * @brief Retrieves the associated NodeVector.
     * @return const NodeVector& Reference to the NodeVector.
     */
    const NodeVector& getNodeVector() const;

    /**
     * @brief Overloads the insertion operator for easy printing.
     * @param os Output stream.
     * @param bearing BearingVector object to print.
     * @return std::ostream& Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const BearingVector& bearing) {
        os << "NodeIndex: " << bearing.index 
           << ", Force: " << bearing.force 
           << ", Vector: " << bearing.vector;
        return os;
    }
};

#endif // BEARINGVECTOR_H
