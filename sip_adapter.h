#ifndef SIP_ADAPTER_H
#define SIP_ADAPTER_H

#include <QObject>
#include <pjsua-lib/pjsua.h>

class Sip_adapter : public QObject
{
    Q_OBJECT
private:
    pjsua_config cfg;                   //pjsua config
    pjsua_logging_config log_cfg;       //logging config
    pjsua_acc_config user_cfg;          //user config
    pjsua_acc_id acc_id;                //account id
    pj_status_t status;                 //status
    std::string domain;                 //domain

    int reg_status;

    static void on_reg_state_2 (pjsua_acc_id acc_id, pjsua_reg_info *reg_info);                              //for registrtion state
    static void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id,pjsip_rx_data *rdata);      //for incoming call
    static void on_call_state(pjsua_call_id call_id, pjsip_event *e);                                   //for call state
    static void on_call_media_state(pjsua_call_id call_id);                                             //for call media state

    Sip_adapter(Sip_adapter &other);            //singleton blocker
    void operator=(const Sip_adapter &);        //singleton blocker

protected:
    Sip_adapter()
    {}
    static Sip_adapter* singleton;          //singleton creating


public:
    static Sip_adapter *get_instance();     //singleton ascess point

    void sip_adapter_init();                //sipadapter initializer
    void sip_adapter_destroy();             //sipadapter destroyer

    //callback functions

    static void error_exit(const char *title, pj_status_t status);

    void reg(std::string user, std::string password, std::string user_domain);      //registration
    void unreg();                                                                   //unregistration
    int get_status();                                       //return registration status

    int make_call (std::string call_uri);               //making an outgoing call. returns call id;
    void hangup_call(int call_id);                      //hang up call
    void answer_call(int call_id, int sipcode);         //answering incoming call

    std::string get_call_name(int call_id);             //returns number of interlocutor
    int get_call_status(int call_id);                   //returns call status

signals:
    void changing_reg_signal(int status);            //get status of connection
    void incoming_call_signal (int call_id, int status);     //signal of incoming call
    void changing_status_signal (int status);
};

#endif // SIP_ADAPTER_H
