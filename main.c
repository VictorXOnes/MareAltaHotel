#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//ESTRUTURAS.
struct Cliente {
    char nome[80];
    char cpf[12];
    char telefone[12];
    int indiceHotelReservado;
    int tipoQuartoReservado;
    int numeroQuartoReservado;
    char checkin[11];  // (dd/mm/aaaa).
    char checkout[11]; // (dd/mm/aaaa).
    int statusPagamento; // 0 = NÃO PAGO, 1 = PAGO
};

struct Hotel {
    char nome[50];
    int quartosLuxuososDisponiveis[10];
    int quartosPadraoDisponiveis[4];
    char checkin[11];  // (dd/mm/aaaa).
    char checkout[11]; // (dd/mm/aaaa).
};

//FUNÇÃO PRINCIPAL.
int main() {
    setlocale(LC_ALL, "Portuguese");

    int senhaFuncionario = 1234;
    int tentativasRestantes = 3;

    struct Cliente clientes[100];
    int numClientes = 0;

    int sair = 0;

    struct Hotel hoteis[3];
    strcpy(hoteis[0].nome, "Hotel Maré Alta - Niterói (RJ)");
    strcpy(hoteis[1].nome, "Hotel Maré Alta - Salvador (BA)");
    strcpy(hoteis[2].nome, "Hotel Maré Alta - Fortaleza (CE)");

    int escolha;

    int clienteIndex = -1;
    int indiceHotelReservado;
    int tipoQuartoReservado;
    int numeroQuartoReservado;
    time_t checkin_time;

    do {
        printf("#****************************#\n");
        printf("#       MENU DE OPÇÕES       #\n");
        printf("#****************************#\n");
        printf("# 1- Fazer Cadastro          #\n");
        printf("# 2- Realizar Reserva        #\n");
        printf("# 3- Cancelar Reserva        #\n");
        printf("# 4- Efetuar Pagamento       #\n");
        printf("# 5- Área do Funcionário     #\n");
        printf("# 6- Sair                    #\n");
        printf("#****************************#\n");
        printf("# Escolha a opção desejada:  #\n");
        printf("#****************************#\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                system("cls");
                printf("********************************************************************************\n");
                printf("                             ÁREA DE CADASTRO\n");
                printf("********************************************************************************\n");

                //MÁXIMO DE CLIENTES QUE O SISTEMA ARMAZENA.
                if (numClientes >= 100) {
                    printf("Desculpe, já atingimos o número máximo de cadastros. Tente novamente mais tarde.\n");
                } else {
                    // ARMAZENAR NOME.
                    printf("INFORME SEU NOME COMPLETO: ");
                    scanf(" %79[^\n]", clientes[numClientes].nome);

                    //ARMAZENAR CPF.
                    printf("INFORME SEU CPF (11 dígitos, somente números): ");
                    scanf("%11s", clientes[numClientes].cpf);

                    //ARMAZENAR TELEFONE.
                    printf("INFORME SEU TELEFONE: ");
                    scanf("%lls", &clientes[numClientes].telefone);
                    printf("\nCliente Cadastrado com Sucesso!\n");

                    //INCREMENTAR NÚMERO DE CLIENTES.
                    numClientes++;
                }

                system("pause");
                system("cls");
                break;

            case 2:
                system("cls");
                printf("********************************************************************************\n");
                printf("                             ÁREA DE HOSPEDAGEM\n");
                printf("********************************************************************************\n");

                //VERIFICAR SE O CLIENTE ESTÁ CADASTRADO.
                char cpf[12];
                printf("Informe seu CPF (11 dígitos, somente números): ");
                scanf("%11s", cpf);

                int clienteIndex = -1;

                for (int i = 0; i < numClientes; i++) {
                    if (strcmp(clientes[i].cpf, cpf) == 0) {
                        clienteIndex = i;
                        break;
                    }
                }

                if (clienteIndex == -1) {
                    printf("Cliente não encontrado. Faça o cadastro primeiro.\n");
                    system("pause");
                    system("cls");
                    break;
                }


                system("cls");
    printf("********************************************************************************\n");
    printf("                           ÁREA DE HOSPEDAGEM\n");
    printf("********************************************************************************\n");
    printf("Nome: %s\n", clientes[clienteIndex].nome);
    printf("CPF: %s\n", clientes[clienteIndex].cpf);
    printf("Telefone: %s\n\n", clientes[clienteIndex].telefone);
    printf("********************************************************************************\n");

    //ESCOLHA DE HOTEL.
    printf("Escolha um hotel para hospedagem:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d - %s\n", i + 1, hoteis[i].nome);
    }

    int escolhaHotel;
    scanf("%d", &escolhaHotel);
    escolhaHotel--;

    if (escolhaHotel < 0 || escolhaHotel > 2) {
        printf("Escolha de hotel inválida.\n");
        system("pause");
        system("cls");
        break;
    }

    struct Hotel hotelEscolhido = hoteis[escolhaHotel];

    printf("Quartos disponíveis no %s:\n", hotelEscolhido.nome);

    for (int i = 0; i < 14; i++) {
        if (i < 10) {
            if (i < 9 && hotelEscolhido.quartosLuxuososDisponiveis[i] == 0) {
                printf("%d - Quarto %d - Modelo Luxuoso\n", i + 1, i + 1);
            } else if (i == 9 && hotelEscolhido.quartosLuxuososDisponiveis[i] == 0) {
                printf("%d - Quarto 10 - Modelo Luxuoso\n", i + 1);
            }
        } else {
            if (hotelEscolhido.quartosPadraoDisponiveis[i - 10] == 0) {
                printf("%d - Quarto %d - Modelo Padrão\n", i + 1, i - 9);
            }
        }
    }

    //ESCOLHER O NÚMERO DO QUARTO.
    int numeroQuarto;
    printf("Escolha o número do quarto: ");
    scanf("%d", &numeroQuarto);

    int tipoQuarto;
    if (numeroQuarto <= 10) {
        tipoQuarto = 1; //LUXUOSO
    } else if (numeroQuarto > 10 && numeroQuarto <= 14) {
        tipoQuarto = 2; //PADRÃO
    } else {
        printf("Número de quarto inválido.\n");
        system("pause");
        system("cls");
        break;
    }

//SOLICITAR AS DATAS DE CHECK-IN E CHECK-OUT.
char checkin[11];
char checkout[11];

printf("Informe a data de check-in (dd/mm/aaaa): ");
scanf("%s", checkin);

printf("Informe a data de check-out (dd/mm/aaaa): ");
scanf("%s", checkout);

    //VERIFICAR SE A DATA É VÁLIDA.
    bool dataValida(const char *data) {
    int dia, mes, ano;
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        return false; //FORMATOS INCORRETOS.
    }

    if (ano < 1900 || ano > 2099 || mes < 1 || mes > 12 || dia < 1) {
        return false; //VERIFICAR LIMITES.
    }

    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return false; //MESES COM 30 DIAS.
    }

    if (mes == 2) {
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
            if (dia > 29) {
                return false; //FEVEREIRO BISSEXTO.
            }
        } else {
            if (dia > 28) {
                return false; //FEVEREIRO NÃO BISSEXTO.
            }
        }
    } else if (dia > 31) {
        return false; //MESES COM 31 DIAS.
    }

    return true;
}

    //VALIDAÇÃO DE DATAS.
    if (!dataValida(checkin) || !dataValida(checkout)) {
    printf("Datas de check-in ou check-out inválidas.\n");
    system("pause");
    system("cls");
    break;
}
    //ARMAZENAR RESERVA.
    if (tipoQuarto == 1) {
        if (numeroQuarto <= 10) {
            hoteis[escolhaHotel].quartosLuxuososDisponiveis[numeroQuarto - 1] = 1; //MARCAR COMO OCUPADO.
        } else {
            printf("Número de quarto de luxo inválido.\n");
            system("pause");
            system("cls");
            break;
        }
    } else {
        if (numeroQuarto > 10 && numeroQuarto <= 14) {
            hoteis[escolhaHotel].quartosPadraoDisponiveis[numeroQuarto - 11] = 1; //MARCAR COMO OCUAPADO.
        } else {
            printf("Número de quarto padrão inválido.\n");
            system("pause");
            system("cls");
            break;
        }
    }
