/**
 * YamlConverter.cpp
 * Implementation of the YamlConverter class
 * Security: Top Secret
 * Author: Minseok Doo
 * Date: Oct 20, 2024
 * Last Modified: Nov 11, 2024
 */

#include "YamlConverter.h"
#include "AttributesManager.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>

YamlConverter::YamlConverter() {}

YamlConverter::~YamlConverter() {}

std::string YamlConverter::ToString(const AttributesManager &attributesManager) {
    YAML::Emitter out;
    Attributes attributes = attributesManager.ReadAllAttributes();

    out << YAML::BeginMap;

    // Node Vectors
    out << YAML::Key << "NodeVectors";
    out << YAML::BeginSeq;
    for (const auto& node : attributes.nodeVectors) {
        auto spherical = node.getSphericalNodeVector();
        auto cartesian = node.getCartesianNodeVector();

        out << YAML::BeginMap;
        // Include both spherical and cartesian representations
        out << YAML::Key << "index" << YAML::Value << spherical.index;
        out << YAML::Key << "spherical" << YAML::BeginMap;
        out << YAML::Key << "r" << YAML::Value << spherical.sphericalCoords.x;
        out << YAML::Key << "theta" << YAML::Value << spherical.sphericalCoords.y;
        out << YAML::Key << "phi" << YAML::Value << spherical.sphericalCoords.z;
        out << YAML::EndMap;

        out << YAML::Key << "cartesian" << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << cartesian.cartesianCoords.x;
        out << YAML::Key << "y" << YAML::Value << cartesian.cartesianCoords.y;
        out << YAML::Key << "z" << YAML::Value << cartesian.cartesianCoords.z;
        out << YAML::EndMap;

        out << YAML::EndMap;
    }
    out << YAML::EndSeq;

    // Bearing Vectors
    out << YAML::Key << "BearingVectors";
    out << YAML::BeginSeq;
    for (const auto& bearing : attributes.bearingVectors) {
        out << YAML::BeginMap;
        out << YAML::Key << "nodeIndex" << YAML::Value << bearing.getNodeIndex();
        out << YAML::Key << "depth" << YAML::Value << bearing.getDepth();

        out << YAML::Key << "angles" << YAML::BeginMap;
        out << YAML::Key << "phi" << YAML::Value << bearing.getPhi();
        out << YAML::Key << "theta" << YAML::Value << bearing.getTheta();
        out << YAML::EndMap;

        auto force = bearing.getForce();
        out << YAML::Key << "force" << YAML::BeginMap;
        out << YAML::Key << "f_x" << YAML::Value << force.force.x;
        out << YAML::Key << "f_y" << YAML::Value << force.force.y;
        out << YAML::Key << "f_z" << YAML::Value << force.force.z;
        out << YAML::EndMap;

        out << YAML::EndMap;
    }
    out << YAML::EndSeq;

    // Liner Segments
    out << YAML::Key << "LinerSegments";
    out << YAML::BeginSeq;
    for (const auto& segment : attributes.linerSegments) {
        out << YAML::BeginMap;

        // LinerSegmentData를 사용하여 모든 멤버 변수 출력
        LinerSegmentData segmentData = segment.returnLinerSegmentData();

        // LinerBufferIndex 출력
        out << YAML::Key << "LinerBufferIndex" << YAML::Value << segmentData.linerBufferIndex;

        // NodeStart 정보 출력
        out << YAML::Key << "NodeStart";
        out << YAML::BeginMap;
        auto sphericalStart = segmentData.nodeStart.getSphericalNodeVector();
        auto cartesianStart = segmentData.nodeStart.getCartesianNodeVector();
        out << YAML::Key << "index" << YAML::Value << sphericalStart.index;
        out << YAML::Key << "spherical" << YAML::BeginMap;
        out << YAML::Key << "r" << YAML::Value << sphericalStart.sphericalCoords.x;
        out << YAML::Key << "theta" << YAML::Value << sphericalStart.sphericalCoords.y;
        out << YAML::Key << "phi" << YAML::Value << sphericalStart.sphericalCoords.z;
        out << YAML::EndMap;
        out << YAML::Key << "cartesian" << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << cartesianStart.cartesianCoords.x;
        out << YAML::Key << "y" << YAML::Value << cartesianStart.cartesianCoords.y;
        out << YAML::Key << "z" << YAML::Value << cartesianStart.cartesianCoords.z;
        out << YAML::EndMap;
        out << YAML::EndMap;

        // NodeEnd 정보 출력
        out << YAML::Key << "NodeEnd";
        out << YAML::BeginMap;
        auto sphericalEnd = segmentData.nodeEnd.getSphericalNodeVector();
        auto cartesianEnd = segmentData.nodeEnd.getCartesianNodeVector();
        out << YAML::Key << "index" << YAML::Value << sphericalEnd.index;
        out << YAML::Key << "spherical" << YAML::BeginMap;
        out << YAML::Key << "r" << YAML::Value << sphericalEnd.sphericalCoords.x;
        out << YAML::Key << "theta" << YAML::Value << sphericalEnd.sphericalCoords.y;
        out << YAML::Key << "phi" << YAML::Value << sphericalEnd.sphericalCoords.z;
        out << YAML::EndMap;
        out << YAML::Key << "cartesian" << YAML::BeginMap;
        out << YAML::Key << "x" << YAML::Value << cartesianEnd.cartesianCoords.x;
        out << YAML::Key << "y" << YAML::Value << cartesianEnd.cartesianCoords.y;
        out << YAML::Key << "z" << YAML::Value << cartesianEnd.cartesianCoords.z;
        out << YAML::EndMap;
        out << YAML::EndMap;

        // LevelOfDetail과 alpha 출력
        out << YAML::Key << "LevelOfDetail" << YAML::Value << segmentData.levelOfDetail;
        out << YAML::Key << "alpha" << YAML::Value << segmentData.alpha;

        // Control Points 출력
        const auto& controlPoints = segment.getControlPoints();
        out << YAML::Key << "controlPoints" << YAML::BeginSeq;
        for (const auto& point : controlPoints) {
            out << YAML::BeginMap;
            out << YAML::Key << "x" << YAML::Value << point.x;
            out << YAML::Key << "y" << YAML::Value << point.y;
            out << YAML::Key << "z" << YAML::Value << point.z;
            out << YAML::EndMap;
        }
        out << YAML::EndSeq;

        // Sampled Points 출력
        const auto& sampledPoints = segment.getSampledPoints();
        out << YAML::Key << "sampledPoints" << YAML::BeginSeq;
        for (const auto& point : sampledPoints) {
            out << YAML::BeginMap;
            out << YAML::Key << "x" << YAML::Value << point.x;
            out << YAML::Key << "y" << YAML::Value << point.y;
            out << YAML::Key << "z" << YAML::Value << point.z;
            out << YAML::EndMap;
        }
        out << YAML::EndSeq;

        out << YAML::EndMap;
    }
    out << YAML::EndSeq;

    out << YAML::EndMap;

    return out.c_str();
}

void YamlConverter::ToYaml(const AttributesManager &attributesManager) {
    std::string yamlString = ToString(attributesManager);
    std::ofstream fout("attributes.yaml");
    if (fout.is_open()) {
        fout << yamlString;
        fout.close();
    } else {
        std::cerr << "Error: Unable to open file for writing YAML." << std::endl;
    }
}
