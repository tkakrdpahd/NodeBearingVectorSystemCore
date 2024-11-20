#include "SurfaceSegment.h"

SurfaceSegment::SurfaceSegment() 
    : index(0), LOD(0), isValid(true),
      nodes(std::make_shared<std::vector<NodeVector>>()), 
      bearings(std::make_shared<std::vector<BearingVector>>()) {}

SurfaceSegment::~SurfaceSegment() {}

void SurfaceSegment::validate() {
    isValid = true;
}

void SurfaceSegment::invalidate() {
    isValid = false;
}

bool SurfaceSegment::isSegmentValid() const {
    return isValid;
}

bool SurfaceSegment::CreateSurfaceSegment() {
    if (!nodes || !bearings) return false;

    // Initialize the data and mark as valid
    nodes->clear();
    bearings->clear();
    validate();
    return true;
}

bool SurfaceSegment::ReadSurfaceSegment() {
    if (!isValid) {
        return false; // Cannot read invalid data
    }

    // Logic to read and validate the data
    return true;
}

bool SurfaceSegment::UpdateSurfaceSegment() {
    if (!isValid) {
        return false; // Cannot update invalid data
    }

    // Perform updates here
    validate(); // Revalidate after update
    return true;
}

bool SurfaceSegment::DeleteSurfaceSegment() {
    if (!isValid) {
        return false; // Cannot delete already invalid data
    }

    nodes->clear();
    bearings->clear();
    validate(); // Ensure valid state
    return true;
}

int SurfaceSegment::getIndex() const {
    return index;
}

void SurfaceSegment::setIndex(int newIndex) {
    if (index != newIndex) {
        index = newIndex;
        invalidate(); // Mark as invalid when data changes
    }
}

int SurfaceSegment::getLOD() const {
    return LOD;
}

void SurfaceSegment::setLOD(int newLOD) {
    if (LOD != newLOD) {
        LOD = newLOD;
        invalidate(); // Mark as invalid when LOD changes
    }
}

std::shared_ptr<std::vector<NodeVector>> SurfaceSegment::getNodes() const {
    return nodes;
}

std::shared_ptr<std::vector<BearingVector>> SurfaceSegment::getBearings() const {
    return bearings;
}

// 출력 연산자 오버로드 정의
std::ostream& operator<<(std::ostream& os, const SurfaceSegment& ss)
{
    os << "SurfaceSegment(ID: " << ss.getIndex() 
       << ", LOD: " << ss.getLOD() 
       << ", isValid: " << (ss.isSegmentValid() ? "true" : "false") 
       << ")";
    return os;
}