//ARMAZENAR AS DATAS DE CHECK IN/OUT NA ESTRUTURA CLIENTE.
strcpy(clientes[clienteIndex].checkin, checkin);
strcpy(clientes[clienteIndex].checkout, checkout);

    clientes[clienteIndex].indiceHotelReservado = escolhaHotel;
    clientes[clienteIndex].tipoQuartoReservado = tipoQuarto;
    clientes[clienteIndex].numeroQuartoReservado = numeroQuarto;

    printf("Hospedagem realizada com sucesso!\n");
    printf("Siga para a área de Pagamentos\n");

    system("pause");
    system("cls");
    break;

            case 3:

    system("cls");
    printf("********************************************************************************\n");
    printf("                          ÁREA DE CANCELAMENTO\n");
    printf("********************************************************************************\n\n");


    printf("Informe seu CPF: ");
    scanf("%11s", &cpf);

    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].cpf == cpf) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("Cliente não encontrado. Faça o cadastro primeiro.\n");
        system("pause");
        system("cls");
        break;
    }

    //VERIFICAR SE O CLIENTE TEM UMA RESERVA.
    if (clientes[clienteIndex].indiceHotelReservado == -1) {
        printf("Você não possui uma reserva ativa.\n");
        system("pause");
        system("cls");
        break;
    }

    int indiceHotelReservado = clientes[clienteIndex].indiceHotelReservado;
    int tipoQuartoReservado = clientes[clienteIndex].tipoQuartoReservado;

    //EXIBIR AS INFORMAÇÕES DA RESERVA ATUAL.
    printf("Você tem uma reserva no seguinte quarto:\n");
    printf("Hotel: %s\n", hoteis[indiceHotelReservado].nome);
    printf("Tipo de quarto: %s\n", (tipoQuartoReservado == 1) ? "Luxuoso" : "Padrão");
    printf("Número do quarto: %d\n", clientes[clienteIndex].numeroQuartoReservado);
    printf("Data de check-in: %s\n", clientes[clienteIndex].checkin);
    printf("Data de check-out: %s\n", clientes[clienteIndex].checkout);

    //SOLICITAR A CONFIRMAÇÃO PARA REALIZAR O CANCELAMENTO.
    printf("\nDeseja cancelar esta reserva? (1-Sim, 2-Não): ");
    int confirmacao;
    scanf("%d", &confirmacao);

    if (confirmacao == 1) {
        //MARCAR QUARTO COMO DÍSPONIVEL NOVAMENTE.
        if (tipoQuartoReservado == 1) {
            hoteis[indiceHotelReservado].quartosLuxuososDisponiveis[clientes[clienteIndex].numeroQuartoReservado - 1] = 0; // Marcar como disponível
        } else {
            hoteis[indiceHotelReservado].quartosPadraoDisponiveis[clientes[clienteIndex].numeroQuartoReservado - 11] = 0; // Marcar como disponível
        }

        //LIMPAR AS INFORMAÇÕES DA RESERVA DO CLIENTE.
        clientes[clienteIndex].indiceHotelReservado = -1;
        clientes[clienteIndex].tipoQuartoReservado = -1;
        clientes[clienteIndex].numeroQuartoReservado = -1;

        printf("Hospedagem cancelada com sucesso!\n");
    } else {
        printf("Ação cancelada.\n");
    }

    system("pause");
    system("cls");
    break;

