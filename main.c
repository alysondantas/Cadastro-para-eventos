/*******************************************************************************

Autor: Alyson Felipe Oliveira Dantas

Componente Curricular: MI - Algoritmos - P04

Concluido em: 07/10/2015

Declaro que este c�digo foi elaborado por mim de forma individual e n�o cont�m nenhum

trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e

apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo

de outra autoria que n�o a minha est� destacado com uma cita��o para o autor e a fonte

do c�digo, e estou ciente que estes trechos n�o ser�o considerados para fins de avalia��o.

******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//biblioteca para manipular strings
#include <time.h>//biblioteca para pegar a hora do sistema

typedef struct{//celula da lista que foi criada uasndo uma struct
	char nome[60];//campo da celula para o nome
	char cpf[14];//campo para cpf
	char email[30];//campo para o email
	char matriculas[20];//campo para o numero de matricula
	char data_nascimento[20];//campo para a dataa de nascimento
	char ocupacao;//campo para ocupa��o sendo professor-P ou aluno-A
	struct participantes *proximo;//ponteiro para a proxima celula
}Participantes; //nome do tipo definido por typedef

Participantes* cadastrar(Participantes *lista,char *data[11]);//prototipo da fun�ao que cadastra novos participantes
Participantes* editar(Participantes *lista);//prototipo da fun�ao que verifica qual o participante editar
Participantes* excluir(Participantes *lista);//prototipo da fun�ao que exclui um participante
Participantes* editar_excluir(Participantes *lista);//prototipo da fun�ao que chama as fun�oes editar e excluir
Participantes* editar_participantes(Participantes *lista_aux);//prototipo da fun�ao que edita participantes
Participantes* listar_participantes(Participantes *lista);//prototipo da fun�ao que da escolha ao usuario de como listar participantes
void listar_ocupacao(Participantes *lista);//prototipo da fun�ao que lista por ocupa��o professor ou aluno
void consulta_cpf(Participantes *lista);//prototipo da fun�ao que faz a consulta por cpf
void verifica_data_limite(char *data[11]);//prototipo da fun�ao que verifica se ja passou da data limite de inscri�oes
void sair_salva_cadastro(Participantes *lista);//prototipo da fun�ao que finaliza o programa e salva os cadastros em um arquivo
Participantes* ordena_lista(Participantes *lista);//prototipo da fun�ao que que ordena a lista por ordem alfabetica
void mostrar_lista_ordenada(Participantes *lista);//prototipo da fun�ao que mostra a lista apos ser ordenada
Participantes* ler_cadastro_anterior(Participantes *lista);//prototipo da fun�ao que faz a leitura do arquivo criado

int main() {
	int opcao_menu=0;//variavel para o switch como op��o do menu principal
	char data[11];//variavel com a data limite para novas inscri��es
	
	verifica_data_limite(data);//chama a fun��o para fericar a data limite que esta salva no arquivo de texto
	Participantes *lista = NULL;//cria a lista inicializando nula
	lista=ler_cadastro_anterior(lista);//lista recebe a leitura do arquivo de texto
	for(;;){//for infinito para o menu principal
	system("cls");//limpa a tela
	printf("============MENU CADASTRO DE PARTICIPANTES - SEMIC 2015============\n");
	printf("Voc� deseja:\n	1-Cadastrar uma pessoa no evento\n	2-Editar ou excluir um cadastro:\n	3-Listar os participantes.\n	4-Sair do programa e salvar cadastro.\n");//menu criado pra navegar entre as op��es que est�o nas fun�oes
	scanf("%i",&opcao_menu);//pega a op��o do menu
	getchar();//captura o enter
	switch(opcao_menu){
		case 1://caso seja pra cadastrar
			lista=cadastrar(lista,data);//lista recebe as modifica��es apos cadastrar nova pessoa
			break;
		case 2://caso seja pra editar ou excluir
			lista=editar_excluir(lista);//lista recebe a modifica��o opinada que vem de outro menu
			break;
		case 3:// caso seja pra listar participantes por ordem alfabetica ou cpf
			lista=listar_participantes(lista);//lista recebe a lista ja ordenada
			break;
		case 4://caso seja pra sair do pragrama
			sair_salva_cadastro(lista);//chama a fun��o de salvar e sair
			break;
		default://se for qualquer outra op��o invalida usuario recebe mensagem de erro
			printf("Op��o invalida.\n");
			break;
	}
}
	return 0;
}

Participantes* cadastrar(Participantes *lista, char *data[11]){//fun��o que cadastra novos participantes
	int resultado;//variavel que recebe resultado da compara��o
	char data_hoje[11];//variavel pra pegar data de hoje
	_strdate(data_hoje);//fun��o pra pegar a data atual do sistema e colocar na variavel
	
	resultado=strcmpi(data,data_hoje);//strcmpi � para comparar duas strings seno insencivel a caixa alta ou caixa baixa
	if(resultado<0){//se resultado for menor que zero � porque a data ja passou da limite ent�o o usuario volta ao menu principal
		printf("A data limite para o cadastros excedeu! prescione enter para voltar ao menu. \nA data limite foi: ");
		puts(data);//exbibe a data limite
		getchar();
		return lista;
	}
	Participantes *lista_aux=lista;//um ponteiro auxiliar que aponta pra lista para percorrer a lista
	Participantes *campo;//um ponteiro para criar a celula e depois inserir na lista
	char ocupacao;// variavel para tratamento de erro caso n�o seja digitado a letra correta
	campo=(Participantes*) malloc (sizeof (Participantes));//campo recebe uma aloca��o de memoria para uma nova celula
		
		printf("Cadastrar nova pessoa:\n");//pega os dados da pessoa
		printf("Nome da pessoa:\n");
		gets(campo->nome);//captura a informa��o
		printf("CPF da pessoa:\n");
		gets(campo->cpf);//captura a informa��o
		printf("Email:\n");
		gets(campo->email);//captura a informa��o
		printf("Matricula:\n");
		gets(campo->matriculas);//captura a informa��o
		printf("Data de nascimento: exemplo 25/11/1996\n");
		gets(campo->data_nascimento);//captura a informa��o
		printf("Ocupa��o E para Estudante ou P para Professor:\n");
		scanf("%c",&ocupacao);//captura a op��o e vai pra compara��o
		getchar();//captura o enter
		if(ocupacao == 'E' || ocupacao == 'P'){//tratamento de erro caso seja digitado uma letra em caixa baixa ou uma letra incorreta
			campo->ocupacao=ocupacao;
		}else if(ocupacao == 'e'){
			campo->ocupacao='E';
		}else if(ocupacao == 'p'){
			campo->ocupacao='P';
		}else{
			printf("Voc� digitou uma ocupa��o invalida por padr�o ele sera estudante.\n");
			campo->ocupacao='E';
		}
		
	if(lista == NULL){//se a lista for vazia
		lista =(Participantes*) malloc (sizeof (Participantes));//aloca espa�o pra primeira celula
		lista=campo;//lista recebe a celula com os dados inseridos
		lista->proximo = NULL;//proximo da lista recebe nulo
	}else{
		campo->proximo = lista;//o proximo do celula criada aponta pra primeira celula da lista
		lista=campo;//e a lista aponta pra o campo assim inserindo pelo inicio
	}
	printf("Cadastro concluido. pressione enter para voltar ao menu.\n");
	getchar();//captura enter
	system("cls");//limpa a tela
	return lista;
	}
	
Participantes* editar_excluir(Participantes *lista){//fun��o para esolha entre editar ou excluir
	int opcao_menu=0;//variavel para op��o do menu
	
	for(;;){//la�o infinito para o menu
	system("cls");
	printf("Voc� deseja:\n	1-Editar um participante\n	2-Excluir um participante:\n	3-Voltar ao menu inicial.\n");//menu criado pra navegar entre as op��es que est�o nas fun�oes
	scanf("%i",&opcao_menu);
	getchar();
	switch(opcao_menu){
		case 1://se chama fun��o para editar o participante
			lista=editar(lista);//lista recebe a lista editada pela fun��o
			break;
		case 2://caso dois para excluir um participante
			lista=excluir(lista);//lista recebe lista modificada pela fun��o
			break;
		case 3:
			return lista;//volta ao menu caso seja outra op��o
			break;
		default:
			printf("Op��o invalida.\n");
			break;
	}}
}

Participantes* editar(Participantes *lista){//fun�ao que edita participantes
	Participantes *lista_aux=lista;//ponteiro auxliar para percorrer a lista
	Participantes *campos;//ponteiro para capiturar o campo de comprara��o
	int opcao_menu=0,opcao_submenu=0,contador=0,verificador=1;//varivel de op��o,de op��o do outro menu, contador, e variavel de compara��o
	campos=(Participantes*) malloc (sizeof (Participantes));//aloca espa�o de memoria para o campo
	
	printf("Voc� deseja procurar participante para editar por:\n	1-CPF.\n	2-Numero de Matricula.\n	3-Nome.\n");//menu criado pra navegar entre as op��es que est�o nas fun�oes
	scanf("%i",&opcao_menu);//seleciona a op��o
	getchar();
	switch(opcao_menu){
		case 1://se for cpf
			printf("Digite o CPF a ser procurado.");
			gets(campos->cpf);//captura o cpf
			while(lista_aux!=NULL){//percorre a lista
				verificador =strcmp(campos->cpf,lista_aux->cpf);//compara com cada elemento da lista o que foi pedido
				if(verificador==0){//se achar
					lista_aux=editar_participantes(lista_aux);//lista auxiliar recebe a fun��o para editar
					return lista;//retorna a lista
				}else{
				contador=contador+1;//incrementa o contador
				printf("\nN�o � o %i\n",contador);//por estetica mosta que n�o foi encontrado
				lista_aux=lista_aux->proximo;}}//auxiliar passa para a proxima celula
				printf("N�o foi encontrado nada correspondente. precione enter para voltar ao menu.");
			getchar();
			return lista;
			break;
		case 2:
			printf("Digite o munero de matricula a ser procurado.");
			gets(campos->matriculas);//captura a matricula
			while(lista_aux!=NULL){//percorre a lista
				verificador =strcmp(campos->matriculas,lista_aux->matriculas);//compara com cada elemento da lista o que foi pedido
				if(verificador==0){//se achar
					lista_aux=editar_participantes(lista_aux);//lista auxiliar recebe a fun��o para editar
					return lista;//retorna a lista
				}else{
				contador=contador+1;//incrementa o contador
				printf("\nN�o � o %i\n",contador);//por estetica mosta que n�o foi encontrado
				lista_aux=lista_aux->proximo;}//auxiliar passa para a proxima celula
			}
			printf("N�o foi encontrado nada correspondente. precione enter para voltar ao menu.");
			getchar();
			return lista;//retorna a lista
			break;
		case 3:
			printf("Digite o Nome a ser procurado.");
			gets(campos->nome);//captura o nome
			while(lista_aux!=NULL){//percorre a lista
				verificador =strcmp(campos->nome,lista_aux->nome);//compara com cada elemento da lista o que foi pedido
				if(verificador==0){//se achar
					lista_aux=editar_participantes(lista_aux);//lista auxiliar recebe a fun��o para editar
					return lista;//retorna a lista
					}else{
				contador=contador+1;//incrementa o contador
				printf("\nN�o � o %i\n",contador);//por estetica mosta que n�o foi encontrado
				lista_aux=lista_aux->proximo;}//auxiliar passa para a proxima celula
			}
			printf("N�o foi encontrado nada correspondente. precione enter para voltar ao menu.");
			getchar();
			return lista;//retorna a lista
			break;
		default:
			return lista;//se errar retorna a lista sem fazer nada
			printf("Op��o invalida.\n");
			break;
	}
}
	
Participantes* excluir(Participantes *lista){
	Participantes *lista_aux=lista;//cria auxiliar pra percorrer a lista em busca do pontteiro a ser comparado
	Participantes *campo;//cria ponteiro para o campo a ser comparado
	campo=(Participantes*) malloc (sizeof (Participantes));//aloca espa�o para o ponteiro 
	Participantes *lista_aux_remocao=lista;//cria um ponteiro auxiliar pra remo��o que recbe a lista
	int opcao_menu=0,verificador=1;//variaveis para o menu e para comparar
	char opcao_submenu='n';//variavel para submenu
	printf("Voc� deseja procurar participante para editar por:\n	1-CPF.\n	2-Numero de Matricula.\n	3-Nome.\n");//menu criado pra navegar entre as op��es que est�o nas fun�oes
	scanf("%i",&opcao_menu);//captura a op��o
	getchar();
	switch(opcao_menu){//verifica a op��o
		case 1:
			printf("Digite o CPF a ser procurado.");
			gets(campo->cpf);//captura o elemento a ser procurado
			while(lista_aux!=NULL){//percorre a lista pra procurar o participante
				verificador =strcmp(campo->cpf,lista_aux->cpf);//verifica se � o participante desejado
				if(verificador==0){//se for exbibe os dados do participante
					printf("Participante encontrado ele �:\n");
					printf("Nome da pessoa: ");
					puts(lista_aux->nome);		
					printf("CPF da pessoa: ");
					puts(lista_aux->cpf);
					printf("Email: ");
					puts(lista_aux->email);
					printf("Matricula: ");
					puts(lista->matriculas);
					printf("\nData de nascimento: ");
					puts(lista_aux->data_nascimento);
					printf("Ocupa��o: ");
					if(lista_aux->ocupacao == 'E'){
						printf("Estudante\n\n");
					}else if(lista_aux->ocupacao == 'P'){
						printf("Professor\n\n");
					}
					printf("Realmente deseja excluir ela s ou n");
					scanf("%c",&opcao_submenu);//pergunta se realmente o usuario deseja excluir o participantes
					getchar();
					if(opcao_submenu == 's'){//se sim
						verificador =strcmp(campo->cpf,lista->cpf);//realiza uma compara��o para ver se � o primeiro elemento
						if(verificador==0){//se for o primeiro elemento
							lista_aux_remocao=lista;//auxiliar de remo��o recebe o primeiro elemento
							lista=lista->proximo;//a lista passa a iniciar no segundo
							free(lista_aux_remocao);//� liberado espa�o da celula removida
							printf("Participante removido com sucesso! Aperte enter para voltar ao menu.\n");
							getchar();//capitura enter
							return lista;//retonar lista
						}else{
							lista_aux_remocao->proximo=lista_aux->proximo;//proximo da auxiliar remo��o recebe a proxima da celula encontrada
							free(lista_aux);//� liberado espa�o da celula removida
							lista_aux=lista_aux_remocao;//auxiliar recebe a auxiliar de remo��o
							printf("Participante removido com sucesso! Aperte enter para voltar ao menu.\n");
							getchar();
							return lista;//retorna lista
						}
					}else if(opcao_submenu == 'n'){
						printf("Remocao cancelada! Aperte enter para voltar ao menu.\n");
						getchar();
						return lista;//se n�o n�o modifica nada e retorna a lista
					}else{
						printf("Opcao invalida! Aperte enter para voltar ao menu.\n");
						getchar();
						return lista;//se op��o for invalida tambem retorna a lista sem modificar nada
					}
					
				}else{
				lista_aux_remocao=lista_aux;//auxiliar de remo��o recebe auxiliar
				lista_aux=lista_aux->proximo;}}//auxiliar recebe seu proximo
			printf("N�o foi encontrado nada correspondente. precione enter para voltar ao menu.");
			getchar();
			return lista;//retorna a lista
			break;
		case 2:
			printf("Digite o munero de matricula a ser procurado.");
			gets(campo->matriculas);//captura o elemento a ser procurado
			while(lista_aux!=NULL){//percorre a lista pra procurar o participante
				if(campo->matriculas==lista_aux->matriculas){//verifica se � o participante desejado
					printf("Participante encontrado ele �:\n");//se for exbibe os dados do participante
					printf("Nome da pessoa: ");
					puts(lista_aux->nome);		
					printf("CPF da pessoa: ");
					puts(lista_aux->cpf);
					printf("Email: ");
					puts(lista_aux->email);
					printf("Matricula: ");
					puts(lista_aux->matriculas);
					printf("\nData de nascimento: ");
					puts(lista_aux->data_nascimento);
					printf("Ocupa��o: ");
					if(lista_aux->ocupacao == 'E'){
						printf("Estudante\n\n");
					}else if(lista_aux->ocupacao == 'P'){
						printf("Professor\n\n");
					}
					printf("Realmente deseja excluir ele s ou n\n");
					scanf("%c",&opcao_submenu);//pergunta se realmente o usuario deseja excluir o participantes
					getchar();
					if(opcao_submenu == 's'){//se sim
						if(lista->matriculas==campo->matriculas){//realiza uma compara��o para ver se � o primeiro elemento
							lista_aux_remocao=lista;//auxiliar de remo��o recebe o primeiro elemento
							lista=lista->proximo;//a lista passa a iniciar no segundo
							free(lista_aux_remocao);//� liberado espa�o da celula removida
							printf("Participante removido com sucesso! Aperte enter para voltar ao menu.\n");
							getchar();
							return lista;//retonar lista
						}else{
							lista_aux_remocao->proximo=lista_aux->proximo;//proximo da auxiliar remo��o recebe a proxima da celula encontrada
							free(lista_aux);//� liberado espa�o da celula removida
							lista_aux=lista_aux_remocao;//auxiliar recebe a auxiliar de remo��o
							printf("Participante removido com sucesso! Aperte enter para voltar ao menu.\n");
							getchar();
							return lista;//retorna a lista
						}
					}else if(opcao_submenu == 'n'){//se n�o n�o modifica nada e retorna a lista
						printf("Remocao cancelada! Aperte enter para voltar ao menu.\n");
						getchar();
						return lista;
					}else{//se op��o for invalida tambem retorna a lista sem modificar nada
						printf("Opcao invalida! Aperte enter para voltar ao menu.\n");
						getchar();
						return lista;
					}
				}else{
				lista_aux_remocao=lista_aux;//auxiliar de remo��o recebe auxiliar
				lista_aux=lista_aux->proximo;}//auxiliar recebe seu proximo
			}
			printf("N�o foi encontrado nada correspondente. precione enter para voltar ao menu.");
			getchar();
			return lista;//retorna a lista
			break;
		case 3:
			printf("Digite o Nome a ser procurado.");
			gets(campo->nome);//capitura o elemento a ser procurado
			while(lista_aux!=NULL){//percorre a lista pra procurar o participante
				verificador =strcmp(campo->nome,lista_aux->nome);//verifica se � o participante desejado
				if(verificador==0){//se for exbibe os dados do participante
					printf("Participante encontrado ele �:\n");
					printf("Nome da pessoa: ");
					puts(lista_aux->nome);		
					printf("CPF da pessoa: ");
					puts(lista_aux->cpf);
					printf("Email: ");
					puts(lista_aux->email);
					printf("Matricula: ");
					puts(lista_aux->matriculas);
					printf("\nData de nascimento: ");
					puts(lista_aux->data_nascimento);
					printf("Ocupa��o: ");
					if(lista_aux->ocupacao == 'E'){
						printf("Estudante\n\n");
					}else if(lista_aux->ocupacao == 'P'){
						printf("Professor\n\n");
					}
					printf("Realmente deseja excluir ela s ou n");//pergunta se realmente o usuario deseja excluir o participantes
					scanf("%c",&opcao_submenu);
					getchar();
					if(opcao_submenu == 's'){//se sim
						verificador =strcmp(campo->nome,lista->nome);//realiza uma compara��o para ver se � o primeiro elemento
						if(verificador==0){//se for o primeiro elemento
							lista_aux_remocao=lista;//auxiliar de remo��o recebe o primeiro elemento
							lista=lista->proximo;//a lista passa a iniciar no segundo
							free(lista_aux_remocao);//� liberado espa�o da celula removida
							printf("Participante removido com sucesso! Aperte enter para voltar ao menu.\n");
							getchar();
							return lista;//retorna a lista
						}else{
							lista_aux_remocao->proximo=lista_aux->proximo;//proximo da auxiliar remo��o recebe a proxima da celula encontrada
							free(lista_aux);//� liberado espa�o da celula removida
							lista_aux=lista_aux_remocao;//auxiliar recebe a auxiliar de remo��o
							printf("Participante removido com sucesso! Aperte enter para voltar ao menu.\n");
							getchar();
							return lista;//retorna a lista
						}
					}else if(opcao_submenu == 'n'){//se n�o n�o modifica nada e retorna a lista
						printf("Remocao cancelada! Aperte enter para voltar ao menu.\n");
						getchar();
						return lista;//retorna a lista
					}else{
						printf("Opcao invalida! Aperte enter para voltar ao menu.\n");//se op��o for invalida tambem retorna a lista sem modificar nada
						getchar();
						return lista;
					}
					}else{
				lista_aux_remocao=lista_aux;//auxiliar de remo��o recebe auxiliar
				lista_aux=lista_aux->proximo;}//auxiliar recebe seu proximo
			}
			printf("N�o foi encontrado nada correspondente. precione enter para voltar ao menu.");
			getchar();
			return lista;//return lista
			break;
		default:
			return lista;//se a op��o for invalida retorna a lista sem modificar nada
			printf("Op��o invalida.\n");
			break;
	}
}
		

Participantes* listar_participantes(Participantes *lista){//fun�a� que lista os participantes
	if(lista==NULL){//se a lista for vazia ele retorna pra o menu para cadastrar
		printf("Erro lista vazia!pressione enter para voltar ao menu principal.");
		getchar();//captura enter
		system("cls");//limpa a tela
		return (lista);
	}
	system("cls");//limpa a tela
	int opcao_menu;//uma variavel para o menu de op��es
	printf("Voc� deseja listar ou consultar por:\n	1-Listar por Ordem alfabetica.\n	2-Realizar consulta por CPF.\n	3-Listar por Ocupa��o.\n	Outro digito para voltar ao menu principal.\n");
	scanf("%i",&opcao_menu);
	getchar();
	switch (opcao_menu){
		case 1://caso seja pra lsitar por ordem alfabetica
			lista=ordena_lista(lista);//lista recebe a modifica��o ordenada
			printf("Lista acaba de ser ordenada\n");
			mostrar_lista_ordenada(lista);//agora a lista � exibida
			break;
		case 2://caso seja para procurar por um cpf
			consulta_cpf(lista);//fun��o de consultar � chamada
			break;
		case 3://caso seja para listar por ocupa��o a fun��o respectiva � chamada
			listar_ocupacao(lista);
			break;
		default:
			break;
	}
	system("cls");//limpa a tela
	return lista;
}

Participantes* editar_participantes(Participantes *lista_aux){//fun��o para editar os participantes
	system("cls");//limpa tela
	int opcao_submenu;//variavel para o submenu
	char ocupacao;//exibe o participante encontrado
	printf("Participante encontrado ele �:\n");
	printf("Nome da pessoa: ");
	puts(lista_aux->nome);		
	printf("CPF da pessoa: ");
	puts(lista_aux->cpf);
	printf("Email: ");
	puts(lista_aux->email);
	printf("Matricula: ");
	puts(lista_aux->matriculas);
	printf("Data de nascimento: ");
	puts(lista_aux->data_nascimento);
	printf("Ocupa��o: ");
	if(lista_aux->ocupacao == 'E'){
		printf("Estudante\n\n");
	}else if(lista_aux->ocupacao == 'P'){
		printf("Professor\n\n");
	}
	printf("Qual dos campos deseja editar?	1-nome\n	2-cpf\n	3-email\n	4-matricula\n	5-Data de nascimento\n	6-Ocupacao\n	outro numero para sair.\n");
	scanf("%i",&opcao_submenu);//captura a op��o
	getchar();
	switch(opcao_submenu){//verifica a op��o
		case 1:
			printf("Digite o novo nome:\n");
			gets(lista_aux->nome);//captura a informa��o para alterar, ja celula.
			printf("Nome alterado com sucesso! pressione enter para continuar.");
			getchar();
			return lista_aux;//retorna a auxiliar
			break;
		case 2:
			printf("Digite o novo CPF:\n");
			gets(lista_aux->cpf);//captura a informa��o para alterar, ja celula.
			printf("CPF alterado com sucesso! pressione enter para continuar.");
			getchar();
			return lista_aux;//retorna a auxiliar
			break;
		case 3:
			printf("Digite o novo email:");
			gets(lista_aux->email);//captura a informa��o para alterar, ja celula.
			printf("Email alterado com sucesso! pressione enter para continuar.");
			getchar();
			return lista_aux;//retorna a auxiliar
			break;
		case 4:
			printf("Digite o nova matricula:");
			gets(lista_aux->matriculas);//captura a informa��o para alterar, ja celula.
			printf("Matricula alterada com sucesso! pressione enter para continuar.");
			getchar();
			return lista_aux;//retorna a auxiliar
			break;
		case 5:
			printf("Digite o nova Data de nascimento:");
			gets(lista_aux->data_nascimento);//captura a informa��o para alterar, ja celula.
			printf("Data de nascimento alterada com sucesso! pressione enter para continuar.");
			getchar();
			return lista_aux;//retorna a auxiliar
			break;
		case 6:
			printf("Ocupa��o E para Estudante ou P para Professor:\n");
			scanf("%c",&ocupacao);
			getchar();//pega informa��o sobre estudante e professor
			if(ocupacao == 'E' || ocupacao == 'P'){//usuario pode digitar tanto em caixa alta ou baixa
				lista_aux->ocupacao=ocupacao;
			}else if(ocupacao == 'e'){//se em caixa baixa � convertido para alta
				lista_aux->ocupacao='E';
			}else if(ocupacao == 'p'){
				lista_aux->ocupacao='P';
			}else{
				printf("Voc� digitou uma ocupa��o invalida por padr�o ele sera estudante.\n");
				lista_aux->ocupacao='E';//se a pessoa erra por padrao ele sera estudante
			}
			printf("Ocupa��o alterada com sucesso! pressione enter para continuar.");
			getchar();
			return lista_aux;//retorna a auxiliar
			break;
		default:
			return lista_aux;//retorna a auxiliar
			break;}
return lista_aux;}

void listar_ocupacao(Participantes *lista){//fun��o para listar por ocupa��o
	system("cls");//limpa a tela
	Participantes *lista_aux=lista;//cria um ponteiro auxiliar que aponta pra lista
	int opcao_menu,contador=0;//variaveis de op��o e para contar qual o numero da pessoa apenas por estetica
	printf("Deseja listar os Professores ou Estudantes?\n	1-Professores\n	2-Estudantes.\n	 outro digito para voltar ao menu anterior.\n\n");
	scanf("%i",&opcao_menu);
	getchar();
	
	switch (opcao_menu){
		case 1:
			while(lista_aux != NULL){//percorre a lista e exibe apenas os prifessores
				if(lista_aux->ocupacao == 'P'){
				contador=contador+1;
				printf("Professor de numero %i:\n",contador);
				printf("Nome da pessoa: ");
				puts(lista_aux->nome);		
				printf("CPF da pessoa: ");
				puts(lista_aux->cpf);
				printf("Email: ");
				puts(lista_aux->email);
				printf("Matricula: ");
				puts(lista_aux->matriculas);
				printf("Data de nascimento: ");
				puts(lista_aux->data_nascimento);
				printf("Ocupa��o: ");
				if(lista_aux->ocupacao == 'E'){
					printf("Estudante\n\n");
				}else if(lista_aux->ocupacao == 'P'){
					printf("Professor\n\n");
				}}
				lista_aux=lista_aux->proximo;//auxiliar passa pra o proximo
			}
			printf("Todos os participantes foram listados acima.\n pressione enter para voltar ao menu anterior.");
			getchar();
		break;
		case 2:
			while(lista_aux != NULL){//percorre a lista e exibe apenas os estudantes
				if(lista_aux->ocupacao == 'E'){
				contador=contador+1;
				printf("Professor de numero %i:\n",contador);
				printf("Nome da pessoa: ");
				puts(lista_aux->nome);		
				printf("CPF da pessoa: ");
				puts(lista_aux->cpf);
				printf("Email: ");
				puts(lista_aux->email);
				printf("Matricula: ");
				puts(lista_aux->matriculas);
				printf("Data de nascimento: ");
				puts(lista_aux->data_nascimento);
				printf("Ocupa��o: ");
				if(lista_aux->ocupacao == 'E'){
					printf("Estudante\n\n");
				}else if(lista_aux->ocupacao == 'P'){
					printf("Professor\n\n");
				}}
				lista_aux=lista_aux->proximo;//auxiliar passa para o proximo
			}
		printf("Todos os participantes foram listados acima.\n pressione enter para voltar ao menu anterior.");
		getchar();
		break;
		default:
			printf("Aperte enter para voltar ao menu anterior.");
			getchar();
	}
}

void consulta_cpf(Participantes *lista){//fun��o que faz a consulta por cpf
	system("cls");//limpa a tela
	Participantes *lista_aux=lista;//cria um ponteiro auxiliar que aponta pra lista
	Participantes *campo=NULL;//cria um ponteiro para o campo procurado
	int verificador=1;//verificador usado na compara��o
	campo=(Participantes*) malloc (sizeof (Participantes));//aloca espa�o para campo do tamanho dos participantes
	printf("Digite o CPF a ser procurado.\n");
	gets(campo->cpf);
	while(lista_aux!=NULL){//enquanto a lista ainda n�o tiver sido percorrida completamente
		verificador =strcmp(campo->cpf,lista_aux->cpf);//verficador recebe a compara��o do elemeto da lista com o elemento capturado
		if(verificador==0){//se participante encontrado � exibido qual o participante
			printf("Participante encontrado ele �:\n");
			printf("Nome da pessoa: ");
			puts(lista_aux->nome);		
			printf("CPF da pessoa: ");
			puts(lista_aux->cpf);
			printf("Email: ");
			puts(lista_aux->email);
			printf("Matricula: ");
			puts(lista_aux->matriculas);
			printf("Data de nascimento: ");
			puts(lista_aux->data_nascimento);
			printf("Ocupa��o: ");
			if(lista_aux->ocupacao == 'E'){
				printf("Estudante\n\n");
			}else if(lista_aux->ocupacao == 'P'){
				printf("Professor\n\n");
			}}
		lista_aux=lista_aux->proximo;}//faz com que o ponteiro auxiliar passe pra proxima celula
	printf("Particcipante listado acima. pressione enter para voltar ao menu.");
	getchar();
}

void verifica_data_limite(char *data[11]){//fun��o pra verificar o limite
	char dia[3];//variavel para pegar o dia
	char mes[3];//variavel para pegar o mes
	char ano[3];//variavel para pegar o ano
	
	FILE *data_limite; //ponteiro para o arquivo txt entrada
	data_limite = fopen("data_limite.txt", "r");//ponteiro recebe a abertura do arquivo
	if(data_limite == NULL){ //avisa caso o o arquivo n�o seja encontrado
		printf("Esta parece ser a primeira inicializa��o do programa.\n");
		fclose(data_limite);//arquivo � fechado e � pedido a data lmite
		printf("Insira uma data limite para as inscri��es de novos participantes.\n");
		printf("Diga o dia. exemplo 30.\n");
		gets(dia);
		printf("Diga o mes. exemplo 01.\n");
		gets(mes);
		printf("Diga o ano, apenas dois ultimos caracteres. exemplo 15.\n");
		gets(ano);
			FILE *data_limite; //ponteiro para o arquivo txt entrada
			data_limite = fopen("data_limite.txt", "w");///ponteiro recebe a abertura do arquivo e a ddata limite � escrita no arquivo
			fputs(mes,data_limite);
			fprintf(data_limite,"/");
			fputs(dia,data_limite);
			fprintf(data_limite,"/");
			fputs(ano,data_limite);
			fclose(data_limite);//arquivo fechado
		FILE *data_limite1; //ponteiro para abrir novamente o arquivo de texto mas dessa vez para ler a string concatenada
		data_limite1 = fopen("data_limite.txt", "r");///ponteiro recebe a abertura do arquivo
		fgets(data,11,data_limite1);//� transferido a data limite para a variavel
		fclose(data_limite1);//arquivo fechado
			return 0;
	}
	fgets(data,11,data_limite);
	fclose(data_limite);//arquivo fechado
	return 0;
}

void sair_salva_cadastro(Participantes *lista){//fun��o para sair do programa
	FILE *cadastro; //ponteiro para o arquivo txt entrada
	cadastro = fopen("cadastro.txt", "w");
	while(lista!=NULL){//grava tidas as celulas no arquivo
		fputs(lista->nome,cadastro);
		fprintf(cadastro,"\n");		
		fputs(lista->cpf,cadastro);
		fprintf(cadastro,"\n");
		fputs(lista->email,cadastro);
		fprintf(cadastro,"\n");
		fputs(lista->matriculas,cadastro);
		fprintf(cadastro,"\n");
		fputs(lista->data_nascimento,cadastro);
		fprintf(cadastro,"\n");
		fprintf(cadastro,"%c",lista->ocupacao);
		if(lista->proximo!=NULL){//para que n�o imprima uma linha vazia no arquivo de texto e na leitura n�o crie uma celula vazia.
			fprintf(cadastro,"\n");
		}

		lista=lista->proximo;//lista recebe sua proxima celula
	}
	fclose(cadastro);//arquivo fechado
	printf("Cadastro salvo. At� mais!\n");
	exit(0);//sai do programa
}

Participantes* ordena_lista(Participantes *lista){//fun��o para ordenar a lista
	int resultado;//variavel para o resultado de compara��es
	int contador=0;//variavel para verificar quantas vezes a ordena��o foi execultada
	Participantes *campo_anterior=lista;//ponteiro para ser o antecessor do ponteiro auxiliar
	Participantes *campo_sucessor=lista->proximo;//ponteiro para ser o sucessor do ponteiro auxliar
	Participantes *lista_aux=lista;//ponteiro auxliar para percorrer a lista e ordenar
	if(lista->proximo==NULL){
		return lista;//se a lista for nula, retorna a lista
	}
	while(lista_aux!=NULL){//enquanto a lista n�o for completamente percorrida
	if(lista_aux->nome==lista->nome && campo_sucessor!=NULL){//se for o primeiro elemento e houver um segundo
		resultado=strcmpi(lista_aux->nome,campo_sucessor->nome);//� comparado os dois elementos primeiro e segundo
		if(resultado>0){//se estiverem desordenados
			lista_aux->proximo=campo_sucessor->proximo;//proximo do auxiliar aponta para o terceiro elemento
			campo_sucessor->proximo=lista_aux;//proximo do sucessor aponta pra auxiliar
			lista=campo_sucessor;//lista aponta pra o antigo sucessor que passa a ser o primeiro elemento
			lista_aux=lista;//lista auxiliar volta ao inicio
			campo_sucessor=lista_aux->proximo;//campo sucessor recebe o segundo elemento
		}
	}else{
		resultado=strcmpi(lista_aux->nome,campo_sucessor->nome);//� comparado o campo com o proximo
		if(resultado>0 && campo_sucessor!=NULL){//se estiver desordenado e n�o for o ultimo elemento
			campo_anterior->proximo=campo_sucessor;//proximo campo anterior aponta pra o campo sucessor
			lista_aux->proximo=campo_sucessor->proximo;// proximo do auxiliar aponta pra o proximo do sucessor
			campo_sucessor->proximo=lista_aux;//proximo do sucessor aponta pra auxiliar 
			lista_aux=lista;//lista auxiliar volta ao inicio
			campo_sucessor=lista_aux->proximo;//campo sucessor recebe o proximo elemento
			campo_anterior=lista_aux;//campo anterior recebe auxiliar antes dele passar pra proxima celula
		}
	}
	campo_anterior=lista_aux;//campo anterior recebe auxiliar antes dele passar pra proxima celula
	lista_aux=lista_aux->proximo;//auxiliar recebe a proxima celula
	if(lista_aux->proximo == NULL){//se essa celular for a ultima
		if(contador==1){//verifica se o programa realizou a verifica��o completa ao menos duas vezes
			break;
		}else{//recoloca a lista auxiliar e o campo sucessor no inicio da lista
			lista_aux=lista;//auxiliar volta ao inicio
			campo_sucessor=lista->proximo;//campo_sucessor recebe o segundo elemnto
			contador=1;//avisa que a lista ja foi verifica ao menos uma vez
		}	
	}else{	
	campo_sucessor=lista_aux->proximo;}//campo sucessor recebe o proximo da auxiliar
	}
	return lista;//retorna a lista
}

void mostrar_lista_ordenada(Participantes *lista){//fun�a� para mostrar a lista depois de ser ordenada
	Participantes *lista_aux=lista;//cria um ponteiro auxiliar que aponta pra lista
	int contador=0;//variavel para contar as pessoas apenas por estetica
	system("cls");//limpa tela
	while(lista_aux != NULL){//enquanto a auxiliar n�o for nula ele vai exibir os participantes
		contador=contador+1;//contador � incrementado
		printf("Pessoa a %i:\n",contador);
		printf("Nome da pessoa: ");
		puts(lista_aux->nome);		
		printf("CPF da pessoa: ");
		puts(lista_aux->cpf);
		printf("Email: ");
		puts(lista_aux->email);
		printf("Matricula: ");
		puts(lista_aux->matriculas);
		printf("Data de nascimento: ");
		puts(lista_aux->data_nascimento);
		printf("Ocupa��o: ");
		if(lista_aux->ocupacao == 'E'){
			printf("Estudante\n\n");
		}else if(lista_aux->ocupacao == 'P'){
			printf("Professor\n\n");
		}
		lista_aux=lista_aux->proximo;//auxliar recebe a proxima celula
	}
	printf("Aperte enter para voltar ao menu...");
	getchar();
	return 0;
}

Participantes* ler_cadastro_anterior(Participantes *lista){
	Participantes *novo_campo=NULL;//cria um ponteiro auxiliar de novo campo
	Participantes *campo_aux=NULL;//cria um ponteiro auxiliar para o campo lido
	char capitura_espaco;//essa variavel � para capturar uma quebra de linha entre duas celulas duante a leitura
	FILE *cadastro; //ponteiro para o arquivo txt entrada
	cadastro = fopen("cadastro.txt", "r");
	if(cadastro == NULL){ //avisa caso o o arquivo n�o seja encontrado
		lista=NULL;
		fclose(cadastro);
		return lista;
	}
	while(!feof(cadastro)){//enquanto o arquivo n�o for todo lido
			novo_campo=(Participantes*) malloc (sizeof (Participantes));//aloca espa�o para uma nova celula e passa do arquivo pra celula
			fgets(novo_campo->nome,60,cadastro);//pega informa��o do arquivo
			strtok(novo_campo->nome,"\n");//remove o a quebra de linha coletada do arquivo
			fgets(novo_campo->cpf,14,cadastro);//pega informa��o do arquivo
			strtok(novo_campo->cpf,"\n");//remove o a quebra de linha coletada do arquivo
			fgets(novo_campo->email,30,cadastro);//pega informa��o do arquivo
			strtok(novo_campo->email,"\n");//remove o a quebra de linha coletada do arquivo
			fgets(novo_campo->matriculas,20,cadastro);//pega informa��o do arquivo
			strtok(novo_campo->matriculas,"\n");//remove o a quebra de linha coletada do arquivo
			fgets(novo_campo->data_nascimento,20,cadastro);//pega informa��o do arquivo
			strtok(novo_campo->data_nascimento,"\n");//remove o a quebra de linha coletada do arquivo
			novo_campo->ocupacao=fgetc(cadastro);//pega informa��o do arquivo
			capitura_espaco=fgetc(cadastro);//captura um uma quebra de linha para diferenciar uma celula de outra.
			novo_campo->proximo=NULL;//proximo campo recebe nulo
		if(lista==NULL){//se for o primeiro elemento da lista
			lista=(Participantes*) malloc (sizeof (Participantes));//aloca espa�o pra lista
			lista=novo_campo;		//e lista recebe o novo campo coletado
		}else{//inserindo no fim do arquivo ja insere ordenado.
			campo_aux=lista;//campo auxliar aponta pra lista
			while(campo_aux->proximo!=NULL){//campo auxliliar vai ate o ultimo elemento
				campo_aux=campo_aux->proximo;
			}
			campo_aux->proximo=novo_campo;//passa o campo auxiliar para apontar para o novo campo inserindo pelo fim
		}
	}
	fclose(cadastro);//fecha o arquivo
	return lista;//retorna a lista
}
