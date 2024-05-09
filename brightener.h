#include <cstdint>
#include "image.h"

class ImageBrightener {
    private:
        std::shared_ptr<Image> m_inputImage;
    public:
        ImageBrightener(std::shared_ptr<Image> inputImage);
        bool BrightenImage(int& attenuatedCount, std::shared_ptr<Image> imageToAdd = nullptr);
};
