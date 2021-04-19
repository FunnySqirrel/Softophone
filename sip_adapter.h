#ifndef SIP_ADAPTER_H
#define SIP_ADAPTER_H

#include <QObject>
#include <pjsua-lib/pjsua.h>

#define THIS_FILE "APP"

class Sip_adapter : public QObject
{
    Q_OBJECT
private:
    pjsua_config cfg;                   //pjsua config
    pjsua_logging_config log_cfg;       //logging config
    pjsua_acc_config user_cfg;          //user config
    pjsua_acc_id acc_id;                //account id
    pj_status_t status;                 //status

    Sip_adapter(Sip_adapter &other);      //singleton blocker
    void operator=(const Sip_adapter &); //singleton blocker

protected:
    Sip_adapter()
    {}
    static Sip_adapter* singleton;      //singleton creating


public:
    static Sip_adapter *get_instance();   //singleton ascess point

    void sip_adapter_init();              //sipadapter initializer

    //callback functions
    static void on_reg_state2 (pjsua_acc_id acc_id, pjsua_reg_info *info);                              //for registrtion state
    static void on_incoming_call(pjsua_acc_id acc_id, pjsua_call_id call_id,pjsip_rx_data *rdata);      //for incoming call
    static void on_call_state(pjsua_call_id call_id, pjsip_event *e);                                   //for call state
    static void on_call_media_state(pjsua_call_id call_id);                                             //for call media state

    static void error_exit(const char *title, pj_status_t status);

    void reg(std::string user, std::string password, std::string domain);       //registration
    void unreg();                                                               //unregistration

    void make_call (std::string call_uri);              //making an outgoing call;

signals:
    void get_status(int status);            //get status of connection
    void incoming_signal (int call_id);     //signal of incoming call
};

#endif // SIP_ADAPTER_H
