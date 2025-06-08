#include <vsomeip/vsomeip.hpp>
#include <memory>
#include <iostream>

constexpr vsomeip::service_t service_id = 0x0100;
constexpr vsomeip::instance_t instance_id = 0x8888;
constexpr vsomeip::method_t method_id = 0x4022;
constexpr vsomeip::eventgroup_t event_group = 0x8070;
constexpr vsomeip::event_t event_id = 0x8070;


void on_service_availability(vsomeip::service_t _service_id, vsomeip::instance_t _instance_id, bool _isAvailable)
{
    if(service_id == _service_id && _instance_id == instance_id && _isAvailable)
    {
        auto app = vsomeip::runtime::get()->get_application("server");
        std::set<vsomeip::eventgroup_t> event_; 
        event_.insert(event_group);
        std::cout<< "[SERVER] available " << std::endl;
        app->offer_event(service_id, instance_id, event_id, event_);
    }
    else
    {
        std::cout<< "[SERVER] NOT available " << std::endl;
    }
    
}

void on_message_handler(const std::shared_ptr< vsomeip::message > & _request)
{
    std::cout<< " [SERVER] request from client " << std::endl;
    if(vsomeip::message_type_e::MT_REQUEST == _request->get_message_type())
    {
        auto app = vsomeip::runtime::get()->get_application("server");
        auto response = vsomeip::runtime::get()->create_response(_request);
        response->set_return_code(vsomeip::return_code_e::E_OK);
        // response->set_payload();
        app->send(response);

        vsomeip::byte_t fady[4] = {'f', 'a', 'd', 'y'};

        auto dumDumPayload = vsomeip::runtime::get()->create_payload();
        dumDumPayload->set_data(fady, 4);
        app->notify(service_id, instance_id, event_id, dumDumPayload);
    }
}

class server {
    private:
    std::shared_ptr<vsomeip::application> app = nullptr;
    public:
    bool init(void) {
        app = vsomeip::runtime::get()->create_application("server");
        app->register_availability_handler(
            service_id,
            instance_id,
            on_service_availability);
            
        app->register_message_handler(service_id,
            instance_id,
            method_id,
            on_message_handler);
            
        app->init();
            
        app->offer_service(service_id, instance_id);
        
        /* client shall request the service */
        return true;
    }

    void start()
    {
        app->start();
    }

    void stop()
    {
        app->unregister_availability_handler(service_id, instance_id);
        app->unregister_message_handler(service_id,instance_id, method_id);
        app->stop();
    }

};