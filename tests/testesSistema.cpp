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
    Sensor termoMotor("S_TEMP_01", "temperatura");

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
    Sensor sensorRpm("S_RPM_01", "rpm");

    SUBCASE("Classificacao de severidade do alerta") {
    sensorRpm.registraHist(18001.0);
    std::string resultado = manager.classificarSeveridade(&sensorRpm);
    std::cout << "[" << resultado << "]" << std::endl;
    CHECK(resultado == "S_RPM_01 CRITICO");
}

    SUBCASE("Fluxo de insercao de alertas ativos na fila") {
        sensorRpm.registraHist(19000.0);
        manager.receberAlertas(&sensorRpm);
        CHECK(manager.getAtivos().size() == 1);
    }
}

TEST_CASE("Testes de Unidade - Classe Maquina") {
    Sensor t("S_T", "temperatura");
    Sensor v("S_V", "rpm");
    Maquina prensa("P_IND_01", &t, &v);

    SUBCASE("Lancamento de Excecao ao instanciar maquina com sensores nulos") {
        CHECK_THROWS_AS(Maquina("MAQ_FALHA", nullptr, &v), std::invalid_argument);
        CHECK_THROWS_AS(Maquina("MAQ_FALHA", &t, nullptr), std::invalid_argument);
        CHECK_THROWS_AS(Maquina("", &t, &v), std::invalid_argument); // ID Vazio
    }
    SUBCASE("Desligamento automatico apos 3 ciclos de alerta de RPM") {
        prensa.ligarDesligar(true);
        v.registraHist(13500.0); 
        t.registraHist(35.0);
        prensa.atualizarEstado(); 
        CHECK(prensa.getStatus() == Maquina::ALERTA);
        CHECK(prensa.getCiclos() == 1);

        prensa.atualizarEstado(); 
        CHECK(prensa.getCiclos() == 2);

        prensa.atualizarEstado(); 
        CHECK(prensa.getStatus() == Maquina::DESLIGADA);
        CHECK(prensa.getCiclos() == 0); 
    }
    SUBCASE("Estado inicial padrao da maquina") {
        CHECK(prensa.getStatus() == Maquina::DESLIGADA);
    }

    SUBCASE("Ativacao do modo de economia de energia") {
        CHECK(prensa.modoMarcha() == false);
    }
}

TEST_CASE("Testes de Unidade - Classes de Servico (Interface e Contratos)") {
    Sensor t("S_T2", "temperatura");
    Sensor v("S_V2", "rpm");
    auto torno = std::make_shared<Maquina>("TOR_01", &t, &v);
    
    std::vector<std::shared_ptr<Maquina>> parqueMaquinas;
    parqueMaquinas.push_back(torno);

    SUBCASE("Validacao do modulo de Relatorios") {
        Relatorio rel;
        // O CHECK_NOTHROW agora encapsula as operacoes de verdade para ver se elas nao travam
        CHECK_NOTHROW(rel.registraTempMaxMin(torno));
        CHECK_NOTHROW(rel.registraRpmMaxMin(torno));
        CHECK_NOTHROW(rel.gerarResumo(parqueMaquinas));
    }

    SUBCASE("Validacao do modulo de Protocolos de Marcha") {
        ProtocoloMarcha prot;
        CHECK_NOTHROW(prot.quedaEnergia(parqueMaquinas));
        CHECK_NOTHROW(prot.equalizarRPM(parqueMaquinas));
        CHECK_NOTHROW(prot.modoNormal(parqueMaquinas));
    }
}

TEST_CASE("Testes de Unidade - Gerenciamento Superior") {
    SistemaMonitor monitor;
    Sensor t("S_T3", "temperatura");
    Sensor v("S_V3", "rpm");
    auto esteira = std::make_shared<Maquina>("EST_01", &t, &v);
    SUBCASE("Remocao de maquina por ID") {
        monitor.adicionarMaquinas(esteira);
        CHECK(monitor.getMaquinas().size() == 1);
        
        monitor.removerMaquinas("EST_01");
        CHECK(monitor.getMaquinas().size() == 0);
    }
    SUBCASE("Inclusao e monitoramento de repositório central") {
        monitor.adicionarMaquinas(esteira);
        CHECK(monitor.getMaquinas().size() == 1);
    }

    SUBCASE("Fluxo de controle de Sessao de Turno") {
        Sessao turno;
        std::vector<std::shared_ptr<Maquina>> listaMonitorada = monitor.getMaquinas();
        CHECK_NOTHROW(turno.inicializarMaquinas(listaMonitorada));
    }

    
}

