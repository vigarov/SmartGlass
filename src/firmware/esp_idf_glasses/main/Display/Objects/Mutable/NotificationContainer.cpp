#include "NotificationContainer.h"
#include "Logos.h"
#include "RawText.h"
#include <memory>

using namespace SmartGlasses;

NotificationContainer::NotificationContainer(std::string& s,notification_t notification,bool overwrites, pixel_pair_t offsets, unsigned char animate, unsigned char priority,TaskHandle_t notifyOnDraw)
: Container(notifyOnDraw,s,overwrites,offsets,animate,priority), m_notification(notification)
{
    ESP_LOGI(s.c_str(),"created %d,%d",offsets.x,offsets.y);
    m_displayables.push_back(getNotificationLogo(notification.application,offsets+(pixel_pair_t){0,NOTIF_LOGO_OFFSET_Y}));
    m_displayables.push_back(std::make_shared<RawText>(parseTerminated(notification.title.text,notification.title.isTerminated),true,offsets+(pixel_pair_t){NOTIF_TITLE_OFFSET_X,NOTIF_TITLE_OFFSET_Y}));
    m_displayables.push_back(std::make_shared<RawText>(parseTerminated(notification.additionalInfo.text,notification.additionalInfo.isTerminated),true,offsets+(pixel_pair_t){NOTIF_ADDINFO_OFFSET_X,NOTIF_ADDINFO_OFFSET_Y}));
}

std::shared_ptr<Logo> NotificationContainer::getNotificationLogo(app_t n, pixel_pair_t offsets){
    switch(n){ //TODO: add system
        case SMS:
            return std::move(std::make_shared<Sms>(m_contentName+" SMS",true,offsets));
            
        case WHATSAPP:
            return std::move(std::make_shared<Whatsapp>(m_contentName+" Whatsapp",true,offsets));
            
        case SIGNAL:
            return std::move(std::make_shared<Signal>(m_contentName+" Signal",true,offsets));
            
        case SNAPCHAT:
            return std::move(std::make_shared<Snapchat>(m_contentName+" Snapchat",true,offsets));
            
        case INSTAGRAM:
            return std::move(std::make_shared<Instagram>(m_contentName+" Instagram",true,offsets));
            
        case GMAIL:
            return std::move(std::make_shared<Gmail>(m_contentName+" Gmail",true,offsets));
            
        case DISCORD:
            return std::move(std::make_shared<Discord>(m_contentName+" Discord",true,offsets));
            
        case FACEBOOK:
            return std::move(std::make_shared<Facebook>(m_contentName+" Facebook",true,offsets));
            
        case TELEGRAM:
            return std::move(std::make_shared<Telegram>(m_contentName+" Telegram",true,offsets));
            
        case LINKEDIN:
            return std::move(std::make_shared<Linkedin>(m_contentName+" Telegram",true,offsets));
        default:
            return std::move(std::make_shared<Other>(m_contentName+" Other",true,offsets));
            

    }
}

std::string NotificationContainer::parseTerminated(char* s, bool terminated){
    std::string ret(s);
    if(!terminated)ret+=(char)SPECIAL_ELLIPSIS_CHAR_IDX;
    return ret;
}