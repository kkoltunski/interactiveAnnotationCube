#include "gtest/gtest.h"
#include "../../SceneModule/scene3d.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

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

TEST_F(Scene3DTestsFixture, initializationCheck){
    m_scene.initialize();
    
    auto interactor = m_scene.getInteractor();
    auto renderer = m_scene.getRenderer();
    int renderWindowDimension[2]{
        m_scene.getRenderer()->GetRenderWindow()->GetSize()[0],
        m_scene.getRenderer()->GetRenderWindow()->GetSize()[1]
    };

    EXPECT_EQ(renderWindowDimension[0], m_initialDimension[0]);
    EXPECT_EQ(renderWindowDimension[1], m_initialDimension[1]);
    ASSERT_EQ(interactor->GetRenderWindow(), renderer->GetRenderWindow());
};