TEST_CASE("Testes de Unidade - Classe Operador") {
    Sensor t("S_T", "temperatura");
    Sensor v("S_V", "rpm");
    Maquina m("M_01", &t, &v);
    Operador op("João", "MANHA");

    SUBCASE("Getter de nome") {
        CHECK(op.getNome() == "João");
    }

    SUBCASE("Excecao ao criar operador com turno invalido") {
        CHECK_THROWS_AS(Operador("Maria", "MADRUGADA"), std::invalid_argument);
    }

    SUBCASE("Alocacao de maquina") {
        op.alocarMaquina(&m);
        // sem crash = ok
        CHECK_NOTHROW(op.alocarMaquina(&m));
    }

    SUBCASE("Desatribuicao de maquina") {
        op.alocarMaquina(&m);
        CHECK_NOTHROW(op.desatribuirMaquina(&m));
    }
}

TEST_CASE("Testes adicionais - Classe Sensor") {
    Sensor s("S_01", "temperatura");

    SUBCASE("Historico vazio inicialmente") {
        CHECK(s.getHistoricoVazio() == true);
    }

    SUBCASE("Historico nao vazio apos registro") {
        s.registraHist(35.0);
        CHECK(s.getHistoricoVazio() == false);
    }

    SUBCASE("Getter de id") {
        CHECK(s.getId() == "S_01");
    }

    SUBCASE("Getter de tipo") {
        CHECK(s.getTipo() == "temperatura");
    }

    SUBCASE("Excecao ao calcular max com historico vazio") {
        CHECK_THROWS(s.calcularMaxRegistrado());
    }

    SUBCASE("Excecao ao calcular min com historico vazio") {
        CHECK_THROWS(s.calcularMinRegistrado());
    }

    SUBCASE("Excecao ao chamar alerta com historico vazio") {
        CHECK_THROWS(s.alerta());
    }
}

TEST_CASE("Testes adicionais - Classe AlertaManager") {
    AlertaManager manager;
    Sensor s("S_01", "temperatura");

    SUBCASE("Severidade LEVE") {
        s.registraHist(46.0); // pouco acima do limMax 45
        CHECK(manager.classificarSeveridade(&s) == "S_01 LEVE");
    }

    SUBCASE("manterFilas move alerta resolvido") {
        s.registraHist(50.0); // em alerta
        manager.receberAlertas(&s);
        CHECK(manager.getAtivos().size() == 1);
        s.registraHist(35.0); // resolvido
        manager.manterFilas(&s);
        CHECK(manager.getResolvidos().size() == 1);
        CHECK(manager.getAtivos().size() == 0);
    }
}

