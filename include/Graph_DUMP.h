#ifndef _GRAPH_DUMP_
#define _GRAPH_DUMP_

#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

void DrawTree(Tree_t* tree, Node_t* node, FILE* dot_file);
void CreateNode(Node_t* node, FILE* dot_file, Tree_t* tree);
void MakeArrow(Node_t* node, Tree_t* tree, FILE*  dot_file);
void SetRankToNodes(Tree_t* tree, Node_Info* progress, FILE* dot_file);
void FinishDotFile(FILE* dot_file);
void ProgressTreeInit(Node_Info* progress, Tree_t* tree);
void RecursiveFillNodeInfoProgress(Node_Info* progress, Node_t* node, size_t rank);

#endif //_GRAPH_DUMP_