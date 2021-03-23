typedef struct skiplist skiplist;
typedef struct no no;
void ler_arquivo(FILE **fp);
int sorteia_nivel(skiplist *sk);
struct no* novo_no(char *str, signed long int nivel);
skiplist* criar(signed long int nivel_max, float p);
int busca(skiplist *sk, char *str);
int inserir(skiplist *sk, char *str);
