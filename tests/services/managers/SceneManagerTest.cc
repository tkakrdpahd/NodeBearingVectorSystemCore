// SceneManagerTest.cc

#include <gtest/gtest.h>
#include "SceneManager.h"
#include "ObjectManager.h"
#include "NodeVector.h"
#include "BearingVector.h"
#include "LinearSegment.h"
#include "Vector3.h"

// 테스트 Fixture 정의
class SceneManagerTest : public ::testing::Test {
protected:
    // 테스트 전에 호출됨
    void SetUp() override {
        sceneMgr = std::make_unique<SceneManager>("TestUser", "2024-11-20");
    }

    // 테스트 후에 호출됨
    void TearDown() override {
        // 필요 시 정리 작업 수행
    }

    std::unique_ptr<SceneManager> sceneMgr;
};

// Test 1: ObjectManager 생성 테스트
TEST_F(SceneManagerTest, CreateObjectManagerTest) {
    bool result = sceneMgr->CreateObjectManager("TestObject");
    EXPECT_TRUE(result);

    // 생성된 ObjectManager가 존재하는지 확인
    ObjectManager* obj = sceneMgr->ReadObjectManager(1);
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->GetName(), "TestObject");
}

// Test 2: ObjectManager 이름 업데이트 테스트
TEST_F(SceneManagerTest, UpdateObjectManagerNameTest) {
    // ObjectManager 생성
    bool createResult = sceneMgr->CreateObjectManager("InitialName");
    EXPECT_TRUE(createResult);

    // 이름 업데이트
    bool updateResult = sceneMgr->UpdateObjectManager(1, "UpdatedName");
    EXPECT_TRUE(updateResult);

    // 업데이트된 이름 확인
    ObjectManager* obj = sceneMgr->ReadObjectManager(1);
    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->GetName(), "UpdatedName");
}

// Test 3: ObjectManager 삭제 테스트
TEST_F(SceneManagerTest, DeleteObjectManagerTest) {
    // ObjectManager 생성
    bool createResult = sceneMgr->CreateObjectManager("ObjectToDelete");
    EXPECT_TRUE(createResult);

    // 삭제 시도
    bool deleteResult = sceneMgr->DeleteObjectManager(1);
    EXPECT_TRUE(deleteResult);

    // 삭제된 ObjectManager가 존재하지 않는지 확인
    ObjectManager* obj = sceneMgr->ReadObjectManager(1);
    EXPECT_EQ(obj, nullptr);
}

// Test 4: ObjectManager 목록 나열 테스트
TEST_F(SceneManagerTest, ListAllObjectManagersTest) {
    // ObjectManager 두 개 생성
    bool createResult1 = sceneMgr->CreateObjectManager("Object1");
    bool createResult2 = sceneMgr->CreateObjectManager("Object2");
    EXPECT_TRUE(createResult1);
    EXPECT_TRUE(createResult2);

    // 콘솔 출력을 캡처하기 위해 ::testing::internal::CaptureStdout() 사용
    ::testing::internal::CaptureStdout();
    sceneMgr->ListAllObjectManagers();
    std::string output = ::testing::internal::GetCapturedStdout();

    // 출력에 Object1과 Object2가 포함되어 있는지 확인
    EXPECT_NE(output.find("Object1"), std::string::npos);
    EXPECT_NE(output.find("Object2"), std::string::npos);
}

// Test 5: ObjectManager 중복 생성 테스트
TEST_F(SceneManagerTest, DuplicateObjectManagerTest) {
    // ObjectManager 첫 번째 생성
    bool firstCreate = sceneMgr->CreateObjectManager("UniqueObject");
    EXPECT_TRUE(firstCreate);

    // 동일한 이름으로 ObjectManager 두 번째 생성 (ID는 자동 증가)
    bool secondCreate = sceneMgr->CreateObjectManager("UniqueObject");
    EXPECT_TRUE(secondCreate);

    // 총 ObjectManager 개수 확인 (2개)
    // 콘솔 출력을 캡처하여 개수 확인
    ::testing::internal::CaptureStdout();
    sceneMgr->ListAllObjectManagers();
    std::string output = ::testing::internal::GetCapturedStdout();

    // "UniqueObject"이 두 번 나오는지 확인
    size_t first = output.find("UniqueObject");
    size_t second = output.find("UniqueObject", first + 1);
    EXPECT_NE(first, std::string::npos);
    EXPECT_NE(second, std::string::npos);
    EXPECT_GT(second, first);
}
