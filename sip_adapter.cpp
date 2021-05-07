#include "sip_adapter.h"

//singleton constructor (конструктор экземпляра синглтон)
Sip_adapter *Sip_adapter::singleton= nullptr;

Sip_adapter *Sip_adapter::get_instance()
{
    if(singleton==nullptr)
    {
        singleton = new Sip_adapter();
        singleton->sip_adapter_init();
    }
    return singleton;
}

//callback called by the library when registration state has changed
void Sip_adapter::on_reg_state_2 (pjsua_acc_id acc_id, pjsua_reg_info *reg_info)
{
    PJ_UNUSED_ARG(acc_id);
    emit Sip_adapter::get_instance()->changing_reg_signal(reg_info->renew);
}

//callback called by the library upon receiving incoming call
void Sip_adapter::on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id, pjsip_rx_data *rdata)
{
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);
    PJ_UNUSED_ARG(acc_id);
    PJ_UNUSED_ARG(rdata);
    emit Sip_adapter::get_instance()->incoming_call_signal(call_id, ci.state);
}

//callback called by the library when call's state has changed
void Sip_adapter::on_call_state(pjsua_call_id call_id, pjsip_event *e)
{
    pjsua_call_info ci;

    PJ_UNUSED_ARG(e);

    pjsua_call_get_info(call_id, &ci);
    int status=ci.state;
    emit Sip_adapter::get_instance()->changing_status_signal(status);
}

//callback called by the library when call's media state has changed
void Sip_adapter::on_call_media_state(pjsua_call_id call_id)
{
    pjsua_call_info ci;

    pjsua_call_get_info(call_id, &ci);

    if (ci.media_status == PJSUA_CALL_MEDIA_ACTIVE)
    {
        // When media is active, connect call to sound device.
        pjsua_conf_connect(ci.conf_slot, 0);
        pjsua_conf_connect(0, ci.conf_slot);
    }
}

//display error and exit application
void Sip_adapter::error_exit(const char *title, pj_status_t status)
{
    //pjsua_perror(THIS_FILE, title, status);
    pjsua_destroy();
    exit(1);
}

//sip adapter initialization (инициализация sip-адаптера)
void Sip_adapter::sip_adapter_init()
{
    //Create pjsua first! (создание pjsua)
    status = pjsua_create();
    //if (status != PJ_SUCCESS) error_exit("Error in pjsua_create()", status);

    //Init pjsua
    pjsua_config_default(&cfg);
    cfg.cb.on_incoming_call = &on_incoming_call;
    cfg.cb.on_call_media_state = &on_call_media_state;
    cfg.cb.on_call_state = &on_call_state;
    cfg.cb.on_reg_state2 = &on_reg_state_2;
    pjsua_logging_config_default(&log_cfg);
    log_cfg.console_level = 4;
    status = pjsua_init(&cfg, &log_cfg, NULL);
    //if (status != PJ_SUCCESS) error_exit("Error in pjsua_init()", status);

    //creating TCP transport (создание TCP транспорта)
    {
    pjsua_transport_config t_cfg;

    pjsua_transport_config_default(&t_cfg);
    t_cfg.port = 0;
    status = pjsua_transport_create(PJSIP_TRANSPORT_TCP, &t_cfg, NULL);
    //if (status != PJ_SUCCESS) error_exit("Error creating transport", status);
    }

    //Initialization is done, now start pjsua (запуск pjsua)
    status = pjsua_start();
    //if (status != PJ_SUCCESS) error_exit("Error starting pjsua", status);
}

void Sip_adapter::sip_adapter_destroy()
{
    pjsua_destroy();
}

//registration (регистрация)
void Sip_adapter::reg(std::string user, std::string password, std::string domain)
{
    pjsua_acc_config_default(&user_cfg);
    std::string id="sip:"+user+"@"+domain;      //creating "string" (создание строки типа "string")
    user_cfg.id = pj_str((char*)id.c_str());    //and convert to char* (и преобразование ее в char*)
    std::string reg_uri="sip:"+domain;
    user_cfg.reg_uri = pj_str((char*)reg_uri.c_str());
    user_cfg.cred_count = 1;
    user_cfg.cred_info[0].realm = pj_str((char*) "*");
    user_cfg.cred_info[0].scheme = pj_str((char*) "digest");
    user_cfg.cred_info[0].username = pj_str((char*) user.c_str());
    user_cfg.cred_info[0].data_type = PJSIP_CRED_DATA_PLAIN_PASSWD;
    user_cfg.cred_info[0].data = pj_str((char*) password.c_str());
    std::string proxy="<sip:"+domain+":5060;transport=tcp>";
    user_cfg.proxy[user_cfg.proxy_cnt++] = pj_str((char*) proxy.c_str());
    status = pjsua_acc_add(&user_cfg, PJ_TRUE, &acc_id);
    //if (status != PJ_SUCCESS) error_exit("Error adding account", status);
}

//unregistration (разрегистрация)
void Sip_adapter::unreg()
{
    status = pjsua_acc_set_registration(acc_id, PJ_FALSE);
    //status = pjsua_acc_del(acc_id);
    if (status != PJ_SUCCESS) error_exit("Error deleting account", status);
}

//making an outgoing call (совершение исходящего звонка)
int Sip_adapter::make_call (std::string call_uri)
{
    pjsua_call_setting call_opt;
    pjsua_call_setting_default(&call_opt);
    pj_str_t call_dst;
    call_dst=pj_str((char*) call_uri.c_str());
    pjsua_call_id call_id;
    status = pjsua_call_make_call(acc_id, &call_dst, &call_opt, 0, NULL, &call_id);
    //if (status != PJ_SUCCESS) error_exit("Error making call", status);
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);
    return call_id;
}

void Sip_adapter::hangup_call(int call_id)
{
    pjsua_call_hangup(call_id, 46, NULL, NULL);             //code 46 - BYE
}

void Sip_adapter::answer_call(int call_id, int sipcode)
{
    pjsua_call_answer(call_id, sipcode, NULL, NULL);
}

std::string Sip_adapter::get_call_name(int call_id)
{
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);
    return std::string(ci.remote_info.ptr);
}

int Sip_adapter::get_call_status(int call_id)
{
    pjsua_call_info ci;
    pjsua_call_get_info(call_id, &ci);
    return ci.state;
}
