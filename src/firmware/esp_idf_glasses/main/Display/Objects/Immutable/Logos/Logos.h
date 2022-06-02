#pragma once

#include "Content.h"
#include "Display.h"
#include <string>
#include <memory>

namespace SmartGlasses{
    class Logo: public ConstantContent{
    public:
        Logo(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent("Logo "+name,overwrites,offsets,animate,priority){}
        const unsigned char size = 20; //== length == height
    };
    class Discord : public Logo{
    public:
        Discord(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Facebook : public Logo{
    public:
        Facebook(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Gmail : public Logo{
    public:
        Gmail(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Instagram : public Logo{
    public:
        Instagram(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Linkedin : public Logo{
    public:
        Linkedin(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Other : public Logo{
    public:
        Other(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Signal : public Logo{
    public:
        Signal(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Sms : public Logo{
    public:
        Sms(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Snapchat : public Logo{
    public:
        Snapchat(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Telegram : public Logo{
    public:
        Telegram(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
    class Whatsapp : public Logo{
    public:
        Whatsapp(const std::string& name, bool overwrites = true, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): Logo(name,overwrites,offsets,animate,priority) {}
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    };
};