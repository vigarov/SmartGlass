#pragma once

namespace SmartGlasses{
    class Discord : public ConstantContent{
        Discord(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Facebook : public ConstantContent{
        Facebook(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Gmail : public ConstantContent{
        Gmail(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Instagram : public ConstantContent{
        Instagram(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Linkedin : public ConstantContent{
        Linkedin(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Other : public ConstantContent{
        Other(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Signal : public ConstantContent{
        Signal(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class SMS : public ConstantContent{
        SMS(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Snapchat : public ConstantContent{
        Snapchat(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Telegram : public ConstantContent{
        Telegram(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
    };
    class Whatsapp : public ConstantContent{
        Whatsapp(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
};