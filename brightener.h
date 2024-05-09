#include <cstdint>
#include "image.h"

class ImageBrightener {
    private:
        std::shared_ptr<Image> m_inputImage;
    public:
        ImageBrightener(std::shared_ptr<Image> inputImage);
        bool BrightenImage(std::shared_ptr<Image> imageToAdd, int& attenuatedCount);
};
