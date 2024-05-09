#include "CppUnitTest.h"
#include "../brightener.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace brighteningtest
{
    std::shared_ptr<Image> CreateImage(uint8_t pixelValues[])
    {
        auto image = std::make_shared<Image>(2, 2);
        image->m_pixels[0] = pixelValues[0]; image->m_pixels[1] = pixelValues[1];
        image->m_pixels[2] = pixelValues[2];; image->m_pixels[3] = pixelValues[3];

        return image;
    }

	TEST_CLASS(BrighteningTest)
	{
	public:
		
		TEST_METHOD(BrightensWholeImage)
		{
            uint8_t pixelValues[] = { 45, 55, 65, 254 };

            auto image = CreateImage(pixelValues);

			ImageBrightener brightener(image);
            int attenuatedCount = 0;
            brightener.BrightenImage(attenuatedCount);
			Assert::AreEqual(1, attenuatedCount);
			Assert::AreEqual(90, int(image->m_pixels[2]));
		}

		TEST_METHOD(BrightensWithAnotherImage)
		{
            uint8_t pixelValues[] = { 45, 55, 65, 75 };

            auto image = CreateImage(pixelValues);

            ImageBrightener brightener(image);
            
            // Test by brightening only the right part
            auto brighteningImage = std::make_shared<Image>(2, 2);
            brighteningImage->m_pixels[0] = 0; brighteningImage->m_pixels[1] = 25;
            brighteningImage->m_pixels[2] = 0; brighteningImage->m_pixels[3] = 25;

            int attenuatedCount = 0;
            bool succeeded = brightener.BrightenImage(attenuatedCount, brighteningImage);
            Assert::IsTrue(succeeded);
            Assert::AreEqual(45, int(image->m_pixels[0])); // left-side pixel is unchanged
            Assert::AreEqual(80, int(image->m_pixels[1])); // right-side pixel is brightened
            Assert::AreEqual(0, attenuatedCount);
		}
	};
}
