#ifndef S21_3D_H
#define S21_3D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct OBJ {
  double **vertexes; //Массив вершин vertexes[№ вершины][x/y/z]
  int **facets; // Массив граней facets[№ грани][№-ра вершин, считая с 1]
} obj;
// Массив вершин vertexes заполняется от 1 до n_vertexes + 1, vertexes[0] -
// пустая строчка Это из-за того, что в гранях указаны №-ра вершин, считая с 1,
// а не с 0

int size_obj(const char *file_name, int *x, int *y, int *r);
void struct_malloc(obj *data);
void struct_free(obj *data);
int scan_obj(obj *data, const char *file_name);
int scan_vertex(obj *data, char *str_vals, int i_vertex);
int scan_facet(obj *data, char *str_vals, int i_facet);

#endif // S21_3D_H
