typedef struct job{
    int id;
    struct operation *operationHead;
    struct job *next;
} job;

typedef struct operation{
    int num;
    struct machine *machineHead;
    struct operation *next;
} operation;

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

void showMachines(machine *machineHead);
machine *m_create_new(int id);
machine *m_insert_end(machine **head, machine *machine_to_insert);
machine *m_find(machine *head, int id);

job *read_job();

void showJob(job *job);