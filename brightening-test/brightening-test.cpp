#include "CppUnitTest.h"
#include "../brightener.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace brighteningtest
{
	TEST_CLASS(BrighteningTest)
	{
	public:
		
		TEST_METHOD(BrightensWholeImage)
		{
			auto image = std::make_shared<Image>(2, 2);
			image->m_pixels[0] = 45; image->m_pixels[1] = 55;
			image->m_pixels[2] = 65; image->m_pixels[3] = 254;

			ImageBrightener brightener(image);
            int attenuatedCount = 0;
            brightener.BrightenImage(nullptr, attenuatedCount);
			Assert::AreEqual(1, attenuatedCount);
			Assert::AreEqual(90, int(image->m_pixels[2]));
		}

		TEST_METHOD(BrightensWithAnotherImage)
		{
			auto image = std::make_shared<Image>(2, 2);
			image->m_pixels[0] = 45; image->m_pixels[1] = 55;
			image->m_pixels[2] = 65; image->m_pixels[3] = 75;
            ImageBrightener brightener(image);
            
            // Test by brightening only the right part
            auto brighteningImage = std::make_shared<Image>(2, 2);
            brighteningImage->m_pixels[0] = 0; brighteningImage->m_pixels[1] = 25;
            brighteningImage->m_pixels[2] = 0; brighteningImage->m_pixels[3] = 25;

            int attenuatedCount = 0;
            bool succeeded = brightener.BrightenImage(brighteningImage, attenuatedCount);
            Assert::IsTrue(succeeded);
            Assert::AreEqual(45, int(image->m_pixels[0])); // left-side pixel is unchanged
            Assert::AreEqual(80, int(image->m_pixels[1])); // right-side pixel is brightened
            Assert::AreEqual(0, attenuatedCount);
		}
	};
}
