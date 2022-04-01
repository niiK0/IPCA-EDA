/**
 * Author: Nicolae Malai
 * Email: a23495@alunos.ipca.pt
 * Github: niiK0
 * Date: 27/03/2022
 * Descrição: Functions definition of the menus, Trabalho Pratico - EDA
 */

void MainMenu();
int GetInt(int min, int max);
job *add_operation_menu(job *head);
job *remove_operation_menu(job *head);
job *change_operation_menu(job *head);
machine *add_machine_menu(machine *m_head);
operation *choose_change_operation_menu(operation *selected_operation, operation *head);
void job_list_menu(job *head);
void data_menu(job *head);
void find_lowest_for_job(job *head);
void find_highest_for_job(job *head);
void find_average_for_operation(job *head);