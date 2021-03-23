typedef struct dados dados;
void ler_arquivo(FILE **fp);
int comparar_string (const void *a, const void *b);
void print_most_similar_tracks(dados *d, char *tracks, int K);
void ler_csv(dados *d, int *total_musicas);
void countingsort_rec(dados *d, int total_musicas);
void busca_binaria(dados *d, int total_musicas, char *busca, int *r);
void dissimilaridade(dados *d, int q, int k, int total_musicas);