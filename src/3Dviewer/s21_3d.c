#include "s21_3d.h"

int count_v; // Счетчик вершин
int count_f; // Счетчик граней
int v_in_f; // Построение квадратами или треугольниками, 3 или 4 вершины

int size_obj(const char *file_name, int *x, int *y, int *r) {
  FILE *fp = NULL;
  int result = 1;
  count_v = 0;
  count_f = 0;

  if ((fp = fopen(file_name, "r")) != NULL) {
    while (1) {
      char str_type[256];
      char str_vals[256];
      char s[256][4];
      fscanf(fp, "%255s", str_type);
      fscanf(fp, "%255[^\n]s", str_vals);
      if (strcmp(str_type, "v") == 0) {
        count_v++;
      } else if (strcmp(str_type, "f") == 0) {
        count_f++;
        int result =
            sscanf(str_vals, "%255s%255s%255s%255s", s[0], s[1], s[2], s[3]);
        if (result == 3 || result == 4)
          v_in_f = result;
      }
      if (feof(fp))
        break;
    }
    fclose(fp);
  } else {
    result = 0;
  }
  *x = count_v;
  *y = count_f;
  *r = v_in_f;

  return result;
}

void struct_malloc(obj *data) {
  data->vertexes = (double **)calloc(count_v + 1, sizeof(double *));
  if (data->vertexes) {
    for (int i = 0; i < count_v + 1; i++)
      data->vertexes[i] = (double *)calloc(3, sizeof(double));
  }

  data->facets = (int **)calloc(count_f, sizeof(int *));
  if (data->facets) {
    for (int i = 0; i < count_f; i++)
      data->facets[i] = (int *)calloc(v_in_f, sizeof(int));
  }
}

void struct_free(obj *data) {
  for (int i = 0; i < count_v + 1; i++)
    free(data->vertexes[i]);
  free(data->vertexes);

  for (int i = 0; i < count_f; i++)
    free(data->facets[i]);
  free(data->facets);
}

int scan_obj(obj *data, const char *file_name) {
  FILE *fp = NULL;
  int result = 1;

  if ((fp = fopen(file_name, "r")) != NULL) {
    int i_vertex = 1, i_facet = 0;

    while (1) {
      char str_type[256];
      char str_vals[256];

      fscanf(fp, "%255s", str_type);
      fscanf(fp, "%255[^\n]s", str_vals);
      if (strcmp(str_type, "v") == 0) {
        scan_vertex(data, str_vals, i_vertex);
        i_vertex++;
      } else if (strcmp(str_type, "f") == 0) {
        scan_facet(data, str_vals, i_facet);
        i_facet++;
      }
      if (feof(fp))
        break;
    }

    fclose(fp);
  } else {
    result = 0;
  }

  return result;
}

int scan_vertex(obj *data, char *str_vals, int i_vertex) {
  char s[3][256];
  int result = 0;

  sscanf(str_vals, "%255s%255s%255s", s[0], s[1], s[2]);
  for (int j = 0; j < 3; j++)
    result += sscanf(s[j], "%255lf", &(data->vertexes[i_vertex][j]));

  return result == 3;
}

int scan_facet(obj *data, char *str_vals, int i_facet) {
  char s[4][256];
  int result = 0;

  sscanf(str_vals, "%255s%255s%255s%255s", s[0], s[1], s[2], s[3]);
  for (int j = 0; j < v_in_f; j++)
    result += sscanf(s[j], "%255d", &(data->facets[i_facet][j]));

  return result == v_in_f;
}
