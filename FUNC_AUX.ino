//=======================================================================================================================
//FUNÇÕES RELACIONADAS AO WIFI
//=======================================================================================================================

//=======================================================================================================================
//CONECTA AO WIFI
//=======================================================================================================================

void wifi_conectar(String ssid, String senha) {
    int cont = 0;

    Serial.println("Conectando ao WiFi: " + String(WIFI_SSID));

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
        
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);

        cont++;
        
        if(cont == 10) {
            Serial.println();
            Serial.println("Não foi possível se conectar!");
            Serial.println("Reiniciando...");
            delay(1000);
            ESP.restart();
        }
    }

    Serial.println();
    Serial.print("WiFi conectado! (IP: ");
    Serial.print(WiFi.localIP());
    Serial.println(")");
}

//=======================================================================================================================
//FUNÇÕES DE CALLBACK PERSONALIZADAS
//=======================================================================================================================

//=======================================================================================================================
//ATUALIZAÇÃO OTA INICIADA
//=======================================================================================================================

void ota_iniciando() {
    Serial.println("Atualizando...");
}

//=======================================================================================================================
//ATUALIZAÇÃO OTA TERMINADA
//=======================================================================================================================

void ota_terminando() {
    Serial.println("Atualização concluída!");
}

//=======================================================================================================================
//PROGRESSO DA ATUALIZAÇÃO OTA
//=======================================================================================================================

void ota_progresso(unsigned int progresso, unsigned int total) {
    static int porcentagem_anterior = -1;
    int porcentagem = 0,
        intervalo = 10;

    porcentagem = (progresso * 100) / total;
    porcentagem = (porcentagem / intervalo) * intervalo;
    
    if(porcentagem != porcentagem_anterior) {
        Serial.println(String(porcentagem) + "%");
        porcentagem_anterior = porcentagem;
    }
}

//=======================================================================================================================
//ERRO NA ATUALIZAÇÃO OTA
//=======================================================================================================================

void ota_erro(ota_error_t erro) {
    Serial.println("ERRO " + String(erro) + ": Parece que algo deu errado :/");
}

//=======================================================================================================================














/*
//=======================================================================================================================
//CONFIGURA A ATUALIZAÇÃO OTA
//=======================================================================================================================

void ota_setup() {
    String hostName = String(MODELO_DISPOSITIVO) + "-" + String(NOME_DISPOSITIVO) + "-v" + String(VERSAO_SOFTWARE);
    
    ArduinoOTA.setHostname(hostName.c_str());
    //ArduinoOTA.setPassword("");
    ArduinoOTA.onStart(ota_iniciando);
    ArduinoOTA.onEnd(ota_terminando);
    ArduinoOTA.onProgress(ota_progresso);
    ArduinoOTA.begin();
}

//=======================================================================================================================
//LOOP DA ATUALIZAÇÃO OTA
//=======================================================================================================================

void ota_loop() {
    static unsigned int tempoAnterior = 0; 
    String versao, link;
    
    ArduinoOTA.handle();

    if(millis() - tempoAnterior >= 30 * 1000) {
        versao = firebase_receber("/esp/versao");                               //Recebe do Firebase a última versão do software
        versao.replace("\"", "");
        
        if(!versao.equals(VERSAO_SOFTWARE)) {                                   //Verifica se as versões são diferentes. Se sim, atualiza 
            link = firebase_receber("/esp/link");                               //Recebe do Firebase o link da atualizacao
            link.replace("\"", "");
            
            Serial.println("************************************");             //Imprime na serial um aviso sobre o
            Serial.println("Atualizacao encontrada!");
            Serial.println("Versao instalada:  HidroMonitor v" + String(VERSAO_SOFTWARE));
            Serial.println("Nova versao:       HidroMonitor v" + versao);
            Serial.println("Link:              " + link + "\n");
            
            ota_iniciando();

            for(int i = 0 ; i <= 10 ; i++) {
                ota_progresso(i, 10);
                delay(2000);
            }

            ota_terminando();
            ESP.restart();  
        }

        tempoAnterior = millis();
    }
}
*/
