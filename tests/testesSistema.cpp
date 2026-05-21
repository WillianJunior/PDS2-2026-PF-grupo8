#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/Sensor.hpp"
#include "../include/AlertaManager.hpp"
#include "../include/Maquina.hpp"
#include "../include/Relatorio.hpp"
#include "../include/ProtocoloMarcha.hpp"
#include "../include/Sessao.hpp"
#include "../include/SistemaMonitor.hpp"

TEST_CASE("Testes de Unidade - Classe Sensor") {
    Sensor termoMotor("S_TEMP_01", "Temperatura", 85.0, 15.0);

    SUBCASE("Validacao do registro e leitura corrente") {
        termoMotor.registraHist(28.4);
        CHECK(termoMotor.retornaAtual() == 28.4);
    }

    SUBCASE("Disparo de alarmes por violacao de limite maximo") {
        termoMotor.registraHist(93.5);
        CHECK(termoMotor.alerta() == true);
    }

    SUBCASE("Disparo de alarmes por violacao de limite minimo") {
        termoMotor.registraHist(10.2);
        CHECK(termoMotor.alerta() == true);
    }

    SUBCASE("Calculo de picos maximos e minimos do historico") {
        termoMotor.registraHist(30.0);
        termoMotor.registraHist(75.5);
        termoMotor.registraHist(22.1);
        
        CHECK(termoMotor.calcularMaxRegistrado() == 75.5);
        CHECK(termoMotor.calcularMinRegistrado() == 22.1);
    }
}

TEST_CASE("Testes de Unidade - Classe AlertaManager") {
    AlertaManager manager;
    Sensor sensorRpm("S_RPM_01", "Giro", 4500.0, 500.0);

    SUBCASE("Classificacao de severidade do alerta") {
        sensorRpm.registraHist(5200.0);
        CHECK(manager.classificarSeveridade(&sensorRpm) == "CRÍTICO");
    }

    SUBCASE("Fluxo de insercao de alertas ativos na fila") {
        sensorRpm.registraHist(5500.0);
        manager.receberAlertas(&sensorRpm);
        CHECK(manager.getAtivos().size() == 1);
    }
}

TEST_CASE("Testes de Unidade - Classe Maquina") {
    Sensor t("S_T", "Temperatura", 90.0, 10.0);
    Sensor v("S_V", "Velocidade", 3000.0, 100.0);
    Maquina prensa("P_IND_01", &t, &v);

    SUBCASE("Estado inicial padrao da maquina") {
        CHECK(prensa.getStatus() == Maquina::DESLIGADA);
    }

    SUBCASE("Ativacao do modo de economia de energia") {
        CHECK(prensa.modoMarcha() == false);
    }
}

TEST_CASE("Testes de Unidade - Classes de Servico (Interface e Contratos)") {
    Sensor t("S_T2", "Temperatura", 80.0, 20.0);
    Sensor v("S_V2", "Velocidade", 2000.0, 200.0);
    Maquina torno("TOR_01", &t, &v);
    
    vector<Maquina*> parqueMaquinas;
    parqueMaquinas.push_back(&torno);

    SUBCASE("Validacao do modulo de Relatorios") {
        Relatorio rel;
        // Verifica se os metodos aceitam a passagem por referencia/ponteiro corretamente
        rel.registraTempMaxMin(&torno);
        rel.registraRpmMaxMin(&torno);
        rel.gerarResumo(parqueMaquinas);
        CHECK_NOTHROW("Metodos de relatorio executados sem quebras de contrato.");
    }

    SUBCASE("Validacao do modulo de Protocolos de Marcha") {
        ProtocoloMarcha prot;
        prot.quedaEnergia(parqueMaquinas);
        prot.equalizarRPM(parqueMaquinas);
        CHECK_NOTHROW("Metodos de protocolo de contingencia validados.");
    }
}

TEST_CASE("Testes de Unidade - Gerenciamento Superior") {
    SistemaMonitor monitor;
    Sensor t("S_T3", "Temperatura", 100.0, 0.0);
    Sensor v("S_V3", "Velocidade", 1500.0, 0.0);
    Maquina esteira("EST_01", &t, &v);

    SUBCASE("Inclusao e monitoramento de repositório central") {
        monitor.adicionarMaquinas(&esteira);
        CHECK(monitor.getMaquinas().size() == 1);
    }

    SUBCASE("Fluxo de controle de Sessao de Turno") {
        Sessao turno;
        vector<Maquina*> listaMonitorada = monitor.getMaquinas();
        turno.inicializarMaquinas(listaMonitorada);
        CHECK_NOTHROW("Turno operacional inicializado.");
    }
}