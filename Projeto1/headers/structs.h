/**
 * Author: Nicolae Malai
 * Email: a23495@alunos.ipca.pt
 * Github: niiK0
 * Date: 27/03/2022
 * Descrição: Structs creation and functions definition, Trabalho Pratico - EDA
 */

/**
 * @brief Struct to store jobs
 *
 * Has and int id (@@id)
 * Has an operation header (@@operationHead)
 * Has a next job pointer (@@next)
 */
typedef struct job{
    int id;
    struct operation *operationHead;
    struct job *next;
} job;

/**
 * @brief Struct to store operations
 *
 * Has and int num (@@num)
 * Has a machine header (@@machineHead)
 * Has a next operation pointer (@@next)
 */
typedef struct operation{
    int num;
    struct machine *machineHead;
    struct operation *next;
} operation;

/**
 * @brief Struct to store machines
 *
 * Has and int id (@@id) and timeValue (@@timeValue)
 * Has a next machine pointer (@@next)
 */
typedef struct machine{
    int id;
    int timeValue;
    struct machine *next;
} machine;

void showJobs(job *head);
job *j_create_new(int jobId, operation *operationHead);
job *j_insert_end(job **head, job *job_to_insert);
job *j_find(job *head, int id);

void showOperations(operation *head);
operation *o_create_new(int operationId, machine *machineHead);
operation *o_insert_end(operation **head, operation *operation_to_insert);
operation *o_find(operation *head, int num);
operation *o_get_last(operation *head);

void showMachines(machine *machineHead);
machine *m_remove(machine *head, machine *machine_to_remove);
machine *m_create_new(int id);
machine *m_insert_end(machine **head, machine *machine_to_insert);
machine *m_find(machine *head, int id);

job *read_job();
void write_job(job *head);

job *create_operation(job *j_head, job *job_where_to_insert, operation *op_to_insert);

void showJob(job *job);