case 4:
    system("cls");
    printf("********************************************************************************\n");
    printf("                            ÁREA DE PAGAMENTOS\n");
    printf("********************************************************************************\n\n");


    // Limpar o buffer de entrada.
    while (getchar() != '\n');

    // Ler o CPF.
    printf("Informe seu CPF (11 dígitos, somente números): ");
    fgets(cpf, sizeof(cpf), stdin);

    // Remover caracteres não numéricos.
    for (int i = 0; cpf[i] != '\0'; i++) {
        if (!isdigit(cpf[i])) {
            cpf[i] = '\0';
            break;
        }
    }



    // Procurar o cliente pelo CPF.
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            clienteIndex = i;
            break;
        }
    }

    if (clienteIndex == -1) {
        printf("Cliente não encontrado. Faça o cadastro primeiro.\n");
        system("pause");
        system("cls");
        break;
    }

    // Verificar se o cliente possui uma reserva.
    if (clientes[clienteIndex].indiceHotelReservado == -1) {
        printf("Você não possui uma reserva ativa. Faça uma reserva primeiro.\n");
        system("pause");
        system("cls");
        break;
    }

    //EXIBIR INFORMAÇÕES DA RESERVA ATUAL.
    printf("Revisão da Hospedagem:\n");
    printf("Hotel: %s\n", hoteis[clientes[clienteIndex].indiceHotelReservado].nome);
    printf("Tipo de quarto: %s\n", (clientes[clienteIndex].tipoQuartoReservado == 1) ? "Luxuoso" : "Padrão");
    printf("Número do quarto: %d\n", clientes[clienteIndex].numeroQuartoReservado);
    printf("Data de check-in: %s\n", clientes[clienteIndex].checkin);
    printf("Data de check-out: %s\n", clientes[clienteIndex].checkout);
    printf("********************************************************************************\n");
    //CALCULAR VALOR TOTAL DE PAGAMENTO.
    char checkinStr[11];
    char checkoutStr[11];
    strcpy(checkinStr, clientes[clienteIndex].checkin);
    strcpy(checkoutStr, clientes[clienteIndex].checkout);

    int diaCheckin, mesCheckin, anoCheckin;
    int diaCheckout, mesCheckout, anoCheckout;

    sscanf(checkinStr, "%d/%d/%d", &diaCheckin, &mesCheckin, &anoCheckin);
    sscanf(checkoutStr, "%d/%d/%d", &diaCheckout, &mesCheckout, &anoCheckout);

    time_t checkin_time = {0};
    time_t checkout_time = {0};
    struct tm tm_checkin = {0};
    struct tm tm_checkout = {0};

    tm_checkin.tm_year = anoCheckin - 1900;
    tm_checkin.tm_mon = mesCheckin - 1;
    tm_checkin.tm_mday = diaCheckin;

    tm_checkout.tm_year = anoCheckout - 1900;
    tm_checkout.tm_mon = mesCheckout - 1;
    tm_checkout.tm_mday = diaCheckout;

    checkin_time = mktime(&tm_checkin);
    checkout_time = mktime(&tm_checkout);

    double diferencaDias = difftime(checkout_time, checkin_time) / (60 * 60 * 24);
    double valorTotal = 0.0;
    double diariaSemDesconto;

    if (clientes[clienteIndex].tipoQuartoReservado == 1) {
        diariaSemDesconto = 3210;
    } else {
        diariaSemDesconto = 1060;
    }

    //LOOP QUE APLICA O DESCONTO DE 5% DE SEGUNDA A QUINTA.
    time_t current_day = checkin_time;

    for (int i = 0; i < diferencaDias; i++) {
        struct tm* tm_current_day = localtime(&current_day);

        //VERIFICADOR DE DIA, PARA SABER SE É SEGUNDA A QUINTA(0 a 3, onde = domingo).
        if (tm_current_day->tm_wday >= 1 && tm_current_day->tm_wday <= 4) {
            valorTotal += (0.95 * diariaSemDesconto); //APLICAR DESCONTO DE 5%.

        } else {
            valorTotal += diariaSemDesconto; //SEM DESCONTO.
        }

        //AVANÇAR DIA.
        current_day += 24 * 60 * 60; //ADICIONAR UM DIA EM SEGUNDOS.
    }


    printf("Quantidade de dias: %.0lf\n", diferencaDias);
    printf("Diária: R$%.2lf\n", diariaSemDesconto);
    printf("Total a pagar: R$%.2lf\n", valorTotal);

    double valorTotalComDesconto = valorTotal; //VALOR INICIAL É IGUAL AO TOTAL SEM APLICAR DESCONTO.


    for (int i = 0; i < diferencaDias; i++) {
        struct tm* tm_current_day = localtime(&current_day);

       //VERIFICAR SE É DIAS DE SEGUNDA A QUINTA.
        if (tm_current_day->tm_wday >= 1 && tm_current_day->tm_wday <= 4) {
            valorTotalComDesconto -= (0.05 * diariaSemDesconto);
        }

        //AVANÇAR PARA O PROXIMO DIA.
        current_day += 24 * 60 * 60;
    }

    printf("Total a pagar com desconto: R$%.2lf\n", valorTotalComDesconto);

