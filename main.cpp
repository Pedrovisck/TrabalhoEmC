#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PACIENTES 100 // n�mero m�ximo de pacientes que podem ser registrados
#define MAX_SALAS 10 // n�mero de salas de atendimento dispon�veis

// Estrutura que representa um paciente
struct Paciente {
    char nome[50];
    char telefone[20];
    char cpf[20];
    time_t horario_chegada;
};

// Vari�veis globais
struct Paciente pacientes[MAX_PACIENTES]; // vetor de pacientes
int num_pacientes = 0; // n�mero atual de pacientes registrados
int salas_disponiveis[MAX_SALAS]; // vetor que guarda as salas dispon�veis
int num_salas_disponiveis = MAX_SALAS; // n�mero atual de salas dispon�veis

// Fun��es
void tela_apresentacao();
void tela_marcar_consulta();
void tela_chamar_paciente();
void tela_finalizar_sistema();
int comparar_horario_chegada();

int main() {
    int opcao;

    // Inicializa as salas dispon�veis
    for (int i = 0; i < MAX_SALAS; i++) {
        salas_disponiveis[i] = i + 1;
    }

    do {
        tela_apresentacao();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                tela_marcar_consulta();
                break;
            case 2:
                tela_chamar_paciente();
                break;
            case 3:
                tela_finalizar_sistema();
                break;
            default:
                printf("Op��o inv�lida.\n");
        }

    } while(opcao != 3);

    return 0;
}

// Implementa��o das fun��es

// Tela de apresenta��o
void tela_apresentacao() {
    printf("\nBem-vindo ao sistema de atendimento.\n");
    printf("Escolha uma op��o:\n");
    printf("1 - Marcar consulta\n");
    printf("2 - Chamar paciente para consulta\n");
    printf("3 - Finalizar sistema\n");
}

// Tela de marca��o de consulta
void tela_marcar_consulta() {
    char nome[50], telefone[20], cpf[20];
    time_t horario_chegada;

    printf("Digite o nome do paciente: \n");
    scanf("%s", nome);

    printf("Digite o telefone do paciente: \n");
    scanf("%s", telefone);

    printf("Digite o CPF do paciente: \n");
    scanf("%s", cpf);

    horario_chegada = time(NULL); // obt�m o hor�rio atual

    // Cria um novo paciente e adiciona ao vetor de pacientes
    struct Paciente novo_paciente;
    strcpy(novo_paciente.nome, nome);
    strcpy(novo_paciente.telefone, telefone);
    strcpy(novo_paciente.cpf, cpf);
    novo_paciente.horario_chegada = horario_chegada;

    pacientes[num_pacientes] = novo_paciente;
    num_pacientes++;

    printf("Consulta marcada com sucesso.\n");
}

int comparar_horario_chegada(const void *a, const void *b) {
    struct Paciente *pa = (struct Paciente*) a;
    struct Paciente *pb = (struct Paciente*) b;

    if (pa->horario_chegada < pb->horario_chegada) {
        return -1;
    } else if (pa->horario_chegada > pb->horario_chegada) {
        return 1;
    } else {
        return 0;
    }
}

void tela_chamar_paciente() {
    if (num_pacientes == 0) {
        printf("N�o h� pacientes registrados.\n");
        return;
    }

    if (num_salas_disponiveis == 0) {
        printf("N�o h� salas dispon�veis no momento.\n");
        return;
    }

    // Ordena os pacientes por ordem de chegada
    
    qsort(pacientes, num_pacientes, sizeof(struct Paciente), comparar_horario_chegada);


    // Escolhe uma sala aleat�ria
    srand(time(NULL));
    int sala_escolhida = salas_disponiveis[rand() % num_salas_disponiveis];

    // Remove a sala escolhida do vetor de salas dispon�veis
    for (int i = 0; i < num_salas_disponiveis; i++) {
        if (salas_disponiveis[i] == sala_escolhida) {
            for (int j = i; j < num_salas_disponiveis - 1; j++) {
                salas_disponiveis[j] = salas_disponiveis[j + 1];
            }
            num_salas_disponiveis--;
            break;
        }
    }

    // Chama o pr�ximo paciente
    struct Paciente proximo_paciente = pacientes[0];
    for (int i = 0; i < num_pacientes - 1; i++) {
        pacientes[i] = pacientes[i + 1];
    }
    num_pacientes--;

    // Mostra os dados do paciente chamado e a sala escolhida
    printf("Chamando paciente: %s\n", proximo_paciente.nome);
    printf("Telefone: %s\n", proximo_paciente.telefone);
    printf("CPF: %s\n", proximo_paciente.cpf);
    printf("Hor�rio de chegada: %s\n", ctime(&proximo_paciente.horario_chegada));
    printf("Sala escolhida: %d\n", sala_escolhida);
}


// Tela de finaliza��o do sistema
void tela_finalizar_sistema() {
printf("Sistema finalizado.\n");
}
