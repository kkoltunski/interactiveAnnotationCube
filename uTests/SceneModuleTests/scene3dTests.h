#include "gtest/gtest.h"
#include "../../SceneModule/scene3d.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

class Scene3DTestsFixture : public ::testing::Test {
protected:
    Scene3DTestsFixture() : 
        m_scene{Scene3D(m_initialDimension[0],m_initialDimension[1])}
    {
    };

    int m_initialDimension[2] = {10,20};
    Scene3D m_scene;
};

TEST_F(Scene3DTestsFixture, constructorCheck){
    ASSERT_NE(m_scene.getRenderer(), nullptr);
    ASSERT_NE(m_scene.getInteractor(), nullptr);
};