TEST_CASE("Testes adicionais - Classe Maquina") {
    Sensor t("S_T", "temperatura");
    Sensor v("S_V", "rpm");
    Maquina m("M_01", &t, &v);

    SUBCASE("ligarDesligar liga a maquina") {
        m.ligarDesligar(true);
        CHECK(m.getStatus() == Maquina::ATIVA);
    }

    SUBCASE("ligarDesligar desliga a maquina") {
        m.ligarDesligar(true);
        m.ligarDesligar(false);
        CHECK(m.getStatus() == Maquina::DESLIGADA);
    }

    SUBCASE("modoMarcha ativa quando ATIVA") {
        m.ligarDesligar(true);
        CHECK(m.modoMarcha() == true);
        CHECK(m.getStatus() == Maquina::MARCHA);
    }

    SUBCASE("atualizarEstado quebra com sensor em alerta") {
        m.ligarDesligar(true);
        t.registraHist(99.0);
        v.registraHist(10000.0);
        m.atualizarEstado();
        CHECK(m.getStatus() == Maquina::QUEBRADA);
    }
    
}
TEST_CASE("Testes de Cobertura - Forcando Excecoes e Metodos Ocultos") {
    
    SUBCASE("Relatorio - Disparo de Excecoes e Anomalias") {
        Relatorio rel;
        CHECK_THROWS_AS(rel.registraTempMaxMin(nullptr), std::invalid_argument);
        CHECK_THROWS_AS(rel.registraRpmMaxMin(nullptr), std::invalid_argument);
        CHECK_THROWS_AS(rel.registraAnomalia(nullptr), std::invalid_argument);
        CHECK_THROWS_AS(rel.registrarDesligamentoAlerta(nullptr), std::invalid_argument);
        
        Sensor t("T_COV", "temperatura");
        Sensor v("V_COV", "rpm");
        auto maq = std::make_shared<Maquina>("MAQ_COV", &t, &v);
        
        maq->ligarDesligar(true);
        t.registraHist(99.0); 
        v.registraHist(10000.0);
        maq->atualizarEstado();
        CHECK_NOTHROW(rel.registraAnomalia(maq));
    }

    SUBCASE("AlertaManager - Historicos e Ponteiros Nulos") {
        AlertaManager am;
        CHECK_THROWS_AS(am.receberAlertas(nullptr), std::invalid_argument);
        CHECK_THROWS_AS(am.classificarSeveridade(nullptr), std::invalid_argument);
        CHECK_THROWS_AS(am.manterFilas(nullptr), std::invalid_argument);
        CHECK_THROWS_AS(am.registrarHistóricos(nullptr), std::invalid_argument);

        Sensor t("T_COV2", "temperatura");
        t.registraHist(50.0);
        CHECK_NOTHROW(am.registrarHistóricos(&t));
    }

    SUBCASE("Operador - Realocacao e Excecoes de Nulo") {
        Operador op("Ana", "TARDE");
        CHECK_THROWS_AS(op.alocarMaquina(nullptr), std::invalid_argument);
        CHECK_THROWS_AS(op.desatribuirMaquina(nullptr), std::invalid_argument);
        
        Sensor t("T_COV3", "temperatura"); 
        Sensor v("V_COV3", "rpm");
        Maquina m("M_COV3", &t, &v);
        Operador op2("Beto", "NOITE");
        
        CHECK_THROWS_AS(op.realocarMaquina(nullptr, &m), std::invalid_argument);
        CHECK_THROWS_AS(op.realocarMaquina(&op2, nullptr), std::invalid_argument);
        CHECK_NOTHROW(op.realocarMaquina(&op2, &m));
    }

    SUBCASE("Sessao - Rotinas de Relatorio e Salvamento") {
        Sessao s;
        std::vector<std::shared_ptr<Maquina>> listaVazia;
        CHECK_NOTHROW(s.relatorioSessao());
        CHECK_NOTHROW(s.contarMaquinasAtivas(listaVazia));
        CHECK_NOTHROW(s.salvarSessao(listaVazia));
    }

    SUBCASE("SistemaMonitor - Validacoes e Exibicao") {
        SistemaMonitor sm;
        CHECK_THROWS_AS(sm.adicionarMaquinas(nullptr), std::invalid_argument);
        CHECK_THROWS_AS(sm.removerMaquinas(""), std::invalid_argument);
        CHECK_THROWS_AS(sm.cadastrarOperador(nullptr), std::invalid_argument);
        
        auto op = std::make_shared<Operador>("Carlos", "MANHA");
        sm.cadastrarOperador(op);
        
        Sensor t("T_COV4", "temperatura"); 
        Sensor v("V_COV4", "rpm");
        auto maq = std::make_shared<Maquina>("M_COV4", &t, &v);
        sm.adicionarMaquinas(maq);
        
        CHECK_NOTHROW(sm.atribuirMaquinasOperador());
        CHECK_NOTHROW(sm.exibirDados());
        CHECK_NOTHROW(sm.cicloMonitoramento());
    }
    
    SUBCASE("ProtocoloMarcha - Abortos por Quebra de Sincronia") {
        ProtocoloMarcha pm;
        std::vector<std::shared_ptr<Maquina>> listaCorrompida;
        listaCorrompida.push_back(nullptr);
        
        CHECK_THROWS_AS(pm.quedaEnergia(listaCorrompida), std::runtime_error);
        CHECK_THROWS_AS(pm.equalizarRPM(listaCorrompida), std::runtime_error);
        CHECK_THROWS_AS(pm.modoNormal(listaCorrompida), std::runtime_error);
    }
}