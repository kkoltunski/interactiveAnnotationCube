#include "gtest/gtest.h"
#include "../../SceneModule/actorsPool.h"

class ActorsPoolTestsFixture : public ::testing::Test{
protected:
    ActorsPool m_actorsPool;
};

TEST_F(ActorsPoolTestsFixture, constructorCheck){
    ASSERT_NE(m_actorsPool.getRenderer(), nullptr);
}