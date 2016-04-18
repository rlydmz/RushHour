
#ifndef H_FIFO
#define H_FIFO

// _____ FIFO _____//


typedef struct FileElem FileElem;
struct FileElem
{
    game g;
    FileElem *next;
};

typedef struct Fifo Fifo;
struct Fifo
{
    FileElem *first;
};

void enfiler(Fifo* file, game newGame);
game defiler(Fifo* file);
Fifo* initialiser_fifo();
bool is_fifo_empty(Fifo* file);
game get_value(Fifo* file);


#endif // H_FIFO
