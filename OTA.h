//=======================================================================================================================
//DIRETIVAS
//=======================================================================================================================
#ifndef OTA_H
#define OTA_H

//=======================================================================================================================
//BIBLIOTECAS
//=======================================================================================================================
#include <Arduino.h>      //lib para as funções padrão do Arduino
#include <ArduinoOTA.h>   //lib do ArduinoOTA
#include <SPIFFS.h> 

//=======================================================================================================================
//CLASSE OTA IDE
//=======================================================================================================================
class OTAIDE {    
    private:
        static void defaultOnStart();                   //Instruções executadas quando a atualização inicia 
        static void defaultOnProgress(unsigned int progresso, unsigned int total);   //Instruções executadas durante a atualização
        static void defaultOnEnd();                     //Instruções executadas quando a atualização termina 
        static void defaultOnError(ota_error_t erro);   //Instruções executadas caso ocorra algum erro durante a atualização
                        
    public:
        OTAIDE();
        void setup();
        void loop();

        void setHostname(String hostname);
        void setPassword(String password);
        void setPasswordHash(String hash);

        static void onStart(void (*funcao)());
        static void onProgress(void (*funcao)(unsigned int progresso, unsigned int total));
        static void onEnd(void (*funcao)());
        static void onError(void (*funcao)(ota_error_t erro));
};

//=======================================================================================================================
//CLASSE OTAHTTP
//=======================================================================================================================
class OTAHTTP {    
    private:
        static void defaultOnStart();                   //Instruções executadas quando a atualização inicia 
        static void defaultOnProgress(unsigned int progresso, unsigned int total);   //Instruções executadas durante a atualização
        static void defaultOnEnd();                     //Instruções executadas quando a atualização termina 
        static void defaultOnError(ota_error_t erro);   //Instruções executadas caso ocorra algum erro durante a atualização
                        
    public:
        OTAHTTP();
        void setup(bool defaultOutputs = true);
        void loop();

        void setHostname(String hostname);
        void setPassword(String password);
        void setPasswordHash(String hash);

        void onStart(void (*funcao)());
        void onProgress(void (*funcao)());
        void onEnd(void (*funcao)());
        void onError(void (*funcao)());
};

//=======================================================================================================================
//FIM
//=======================================================================================================================
#endif
