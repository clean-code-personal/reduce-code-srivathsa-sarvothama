#include "brightener.h"

ImageBrightener::ImageBrightener(std::shared_ptr<Image> inputImage): m_inputImage(inputImage) {
}

bool ImageBrightener::BrightenImage(std::shared_ptr<Image> imageToAdd, int& attenuatedCount)
{
    attenuatedCount = 0;

    if (imageToAdd && (imageToAdd->m_rows != m_inputImage->m_rows || imageToAdd->m_columns != m_inputImage->m_columns))
    {
        return false;
    }

    for (int x = 0; x < m_inputImage->m_rows; x++) 
    {
        for (int y = 0; y < m_inputImage->m_columns; y++) 
        {
            int pixelIndex = x * m_inputImage->m_columns + y;

            int brighteningOffset = imageToAdd ? imageToAdd->m_pixels[pixelIndex] : 25;

            if (int(m_inputImage->m_pixels[pixelIndex]) + brighteningOffset > 255) 
            {
                ++attenuatedCount;
                m_inputImage->m_pixels[pixelIndex] = 255;
            }
            else {
                m_inputImage->m_pixels[pixelIndex] += brighteningOffset;
            }
        }
    }

    return true;

}