//=======================================================================================================================
//BIBLIOTECAS
//=======================================================================================================================
#include "OTA.h"

//=======================================================================================================================
//CONSTRUTOR
//=======================================================================================================================

OTAIDE::OTAIDE() {
    ArduinoOTA.onStart(defaultOnStart);
    ArduinoOTA.onProgress(defaultOnProgress);
    ArduinoOTA.onEnd(defaultOnEnd);
    ArduinoOTA.onError(defaultOnError);
}

//=======================================================================================================================
//SETUP
//=======================================================================================================================

void OTAIDE::setup() {
    ArduinoOTA.begin();
}

//=======================================================================================================================
//LOOP
//=======================================================================================================================

void OTAIDE::loop() {
    ArduinoOTA.handle();
}

//=======================================================================================================================
//MÉTODOS SETTERS
//=======================================================================================================================

//=======================================================================================================================
//ALTERA O HOSTNAME (NOME DO DISPOSITIVO QUE SERÁ MOSTRADO NA IDE DO ARDUINO)
//=======================================================================================================================

void OTAIDE::setHostname(String hostname) {
    ArduinoOTA.setHostname(hostname.c_str());     //Define o Hostname do dispositivo (Padrão: esp32-[MAC]
}

//=======================================================================================================================
//DEFINE O PASSWORD (SENHA QUE SERÁ PEDIDA QUANDO UMA ATUALIZAÇÃO FOR ENCONTRADA)
//=======================================================================================================================

void OTAIDE::setPassword(String password) {
    ArduinoOTA.setPassword(password.c_str());     //Define a Senha para atualização do dispositivo (Padrão: nenhuma)
}

//=======================================================================================================================
//DEFINE UM HASH COMO PASSWORD (SENHA QUE SERÁ PEDIDA QUANDO UMA ATUALIZAÇÃO FOR ENCONTRADA)
//=======================================================================================================================

void OTAIDE::setPasswordHash(String hash) {
    ArduinoOTA.setPasswordHash(hash.c_str());     //Define a Senha para atualização do dispositivo com uma criptografia Hash MD5
                                                  //Exemplo de MD5 para senha "admin" = 21232f297a57a5a743894a0e4a801fc3
}

//=======================================================================================================================
//FUNÇÕES DE CALLBACK
//=======================================================================================================================

//=======================================================================================================================
//INSTRUÇÕES EXECUTADAS QUANDO A ATUALIZAÇÃO INICIA
//=======================================================================================================================

void OTAIDE::defaultOnStart() {
    if(ArduinoOTA.getCommand() == U_FLASH) {
        Serial.println("Iniciando atualização do software...");
    }

    else if(ArduinoOTA.getCommand() == U_SPIFFS) {
        Serial.println("Iniciando atualização da SPIFFS...");
        SPIFFS.end();
    }
}

//=======================================================================================================================
//INSTRUÇÕES EXECUTADAS DURANTE A ATUALIZAÇÃO
//=======================================================================================================================

void OTAIDE::defaultOnProgress(unsigned int progresso, unsigned int total) {
    static int porcentagem_anterior = -1;
    int porcentagem = 0;

    porcentagem = (progresso * 100) / total;

    if(porcentagem != porcentagem_anterior) {
        Serial.println(String(porcentagem) + "%");
        porcentagem_anterior = porcentagem;
    }
}

//=======================================================================================================================
//INSTRUÇÕES EXECUTADAS QUANDO A ATUALIZAÇÃO TERMINA
//=======================================================================================================================

void OTAIDE::defaultOnEnd() {
    Serial.println("Atualização concluída!");
}

//=======================================================================================================================
//INSTRUÇÕES EXECUTADAS CASO OCORRA ALGUM ERRO DURANTE A ATUALIZAÇÃO
//=======================================================================================================================

void OTAIDE::defaultOnError(ota_error_t erro) {
    Serial.print("Erro " + String(erro) + ": ");
      
    if (erro == OTA_AUTH_ERROR) Serial.println("Falha na autenticação!");
    else if (erro == OTA_BEGIN_ERROR) Serial.println("Falha ao iniciar a atualização!");
    else if (erro == OTA_CONNECT_ERROR) Serial.println("Falha ao se conectar!");
    else if (erro == OTA_RECEIVE_ERROR) Serial.println("Falha no recebimento da atualização!");
    else if (erro == OTA_END_ERROR) Serial.println("Falha ao conluir a atualização!");
    else Serial.println("Falha desconhecida!");   
}

//=======================================================================================================================
//FUNÇÕES DE CALLBACK PERSOLANIZADAS
//=======================================================================================================================

//=======================================================================================================================
//INSTRUÇÕES PERSONALIZADAS EXECUTADAS QUANDO A ATUALIZAÇÃO INICIA
//=======================================================================================================================

void OTAIDE::onStart(void (*funcao)()) {
    ArduinoOTA.onStart(funcao);
}

//=======================================================================================================================
//INSTRUÇÕES PERSONALIZADAS EXECUTADAS DURANTE A ATUALIZAÇÃO
//=======================================================================================================================

void OTAIDE::onProgress(void (*funcao)(unsigned int progresso, unsigned int total)) {
    ArduinoOTA.onProgress(funcao);
}

//=======================================================================================================================
//INSTRUÇÕES PERSONALIZADAS EXECUTADAS QUANDO A ATUALIZAÇÃO TERMINA
//=======================================================================================================================

void OTAIDE::onEnd(void (*funcao)()) {
    ArduinoOTA.onEnd(funcao);
}

//=======================================================================================================================
//INSTRUÇÕES EXECUTADAS CASO OCORRA ALGUM ERRO DURANTE A ATUALIZAÇÃO
//=======================================================================================================================

void OTAIDE::onError(void (*funcao)(ota_error_t erro)) {
    ArduinoOTA.onError(funcao); 
}

//=======================================================================================================================
