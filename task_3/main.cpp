#include <iostream>
#include "lib/chainRes.hpp"



int main(void) {
    WarningLogMessage* log1 = new WarningLogMessage;
    ErrorLogMessage* log2 = new ErrorLogMessage;
    FatalErrorLogMessage* log3 = new FatalErrorLogMessage;
    UnknowMsgLogMessage* log4 = new UnknowMsgLogMessage;

    log2->AddFile("log.txt");
    log1->SetNext(log2)->SetNext(log3)->SetNext(log4);

    Message msg_w;
    msg_w.type_of_message = Type::Warning;
    msg_w.message = "I'm warning!";
    log1->message(msg_w);

    Message msg_e;
    msg_e.type_of_message = Type::Error;
    msg_e.message = "I'm Error!";
    log1->message(msg_e);

    Message msg_fe;
    msg_fe.type_of_message = Type::FatalError;
    msg_fe.message = "I'm fatal error!";
    log1->message(msg_fe);

    Message msg_ue;
    msg_ue.type_of_message = Type::UnknowMessage;
    msg_ue.message = "I'm unknow message :(";
    log1->message(msg_ue);

    delete log1;
    delete log2;
    delete log3;
    delete log4;
    return EXIT_SUCCESS;
}