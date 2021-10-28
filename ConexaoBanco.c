#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <mysql.h>

void erro(MYSQL *conexao)
{
    fprintf(stderr, "\n%s\n", mysql_error(conexao));
    mysql_close(conexao);
    exit(1);
}

MYSQL *__stdcall obterConexao()
{
    char *servidor = "127.0.0.1";
    char *utilizador ="root";
    char *senha ="";
    char *nomeBanco ="pessoa";

    MYSQL *conexao = mysql_init(NULL);

    if (!mysql_real_connect(conexao, servidor, utilizador, senha, nomeBanco, 0, NULL, 0))
    {
        erro(conexao);
    }
    else
    {
        printf("\nConexao realizada com sucesso!\n");
        return conexao;
    }
}/*
    função INSERT INTO do SQL
*/
void inserir(MYSQL *conexao, char *nome, char *sexo)
{
    char query[100];
    sprintf(query, "INSERT INTO Utilizador(nome, sexo) VALUES('%s', '%s');", nome, sexo);

    if (mysql_query(conexao, query)) // "INSERT INTO Utilizador(nome, sexo) VALUES('%s', '%s');", nome, sexo
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados inseridos com sucesso!\n");
    }
}
/*
    Função SELECT do SQL
*/
void ler(MYSQL *conexao)
{
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    if (mysql_query(conexao, "SELECT * FROM Utilizador"))
    {
        erro(conexao);
    }

    resultado = mysql_store_result(conexao);
    if (resultado == NULL)
    {
        erro(conexao);
    }

    while ((row = mysql_fetch_row(resultado)) != NULL)
    {
        printf("\nIdUtilizador: %s\n", row[0]);
        printf("Nome: %s\n", row[1]);
        printf("Sexo: %s\n", row[2]);
    }

    mysql_free_result(resultado);
}
/*
    Função DELETE do SQL
*/
void apagar(MYSQL *conexao, int idUtilizador)
{
    char query[100];
    sprintf(query, "DELETE FROM Utilizador WHERE idUtilizador = '%d';", idUtilizador);

    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados apagados com sucesso!\n");
    }
}
/*
    Função UPDATE do SQL
*/
void atualizar(MYSQL *conexao, int idUtilizador , char *nome)
{
    char query[100];
    sprintf(query, "UPDATE Utilizador SET nome = '%s' WHERE idUtilizador = '%d';", nome, idUtilizador);
        //update utilizador set nome ='TesteFeito' where idUtilizador ='16';
    if (mysql_query(conexao, query))
    {
        erro(conexao);
    }
    else
    {
        printf("\nDados atualizados com sucesso!\n");
    }
}
int main (){
     MYSQL *conexao = obterConexao();
     char nome[30];
     char sexo[30];
     int i;

     // função que faz o cadastro dinamico dos Utilizadores
    /*printf("\n*** CADASTRO DE UTILIZADORES ***\n");
    for (i = 1; i <= 2; i++)
    {
        printf("\n%d - Nome: ", i);
        //fflush(stdin);
        gets(&nome);
        printf("%d - Sexo: ", i);
        gets(&sexo);
        inserir(conexao, nome, sexo);
    }*/
    //Funcão de Lista todos os Utilizadores Cadastrados
     printf("\n*** UTILIZADORES CADASTRADOS ***\n");
     ler(conexao);
    //função que apaga os dados na tabela Utilizador
     //apagar(conexao,27);
    //atualizar(conexao,21,"Feia2021");
    //printf("\n*** UTILIZADORES CADASTRADOS ***\n");
    ler(conexao);
    mysql_close(conexao);
    return (0);
}