//GERADOR DE CÓDIGO ALEATÓRIO PARA EFETUAR O PAGAMENTO.
char codigoPagamento[33];
const char caracteresValidos[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

for (int i = 0; i < 32; i++) {
    codigoPagamento[i] = caracteresValidos[rand() % (sizeof(caracteresValidos) - 1)];
}
codigoPagamento[32] = '\0';

//EXIBIR O CÓDIGO DE PAGAMENTO.
printf("Seu código de pagamento é: %s\n", codigoPagamento);

    //CONFIRMAÇÃO OU NÃO DE PAGAMENTO.
    printf("Deseja efetuar o pagamento? (1-Sim, 2-Não): ");
    int opcaoPagamento;
    scanf("%d", &opcaoPagamento);

    if (opcaoPagamento == 1) {
    clientes[clienteIndex].statusPagamento = 1;
    clientes[clienteIndex].indiceHotelReservado = -1;
    clientes[clienteIndex].tipoQuartoReservado = -1;
    clientes[clienteIndex].numeroQuartoReservado = -1;
    printf("Pagamento efetuado com sucesso!\n");
} else {
    printf("Pagamento cancelado.\n");
}

    system("pause");
    system("cls");
    break;

            case 5:
    {   int senhaFuncionario = 1234;
int tentativasRestantes = 3;
int senhaDigitada;
char nomeFuncionario[50];  //ARMAZENAR O NOME DO FUNCIONÁRIO.

//PEDIR NOME DO FUNCIONÁRIO.
printf("Informe o nome do funcionário: ");
scanf(" %s", nomeFuncionario);
int escolhadoFun = -1;
do {
    printf("Digite a senha, %s (Tentativas restantes: %d): ", nomeFuncionario, tentativasRestantes);
    scanf("%d", &senhaDigitada);

    if (senhaDigitada == senhaFuncionario) {
        system("cls");
                printf("Acesso Permitido com Sucesso!\n");

                printf("\nOlá, %s, o que deseja fazer?\n", nomeFuncionario);
                printf("\n#****************************#\n");
                printf("#    MENU DO FUNCIONÁRIO     #\n");
                printf("#****************************#\n");
                printf("# 1- Clientes Cadastrados    #\n");
                printf("# 2- Quartos Reservados      #\n");
                printf("# 3- Pagamentos              #\n");
                printf("# 4- Voltar                  #\n");
                printf("#****************************#\n");
                printf("# Escolha a opção desejada:  #\n");
                printf("#****************************#\n");
                scanf("%d", &escolhadoFun);

                switch (escolhadoFun) {
                   case 1:
                       system("cls");
    //EXIBIR TODOS OS CLIENTES CADASTRADOS NO SISTEMA.
    if (numClientes == 0) {
        printf("Nenhum cadastro disponível.\n");
    } else {
        for (int i = 0; i < numClientes; i++) {
            printf("Cliente %d:\n", i + 1);
            printf("Nome: %s\n", clientes[i].nome);
            printf("CPF: %11s\n", clientes[i].cpf);
            printf("Telefone: %s\n", clientes[i].telefone);
            printf("********************************************************************************\n");
        }
    }
    break;

case 2:
    system("cls");
    //EXIBIR QUARTOS QUE ESTÁ RESERVADO COM CADA CLIENTE.
    if (numClientes == 0) {
        printf("Nenhum cadastro disponível.\n");
    } else {
        int quartosReservados = 0;
        for (int i = 0; i < numClientes; i++) {
            if (clientes[i].indiceHotelReservado != -1) {
                printf("Cliente %d - %s (CPF: %11s)\n", i + 1, clientes[i].nome, clientes[i].cpf);
                int indiceHotelReservado = clientes[i].indiceHotelReservado;
                printf("Hotel: %s\n", hoteis[indiceHotelReservado].nome);
                printf("Tipo de quarto: %s\n", (clientes[i].tipoQuartoReservado == 1) ? "Luxuoso" : "Padrão");
                printf("Número do quarto: %d\n", clientes[i].numeroQuartoReservado);
                printf("Data de check-in: %s\n", clientes[i].checkin);
                printf("Data de check-out: %s\n", clientes[i].checkout);
                quartosReservados++;
                printf("********************************************************************************\n");
            }
        }
        if (quartosReservados == 0) {
            printf("Nenhum quarto reservado.\n");
        }
    }
    break;

case 3:
    system("cls");
    if (numClientes == 0) {
        printf("Nenhuma informação disponível.\n");
    } else {
        printf("Status de pagamento dos clientes:\n");
        for (int i = 0; i < numClientes; i++) {
            printf("Cliente %d - %s (CPF: %s)\n", i + 1, clientes[i].nome, clientes[i].cpf);
            if (clientes[i].statusPagamento == 0) {
                printf("Status de pagamento: Não pago\n");
            } else {
                printf("Status de pagamento: Pago\n");
            }
            printf("********************************************************************************\n");
        }
    }
    break;
                    case 4:
                        system("pause");
                        system("cls");
                        break;

                    default:
                        printf("Opção inválida. Tente novamente.\n");
                }
            } else {
                tentativasRestantes--;
                if (tentativasRestantes == 0) {
                        system("cls");
                    printf("Acesso Negado. Máximo de tentativas atingido.\n");
                    break;
                }
                printf("Acesso Negado. Tentativas restantes: %d\n", tentativasRestantes);
            }
        } while (escolhadoFun != 4);
        break;
    }
                break;

            case 6:
                //SAIR DO PROGRAMA.
                printf("\nSaindo do sistema... Até mais!\n");
                sair = 1;
                break;


            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (escolha != 6);

    return 0;
}
