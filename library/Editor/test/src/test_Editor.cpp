#include <Editor/GraphicEditor.h>

#include <gtest/gtest.h>

TEST(Editor, Ctor)
{
   GraphicEditor editor;
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}