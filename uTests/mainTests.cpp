#include "gtest/gtest.h"
#include "SceneModuleTests/scene3dTests.h"
#include "SceneModuleTests/customInteractorStyleTests.h"
#include "SceneModuleTests/actorsPoolTests.h"

#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2)

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}